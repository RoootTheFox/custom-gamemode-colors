using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include <ui/CustomCharacterColorPage.hpp>

class $modify(GJGarageLayerModify, GJGarageLayer) {
    virtual bool init() {
        if (!GJGarageLayer::init()) return false;

        auto menu = static_cast<CCMenu*>(this->getChildByID("shards-menu"));

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(TEXTURE_PAINT_BUTTON),
            this,
            menu_selector(GJGarageLayerModify::onColorOverrideButton)
        );

        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onColorOverrideButton(CCObject* pSender) {
        auto custom_color_page = CustomCharacterColorPage::customCreate();
        dynamic_cast<FLAlertLayer*>(custom_color_page)->show();
    }
};
