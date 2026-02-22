#include <Geode/modify/ProfilePage.hpp>
#include <Geode/Geode.hpp>
#include "state.hpp"

using namespace geode::prelude;

class $modify(ProfilePage) {
    virtual void loadPageFromUserInfo(GJUserScore* score) {
        log::debug("loadPageFromUserInfo");
        ProfilePage::loadPageFromUserInfo(score);

        if(!score->isCurrentUser()) return;

        auto gameManager = GameManager::sharedState();
        auto state = State::sharedInstance();

        auto player_menu = this->m_mainLayer->getChildByID("player-menu");

        if (player_menu == nullptr) {
            log::error("player_menu is null");
            return;
        }

        // todo !!
        bool p2 = false;

        if (CGC_OVERRIDE(cube).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-icon")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(cube).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(cube).secondary));
        }
        if (CGC_OVERRIDE(ship).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ship")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(ship).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(ship).secondary));
        }
        if (CGC_OVERRIDE(ball).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ball")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(ball).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(ball).secondary));
        }
        if (CGC_OVERRIDE(ufo).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ufo")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(ufo).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(ufo).secondary));
        }
        if (CGC_OVERRIDE(wave).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-wave")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(wave).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(wave).secondary));
        }
        if (CGC_OVERRIDE(robot).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-robot")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(robot).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(robot).secondary));
        }
        if (CGC_OVERRIDE(spider).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-spider")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(spider).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(spider).secondary));
        }
        if (CGC_OVERRIDE(swing).enabled) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-swing")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(CGC_OVERRIDE(swing).primary));
            player->setSecondColor(gameManager->colorForIdx(CGC_OVERRIDE(swing).secondary));
        }
    }
};
