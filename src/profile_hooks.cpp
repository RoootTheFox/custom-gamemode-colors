#include <Geode/modify/ProfilePage.hpp>
#include <Geode/Geode.hpp>
#include "settings.hpp"

using namespace geode::prelude;

class $modify(ProfilePage) {
    virtual void loadPageFromUserInfo(GJUserScore* score) {
        log::debug("loadPageFromUserInfo");
        ProfilePage::loadPageFromUserInfo(score);

        if(!score->isCurrentUser()) return;

        auto gameManager = GameManager::sharedState();
        auto settings = Settings::sharedInstance();

        auto player_menu = this->m_mainLayer->getChildByID("player-menu");

        if (player_menu == nullptr) {
            log::error("player_menu is null");
            return;
        }

        if (settings->m_override_cube) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-icon")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_cube_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_cube_override.secondary));
        }
        if (settings->m_override_ship) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ship")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_ship_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_ship_override.secondary));            
        }
        if (settings->m_override_ball) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ball")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_ball_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_ball_override.secondary));            
        }
        if (settings->m_override_ufo) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ufo")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_ufo_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_ufo_override.secondary));            
        }
        if (settings->m_override_wave) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-wave")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_wave_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_wave_override.secondary));            
        }
        if (settings->m_override_robot) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-robot")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_robot_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_robot_override.secondary));            
        }
        if (settings->m_override_spider) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-spider")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_spider_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_spider_override.secondary));            
        }
        if (settings->m_override_swing) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-swing")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_swing_override.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_swing_override.secondary));            
        }
    }
};