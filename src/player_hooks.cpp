#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "state.hpp"

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
        auto state = State::sharedInstance();

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

        int col1 = state->m_defaultColor;
        int col2 = state->m_defaultColor2;

        if(isCube) {
            col1 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).primary   : state->m_defaultColor;
            col2 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).secondary : state->m_defaultColor2;
        }

        if(this->m_isShip) {
            col1 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).primary   : state->m_defaultColor;
            col2 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).secondary : state->m_defaultColor2;
        }

        if(this->m_isBall) {
            col1 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).primary   : state->m_defaultColor;
            col2 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).secondary : state->m_defaultColor2;
        }

        if(this->m_isBird) {
            col1 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).primary   : state->m_defaultColor;
            col2 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).secondary : state->m_defaultColor2;
        }

        if(this->m_isDart) {
            col1 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).primary   : state->m_defaultColor;
            col2 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).secondary : state->m_defaultColor2;
            this->m_waveTrail->setColor(gameManager->colorForIdx(col1)); // fix wave trail
        }

        if(this->m_isRobot) {
            col1 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).primary  : state->m_defaultColor;
            col2 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).secondary : state->m_defaultColor2;
        }

        if(this->m_isSpider) {
            col1 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).primary  : state->m_defaultColor;
            col2 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).secondary : state->m_defaultColor2;
        }

        if(this->m_isSwing) {
            col1 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).primary  : state->m_defaultColor;
            col2 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).secondary : state->m_defaultColor2;
        }

        auto real_col1 = gameManager->colorForIdx(col1);
        auto real_col2 = gameManager->colorForIdx(col2);
        this->setColor(real_col1);
        this->setSecondColor(real_col2);

        this->m_regularTrail->setColor(real_col1); // fix small trail/particles behind player#
        if (this->m_ghostTrail) this->m_ghostTrail->m_color = real_col1; // fix ghost ("enable trail" trigger) trail

        // change the tiny cube color inside the ship and ufo
        if ((this->m_isBird || this->m_isShip) && CGC_OVERRIDE(cube).enabled && state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube) {
            this->m_iconSprite->setColor(gameManager->colorForIdx(CGC_OVERRIDE(cube).primary));
            this->m_iconSpriteSecondary->setColor(gameManager->colorForIdx(CGC_OVERRIDE(cube).secondary));
        }
    }
};
