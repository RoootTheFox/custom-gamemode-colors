#include "include.hpp"

using namespace geode::prelude;

$execute {
	fmt::print("nya !\n");

	auto mod = Mod::get();

	// i deadass forgot what this was for lmao
	auto _ = mod->patch(reinterpret_cast<void*>(base::get() + 0x2c3ebf), { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });

	// initialize settings (please don't stab me)
	auto settings = Settings::sharedInstance();

	settings->m_cube_override = mod->getSavedValue<int>("cube_override", 0);
	settings->m_cube_override2 = mod->getSavedValue<int>("cube_override2", 0);

	settings->m_ship_override = mod->getSavedValue<int>("ship_override", 0);
	settings->m_ship_override2 = mod->getSavedValue<int>("ship_override2", 0);

	settings->m_ball_override = mod->getSavedValue<int>("ball_override", 0);
	settings->m_ball_override2 = mod->getSavedValue<int>("ball_override2", 0);

	settings->m_bird_override = mod->getSavedValue<int>("bird_override", 0);
	settings->m_bird_override2 = mod->getSavedValue<int>("bird_override2", 0);

	settings->m_dart_override = mod->getSavedValue<int>("dart_override", 0);
	settings->m_dart_override2 = mod->getSavedValue<int>("dart_override2", 0);

	settings->m_robot_override = mod->getSavedValue<int>("robot_override", 0);
	settings->m_robot_override2 = mod->getSavedValue<int>("robot_override2", 0);

	settings->m_spider_override = mod->getSavedValue<int>("spider_override", 0);
	settings->m_spider_override2 = mod->getSavedValue<int>("spider_override2", 0);

	settings->m_swing_override = mod->getSavedValue<int>("swing_override", 0);
	settings->m_swing_override2 = mod->getSavedValue<int>("swing_override2", 0);

	settings->m_override_cube = mod->getSavedValue<bool>("override_cube", false);
	settings->m_override_ship = mod->getSavedValue<bool>("override_ship", false);
	settings->m_override_ball = mod->getSavedValue<bool>("override_ball", false);
	settings->m_override_bird = mod->getSavedValue<bool>("override_bird", false);
	settings->m_override_dart = mod->getSavedValue<bool>("override_dart", false);
	settings->m_override_robot = mod->getSavedValue<bool>("override_robot", false);
	settings->m_override_spider = mod->getSavedValue<bool>("override_spider", false);
	settings->m_override_swing = mod->getSavedValue<bool>("override_swing", false);

	fmt::println("(START) override_cube: {}", settings->m_override_cube);
}

$on_mod(Loaded) {
	log::info("mod loaded");
	auto gameManager = GameManager::get();

	Settings* settings = Settings::sharedInstance();
	settings->m_defaultColor = gameManager->m_playerColor;
	settings->m_defaultColor2 = gameManager->m_playerColor2;
}