#include "include.hpp"

using namespace geode::prelude;

$execute {
	auto mod = Mod::get();

	// initialize settings (please don't stab me)
	auto settings = Settings::sharedInstance();

	settings->m_cube_override = mod->getSavedValue<int>(CUBE_OVERRIDE_PRIMARY, 0);
	settings->m_cube_override2 = mod->getSavedValue<int>(CUBE_OVERRIDE_SECONDARY, 0);

	settings->m_ship_override = mod->getSavedValue<int>(SHIP_OVERRIDE_PRIMARY, 0);
	settings->m_ship_override2 = mod->getSavedValue<int>(SHIP_OVERRIDE_SECONDARY, 0);

	settings->m_ball_override = mod->getSavedValue<int>(BALL_OVERRIDE_PRIMARY, 0);
	settings->m_ball_override2 = mod->getSavedValue<int>(BALL_OVERRIDE_SECONDARY, 0);

	settings->m_ufo_override = mod->getSavedValue<int>(UFO_OVERRIDE_PRIMARY, 0);
	settings->m_ufo_override2 = mod->getSavedValue<int>(UFO_OVERRIDE_SECONDARY, 0);

	settings->m_wave_override = mod->getSavedValue<int>(WAVE_OVERRIDE_PRIMARY, 0);
	settings->m_wave_override2 = mod->getSavedValue<int>(WAVE_OVERRIDE_SECONDARY, 0);

	settings->m_robot_override = mod->getSavedValue<int>(ROBOT_OVERRIDE_PRIMARY, 0);
	settings->m_robot_override2 = mod->getSavedValue<int>(ROBOT_OVERRIDE_SECONDARY, 0);

	settings->m_spider_override = mod->getSavedValue<int>(SPIDER_OVERRIDE_PRIMARY, 0);
	settings->m_spider_override2 = mod->getSavedValue<int>(SPIDER_OVERRIDE_SECONDARY, 0);

	settings->m_swing_override = mod->getSavedValue<int>(SWING_OVERRIDE_PRIMARY, 0);
	settings->m_swing_override2 = mod->getSavedValue<int>(SWING_OVERRIDE_SECONDARY, 0);

	settings->m_override_cube = mod->getSavedValue<bool>(OVERRIDE_CUBE_ENABLED, false);
	settings->m_override_ship = mod->getSavedValue<bool>(OVERRIDE_SHIP_ENABLED, false);
	settings->m_override_ball = mod->getSavedValue<bool>(OVERRIDE_BALL_ENABLED, false);
	settings->m_override_ufo = mod->getSavedValue<bool>(OVERRIDE_UFO_ENABLED, false);
	settings->m_override_wave = mod->getSavedValue<bool>(OVERRIDE_WAVE_ENABLED, false);
	settings->m_override_robot = mod->getSavedValue<bool>(OVERRIDE_ROBOT_ENABLED, false);
	settings->m_override_spider = mod->getSavedValue<bool>(OVERRIDE_SPIDER_ENABLED, false);
	settings->m_override_swing = mod->getSavedValue<bool>(OVERRIDE_SWING_ENABLED, false);
}

$on_mod(Loaded) {
	log::info("mod loaded");
	auto gameManager = GameManager::get();

	Settings* settings = Settings::sharedInstance();
	settings->m_defaultColor = gameManager->m_playerColor;
	settings->m_defaultColor2 = gameManager->m_playerColor2;
}