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
        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            if (getChildByIDRecursive("arrow-2")->isVisible()) {
                FLAlertLayer::create("Be careful!", "You have Weebify's \"Separate Dual Icons\" mod installed, and it looks like you're trying to edit Player 2's colors. This is currently not supported at this time.", "OK")->show();
                return;
            }
        }
        auto custom_color_page = CustomCharacterColorPage::customCreate();
        dynamic_cast<FLAlertLayer*>(custom_color_page)->show();
    }
};

class $modify(CharacterColorPage) {
    void onPlayerColor(cocos2d::CCObject* sender) {
        auto game_manager = GameManager::sharedState();
        auto settings = Settings::sharedInstance();

        CharacterColorPage::onPlayerColor(sender);

        // the player colors in gamemanager are updated after onPlayerColor is called
        settings->m_defaultColor = game_manager->m_playerColor;
        settings->m_defaultColor2 = game_manager->m_playerColor2;
    }
};
