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

        // todo !!
        bool p2 = false;

        if (CGC_OVERRIDE_ENABLED(cube)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-icon")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_cube.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_cube.secondary));
        }
        if (CGC_OVERRIDE_ENABLED(ship)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ship")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ship.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ship.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(ball)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ball")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ball.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ball.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(ufo)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-ufo")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_ufo.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(wave)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-wave")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_wave.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_wave.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(robot)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-robot")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_robot.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_robot.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(spider)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-spider")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_spider.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_spider.secondary));            
        }
        if (CGC_OVERRIDE_ENABLED(swing)) {
            auto player = static_cast<SimplePlayer*>(player_menu->getChildByID("player-swing")->getChildren()->objectAtIndex(0));
            player->setColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_swing.primary));
            player->setSecondColor(gameManager->colorForIdx(settings->m_overrides[CGC_PLAYER_INDEX].m_swing.secondary));            
        }
    }
};