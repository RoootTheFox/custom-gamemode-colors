using namespace geode::prelude;

#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "settings.hpp"

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

    void updatePlayerSpiderFrame(int p0) {
        PlayerObject::updatePlayerSpiderFrame(p0);

        meow();
    }

    void updatePlayerArt() {
        PlayerObject::updatePlayerArt();
        //log::info("updatePlayerArt");

        meow();
    }

    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
        if(!PlayerObject::init(p0, p1, p2, p3, p4)) return false;
        //log::info("init");

        meow();
        return true;
    }

    void flashPlayer(float p0, float p1, cocos2d::ccColor3B mainColor, cocos2d::ccColor3B secondColor) {
        // make flashPlayer do nothing.
        // flashPlayer sets the players color back to the original color. TODO: RE flashPlayer
        // to figure out how to fix this.
    }

    TodoReturn flipGravity(bool p0, bool p1) {
        meow();
        return PlayerObject::flipGravity(p0, p1);
    }

    void meow() {
        auto gameManager = GameManager::get();
        auto settings = Settings::sharedInstance();

        auto play_layer = gameManager->m_playLayer;

        // only run on playlayer
        if (play_layer == nullptr) return;

        // this will also be used for proper dual color support later
        bool is_p1 = this == play_layer->m_player1;
        bool is_p2 = this == play_layer->m_player2;

        // fix issues with globed
        if (!(is_p1 || is_p2)) {
            return;
        }

        bool isCube = !this->m_isShip && !this->m_isBall && !this->m_isBird && !this->m_isDart && !this->m_isRobot && !this->m_isSpider && !this->m_isSwing;

        if(isCube) {
            int col1 = settings->m_override_cube ? settings->m_cube_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_cube ? settings->m_cube_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }
        
        if(this->m_isShip) {
            int col1 = settings->m_override_ship ? settings->m_ship_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_ship ? settings->m_ship_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBall) {
            int col1 = settings->m_override_ball ? settings->m_ball_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_ball ? settings->m_ball_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBird) {
            int col1 = settings->m_override_ufo ? settings->m_ufo_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_ufo ? settings->m_ufo_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isDart) {
            int col1 = settings->m_override_wave ? settings->m_wave_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_wave ? settings->m_wave_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isRobot) {
            int col1 = settings->m_override_robot ? settings->m_robot_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_robot ? settings->m_robot_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSpider) {
            int col1 = settings->m_override_spider ? settings->m_spider_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_spider ? settings->m_spider_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSwing) {
            int col1 = settings->m_override_swing ? settings->m_swing_override.primary  : settings->m_defaultColor;
            int col2 = settings->m_override_swing ? settings->m_swing_override.secondary : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        // change the tiny cube color inside the ship and ufo
        if ((this->m_isBird || this->m_isShip) && settings->m_override_cube) {
            this->m_iconSprite->setColor(gameManager->colorForIdx(settings->m_cube_override.primary));
            this->m_iconSpriteSecondary->setColor(gameManager->colorForIdx(settings->m_cube_override.secondary));
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

class $modify(GameManager) {
    void setPlayerColor(int id) {
        Settings::sharedInstance()->m_defaultColor = id;
        GameManager::setPlayerColor(id);
    }
};