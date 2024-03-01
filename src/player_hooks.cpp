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

    void updatePlayerFrame(int p0) {
        PlayerObject::updatePlayerFrame(p0);
        //log::info("updatePlayerFrame {}", p0);

        meow();
    }

    void updatePlayerBirdFrame(int p0) {
        PlayerObject::updatePlayerBirdFrame(p0);
        //log::info("updatePlayerBirdFrame {}", p0);

        meow();
    }

    void updatePlayerDartFrame(int p0) {
        PlayerObject::updatePlayerDartFrame(p0);
        //log::info("updatePlayerDartFrame {}", p0);

        meow();
    }

    void updatePlayerShipFrame(int p0) {
        PlayerObject::updatePlayerShipFrame(p0);
        //log::info("updatePlayerShipFrame {}", p0);

        meow();
    }

    void updatePlayerRollFrame(int p0) {
        PlayerObject::updatePlayerRollFrame(p0);
        //log::info("updatePlayerRollFrame {}", p0);

        meow();
    }

    // this doesn't get called for some reason lmao
    void updatePlayerRobotFrame(int p0) {
        PlayerObject::updatePlayerRobotFrame(p0);
        //log::info("updatePlayerRobotFrame {}", p0);

        meow();
    }

    void updatePlayerSwingFrame(int p0) {
        PlayerObject::updatePlayerSwingFrame(p0);
        //log::info("updatePlayerSwingFrame {}", p0);

        meow();
    }

    void updatePlayerJetpackFrame(int p0) {
        PlayerObject::updatePlayerJetpackFrame(p0);
        //log::info("updatePlayerJetpackFrame {}", p0);

        meow();
    }

    void updatePlayerSpiderFrame(int p0) {
        PlayerObject::updatePlayerSpiderFrame(p0);
        //log::info("updatePlayerSpiderFrame {}", p0);

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

    void meow() {
        auto gameManager = GameManager::get();
        auto settings = Settings::sharedInstance();

        // only run on playlayer
        if (gameManager->m_playLayer == nullptr) return;

        bool isCube = !this->m_isShip && !this->m_isBall && !this->m_isBird && !this->m_isDart && !this->m_isRobot && !this->m_isSpider && !this->m_isSwing;

        if(isCube) {
            log::debug("cube");
            int col1 = settings->m_override_cube ? settings->m_cube_override  : settings->m_defaultColor;
            int col2 = settings->m_override_cube ? settings->m_cube_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }
        
        if(this->m_isShip) {
            log::debug("ship");
            int col1 = settings->m_override_ship ? settings->m_ship_override  : settings->m_defaultColor;
            int col2 = settings->m_override_ship ? settings->m_ship_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBall) {
            log::debug("ball");
            int col1 = settings->m_override_ball ? settings->m_ball_override  : settings->m_defaultColor;
            int col2 = settings->m_override_ball ? settings->m_ball_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isBird) {
            log::debug("bird");
            int col1 = settings->m_override_bird ? settings->m_bird_override  : settings->m_defaultColor;
            int col2 = settings->m_override_bird ? settings->m_bird_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isDart) {
            log::debug("dart");
            int col1 = settings->m_override_dart ? settings->m_dart_override  : settings->m_defaultColor;
            int col2 = settings->m_override_dart ? settings->m_dart_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isRobot) {
            log::debug("robot");
            int col1 = settings->m_override_robot ? settings->m_robot_override  : settings->m_defaultColor;
            int col2 = settings->m_override_robot ? settings->m_robot_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSpider) {
            log::debug("spider");
            int col1 = settings->m_override_spider ? settings->m_spider_override  : settings->m_defaultColor;
            int col2 = settings->m_override_spider ? settings->m_spider_override2 : settings->m_defaultColor2;

            log::debug("colors: {} {}", col1, col2);

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }

        if(this->m_isSwing) {
            log::debug("swing");
            int col1 = settings->m_override_swing ? settings->m_swing_override  : settings->m_defaultColor;
            int col2 = settings->m_override_swing ? settings->m_swing_override2 : settings->m_defaultColor2;

            this->setColor(gameManager->colorForIdx(col1));
            this->setSecondColor(gameManager->colorForIdx(col2));
            gameManager->m_playerColor = col1;
            gameManager->m_playerColor2 = col2;
        }
    }
};

class $modify(PlayLayer) {
    void onQuit() {
        log::debug("PlayLayer::onQuit");
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
        log::debug("GameManager::setPlayerColor");

        Settings::sharedInstance()->m_defaultColor = id;
        log::debug("-> color: {} ({})", GameManager::colorForIdx(id), id);
        GameManager::setPlayerColor(id);
    }
};