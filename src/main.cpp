#include "include.hpp"
#include <Geode/modify/MenuLayer.hpp>
#include <chrono>

using namespace geode::prelude;

class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
		FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show(); 
	} 
};

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

	auto t1 = std::chrono::high_resolution_clock::now();
    gameManager->colorForIdx(0);
    gameManager->colorForIdx(1);
    gameManager->colorForIdx(2);
    gameManager->colorForIdx(3);
    gameManager->colorForIdx(4);
    gameManager->colorForIdx(5);
    gameManager->colorForIdx(6);
    gameManager->colorForIdx(7);
    gameManager->colorForIdx(8);
    gameManager->colorForIdx(9);
    gameManager->colorForIdx(11);
    gameManager->colorForIdx(12);
    gameManager->colorForIdx(13);
    gameManager->colorForIdx(14);
	gameManager->colorForIdx(15);
	gameManager->colorForIdx(16);
	gameManager->colorForIdx(17);
	gameManager->colorForIdx(18);
	gameManager->colorForIdx(19);
	gameManager->colorForIdx(20);
	gameManager->colorForIdx(21);
	gameManager->colorForIdx(22);
	gameManager->colorForIdx(23);
	gameManager->colorForIdx(24);
	gameManager->colorForIdx(25);
	gameManager->colorForIdx(26);
	gameManager->colorForIdx(27);
	gameManager->colorForIdx(28);
	gameManager->colorForIdx(29);
	gameManager->colorForIdx(30);
	gameManager->colorForIdx(31);
	gameManager->colorForIdx(32);
	gameManager->colorForIdx(33);
	gameManager->colorForIdx(34);
	gameManager->colorForIdx(35);
	gameManager->colorForIdx(36);
	gameManager->colorForIdx(37);
	gameManager->colorForIdx(38);
	gameManager->colorForIdx(39);
	gameManager->colorForIdx(40);
	gameManager->colorForIdx(41);
	gameManager->colorForIdx(42);
	gameManager->colorForIdx(43);
	gameManager->colorForIdx(44);
	gameManager->colorForIdx(45);
	gameManager->colorForIdx(46);
	gameManager->colorForIdx(47);
	gameManager->colorForIdx(48);
	gameManager->colorForIdx(49);
	gameManager->colorForIdx(50);
	gameManager->colorForIdx(51);
	gameManager->colorForIdx(52);
	gameManager->colorForIdx(53);
	gameManager->colorForIdx(54);
	gameManager->colorForIdx(55);
	gameManager->colorForIdx(56);
	gameManager->colorForIdx(57);
	gameManager->colorForIdx(58);
	gameManager->colorForIdx(59);
	gameManager->colorForIdx(60);
	gameManager->colorForIdx(61);
	gameManager->colorForIdx(62);
	gameManager->colorForIdx(63);
	gameManager->colorForIdx(64);
	gameManager->colorForIdx(65);
	gameManager->colorForIdx(66);
	gameManager->colorForIdx(67);
	gameManager->colorForIdx(68);
	gameManager->colorForIdx(69);
	gameManager->colorForIdx(70);
	gameManager->colorForIdx(71);
	gameManager->colorForIdx(72);
	gameManager->colorForIdx(73);
	gameManager->colorForIdx(74);
	gameManager->colorForIdx(75);
	gameManager->colorForIdx(76);
	gameManager->colorForIdx(77);
	gameManager->colorForIdx(78);
	gameManager->colorForIdx(79);
	gameManager->colorForIdx(80);
	gameManager->colorForIdx(81);
	gameManager->colorForIdx(82);
	gameManager->colorForIdx(83);
	gameManager->colorForIdx(84);
	gameManager->colorForIdx(85);
	gameManager->colorForIdx(86);
	gameManager->colorForIdx(87);
	gameManager->colorForIdx(88);
	gameManager->colorForIdx(89);
	gameManager->colorForIdx(90);
	gameManager->colorForIdx(91);
	gameManager->colorForIdx(92);
	gameManager->colorForIdx(93);
	gameManager->colorForIdx(94);
	gameManager->colorForIdx(95);
	gameManager->colorForIdx(96);
	gameManager->colorForIdx(97);
	gameManager->colorForIdx(98);
	gameManager->colorForIdx(99);

    auto t2 = std::chrono::high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ns_int = duration_cast<std::chrono::nanoseconds>(t2 - t1);

	log::info("colorForIdx calls took {}ns", ns_int.count());
}