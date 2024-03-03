using namespace geode::prelude;

#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include <ui/CustomCharacterColorPage.hpp>

class $modify(GJGarageLayerModify, GJGarageLayer) {
    virtual bool init() {
        if (!GJGarageLayer::init()) return false;
        log::debug("GJGarageLayer::init");

        auto menu = static_cast<CCMenu*>(this->getChildByID("shards-menu"));

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_paintBtn_001.png"),
            this,
            menu_selector(GJGarageLayerModify::onColorOverrideButton)
        );

        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onColorOverrideButton(CCObject* pSender) {
        auto custom_color_page = CustomCharacterColorPage::customCreate();
        log::debug("custom_color_page CREATED meow");
        dynamic_cast<FLAlertLayer*>(custom_color_page)->show();
    }
};

class $modify(CharacterColorPage) {
    bool init() {
        if (!CharacterColorPage::init()) return false;
        log::debug("CharacterColorPage::init");

        return true;
    }
};