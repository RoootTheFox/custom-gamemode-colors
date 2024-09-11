#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "settings.hpp"

using namespace geode::prelude;

class $modify(PlayerObject) {
    void switchedToMode(GameObjectType p0) {       
        PlayerObject::switchedToMode(p0);
        //log::info("switchedToMode");

        meow();
    }

    // this technically isn't needed either but i'm keeping it just to be safe
    void updatePlayerFrame(int p0) {
        PlayerObject::updatePlayerFrame(p0);
        //log::info("updatePlayerFrame {}", p0);

        meow();
    }

// lazy
#if !defined(GEODE_IS_IOS) && !defined(GEODE_IS_MACOS)
    void updatePlayerArt() {
        PlayerObject::updatePlayerArt();
        //log::info("updatePlayerArt");

        meow();
    }
#endif

    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
        if(!PlayerObject::init(p0, p1, p2, p3, p4)) return false;
        //log::info("init");

        meow();
        return true;
    }
#if defined(GEODE_IS_IOS) || defined(GEODE_IS_MACOS) || defined(GEODE_IS_WINDOWS) // TEMPORARY; REMOVE THIS WHEN FLASHPLAYER IS SORTED OUT !!
    void update(float p0) {
        PlayerObject::update(p0);
        meow();
    }
#else
    void flashPlayer(float p0, float p1, cocos2d::ccColor3B mainColor, cocos2d::ccColor3B secondColor) {
        // make flashPlayer do nothing.
        // flashPlayer sets the players color back to the original color. TODO: RE flashPlayer
        // to figure out how to fix this.
    }
#endif

    void flipGravity(bool p0, bool p1) {
        meow();
        PlayerObject::flipGravity(p0, p1);
    }

    void meow() {
        auto gameManager = GameManager::get();
        auto settings = Settings::sharedInstance();

        auto play_layer = gameManager->m_playLayer;
        auto edit_layer = gameManager->m_levelEditorLayer;

        // only run on playlayer
        if (play_layer == nullptr && edit_layer == nullptr) return;

        // this will also be used for proper dual color support later
        bool p1 = this == gameManager->m_gameLayer->m_player1;
        bool p2 = this == gameManager->m_gameLayer->m_player2;

        // fix issues with globed
        if (!(p1 || p2)) {
            return;
        }

        bool isCube = !this->m_isShip && !this->m_isBall && !this->m_isBird && !this->m_isDart && !this->m_isRobot && !this->m_isSpider && !this->m_isSwing;

        if(isCube) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_cube.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_cube.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }
        
        if(this->m_isShip) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_ship.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ship.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_ship.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ship.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBall) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_ball.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ball.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_ball.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ball.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBird) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isDart) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_wave.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_wave.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_wave.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_wave.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isRobot) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_robot.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_robot.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_robot.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_robot.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSpider) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_spider.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_spider.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_spider.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_spider.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSwing) {
            int col1 = settings->m_overrides[CGC_PLAYER_INDEX].m_swing.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_swing.primary  : settings->m_defaultColor;
            int col2 = settings->m_overrides[CGC_PLAYER_INDEX].m_swing.enabled ? settings->m_overrides[CGC_PLAYER_INDEX].m_swing.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        // change the tiny cube color inside the ship and ufo
        if ((this->m_isBird || this->m_isShip) && settings->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled && settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube) {
            this->m_iconSprite->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_cube.primary));
            this->m_iconSpriteSecondary->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_cube.secondary));
        }
    }
};

class $modify(PlayLayer) {
    void onQuit() {
        PlayLayer::onQuit();

        // whenever we quit a level, reset the gameManager player colors (else they'll reflect the last icon override)
        auto gameManager = GameManager::get();
        auto settings = Settings::sharedInstance();
        gameManager->m_playerColor = settings->m_defaultColor;
        gameManager->m_playerColor2 = settings->m_defaultColor2;
    }
};

// TODO: fixme (this is inlined everywhere?)
/*
class $modify(GameManager) {
    void setPlayerColor(int id) {
        Settings::sharedInstance()->m_defaultColor = id;
        GameManager::setPlayerColor(id);
    }
};
*/