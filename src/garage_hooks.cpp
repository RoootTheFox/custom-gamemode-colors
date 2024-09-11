#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include <ui/CustomCharacterColorPage.hpp>

using namespace geode::prelude;

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
        // if separate dual icons is loaded

        bool p2 = false;
        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            auto arrow2 = as<CCSprite*>(this->getChildByID("arrow-2")); // this is added by separate dual icons
            if (arrow2) {
                log::debug("found arrow 2 from separate dual icons");
                p2 = arrow2->isVisible();
                log::debug("p2: {}", p2);
            }
        }

        auto custom_color_page = CustomCharacterColorPage::customCreate(p2);
        custom_color_page->FLAlertLayer::show();
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