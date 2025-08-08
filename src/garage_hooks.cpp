#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include <ui/CustomCharacterColorPage.hpp>

using namespace geode::prelude;

class $modify(GJGarageLayerModify, GJGarageLayer) {
    struct Fields {
        IconType current_page_type = IconType::Cube;
        bool m_current_page_invalid = false;
    };

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

        this->customUpdateColors();

        Settings::sharedInstance()->m_garage_layer = this;
        return true;
    }

    void onColorOverrideButton(CCObject* pSender) {
        bool p2 = this->getIsP2();

        auto custom_color_page = CustomCharacterColorPage::create(p2);
        custom_color_page->show();
    }

    void setupPage(int p0, IconType p1) {
        GJGarageLayer::setupPage(p0, p1);
        if (static_cast<int>(p1) < 9) {
            this->m_fields->current_page_type = p1;
            this->m_fields->m_current_page_invalid = false;
        } else {
            this->m_fields->m_current_page_invalid = true;
        }
    }

    void selectTab(IconType p0) {
        GJGarageLayer::selectTab(p0);
        this->customUpdateColors();
    }

    void onSelect(cocos2d::CCObject* sender) {
        GJGarageLayer::onSelect(sender);
        auto settings = Settings::sharedInstance();
        if (this->getIsP2()) {
            if (!this->m_fields->m_current_page_invalid) {
                Mod::get()->setSavedValue<int>("_ui_lasttype2", static_cast<int>(this->m_fields->current_page_type));
            }
        } else {
            if (!this->m_fields->m_current_page_invalid) {
                Mod::get()->setSavedValue<int>("_ui_lasttype1", static_cast<int>(this->m_fields->current_page_type));
            }
        }
        this->customUpdateColors();
    }

    void updatePlayerColors() {
        GJGarageLayer::updatePlayerColors();
        this->customUpdateColors();
    }

    bool getIsP2() {
        bool p2 = false;
        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            auto arrow2 = as<CCSprite*>(this->getChildByID("arrow-2")); // this is added by separate dual icons
            if (arrow2) {
                log::debug("found arrow 2 from separate dual icons");
                p2 = arrow2->isVisible();
                log::debug("p2: {}", p2);
            }
        }
        return p2;
    }

    void customUpdateColors() {
        auto mod = Mod::get();
        auto settings = Settings::sharedInstance();
        auto game_manager = GameManager::sharedState();

        auto player1 = as<SimplePlayer*>(this->getChildByID("player-icon"));

        if (player1) {
            bool p2 = false;
            auto p1_override = CGC_OVERRIDE_GAMEMODE(mod->getSavedValue<int>("_ui_lasttype1", 0));

            int col1 = p1_override.enabled ? p1_override.primary : settings->m_defaultColor;
            int col2 = p1_override.enabled ? p1_override.secondary : settings->m_defaultColor2;

            player1->setColor(game_manager->colorForIdx(col1));
            player1->setSecondColor(game_manager->colorForIdx(col2));
        }

        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            auto player2 = as<SimplePlayer*>(this->getChildByID("player2-icon"));
            bool p2 = true;

            if (player2) {
                auto p2_override = CGC_OVERRIDE_GAMEMODE(mod->getSavedValue<int>("_ui_lasttype2", 0));

                int col1 = p2_override.enabled ? p2_override.primary : settings->m_defaultColor;
                int col2 = p2_override.enabled ? p2_override.secondary : settings->m_defaultColor2;

                player2->setColor(game_manager->colorForIdx(col1));
                player2->setSecondColor(game_manager->colorForIdx(col2));
            }
        }
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
