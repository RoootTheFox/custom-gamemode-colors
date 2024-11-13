#include "include.hpp"

using namespace geode::prelude;

$execute {
	auto mod = Mod::get();

	// initialize settings (please don't stab me)
	auto settings = Settings::sharedInstance();

	// legacy migration (v0)
	if (mod->getSavedValue<int>("format", 0) == 0) {
		log::info("data format outdated, migrating !");

		// glow isn't implemented yet so we're just gonna set it to 0

		ColorOverride cube_override = {
			.primary = mod->getSavedValue<int>(CUBE_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(CUBE_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};
		
		ColorOverride ship_override = {
			.primary = mod->getSavedValue<int>(SHIP_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(SHIP_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride ball_override = {
			.primary = mod->getSavedValue<int>(BALL_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(BALL_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride ufo_override = {
			.primary = mod->getSavedValue<int>(UFO_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(UFO_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride wave_override = {
			.primary = mod->getSavedValue<int>(WAVE_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(WAVE_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride robot_override = {
			.primary = mod->getSavedValue<int>(ROBOT_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(ROBOT_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride spider_override = {
			.primary = mod->getSavedValue<int>(SPIDER_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(SPIDER_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		ColorOverride swing_override = {
			.primary = mod->getSavedValue<int>(SWING_OVERRIDE, 0),
			.secondary = mod->getSavedValue<int>(SWING_OVERRIDE_SECONDARY, 0),
			.glow = 0,
		};

		log::info("saving new values !");

		// erase old values
		mod->getSaveContainer().erase(CUBE_OVERRIDE);
		mod->getSaveContainer().erase(SHIP_OVERRIDE);
		mod->getSaveContainer().erase(BALL_OVERRIDE);
		mod->getSaveContainer().erase(UFO_OVERRIDE);
		mod->getSaveContainer().erase(WAVE_OVERRIDE);
		mod->getSaveContainer().erase(ROBOT_OVERRIDE);
		mod->getSaveContainer().erase(SPIDER_OVERRIDE);
		mod->getSaveContainer().erase(SWING_OVERRIDE);
		mod->getSaveContainer().erase(CUBE_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(SHIP_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(BALL_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(UFO_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(WAVE_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(ROBOT_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(SPIDER_OVERRIDE_SECONDARY);
		mod->getSaveContainer().erase(SWING_OVERRIDE_SECONDARY);

		mod->setSavedValue<ColorOverride>(CUBE_OVERRIDE, cube_override);
		mod->setSavedValue<ColorOverride>(SHIP_OVERRIDE, ship_override);
		mod->setSavedValue<ColorOverride>(BALL_OVERRIDE, ball_override);
		mod->setSavedValue<ColorOverride>(UFO_OVERRIDE, ufo_override);
		mod->setSavedValue<ColorOverride>(WAVE_OVERRIDE, wave_override);
		mod->setSavedValue<ColorOverride>(ROBOT_OVERRIDE, robot_override);
		mod->setSavedValue<ColorOverride>(SPIDER_OVERRIDE, spider_override);
		mod->setSavedValue<ColorOverride>(SWING_OVERRIDE, swing_override);
		
		mod->setSavedValue<int>("format", 1);

		auto saved = mod->saveData();
		if (saved.isOk()) {
			log::info("data migrated to format 1 !");
		} else {
			log::error("failed to migrate data: {}", saved.unwrapErr());
		}
	}
	
	// migrate to format 2
	if (mod->getSavedValue<int>("format", 0) == 1) {
		log::info("data format outdated, migrating (1 -> 2)!");

		// glow isn't implemented yet so we're just gonna set it to 0

		ColorOverride cube_override = mod->getSavedValue<ColorOverride>(CUBE_OVERRIDE, ColorOverride {});
		ColorOverride ship_override = mod->getSavedValue<ColorOverride>(SHIP_OVERRIDE, ColorOverride {});
		ColorOverride ball_override = mod->getSavedValue<ColorOverride>(BALL_OVERRIDE, ColorOverride {});
		ColorOverride ufo_override = mod->getSavedValue<ColorOverride>(UFO_OVERRIDE, ColorOverride {});
		ColorOverride wave_override = mod->getSavedValue<ColorOverride>(WAVE_OVERRIDE, ColorOverride {});
		ColorOverride robot_override = mod->getSavedValue<ColorOverride>(ROBOT_OVERRIDE, ColorOverride {});
		ColorOverride spider_override = mod->getSavedValue<ColorOverride>(SPIDER_OVERRIDE, ColorOverride {});
		ColorOverride swing_override = mod->getSavedValue<ColorOverride>(SWING_OVERRIDE, ColorOverride {});

		cube_override.enabled = mod->getSavedValue<bool>(OVERRIDE_CUBE_ENABLED, false);
		ship_override.enabled = mod->getSavedValue<bool>(OVERRIDE_SHIP_ENABLED, false);
		ball_override.enabled = mod->getSavedValue<bool>(OVERRIDE_BALL_ENABLED, false);
		ufo_override.enabled = mod->getSavedValue<bool>(OVERRIDE_UFO_ENABLED, false);
		wave_override.enabled = mod->getSavedValue<bool>(OVERRIDE_WAVE_ENABLED, false);
		robot_override.enabled = mod->getSavedValue<bool>(OVERRIDE_ROBOT_ENABLED, false);
		spider_override.enabled = mod->getSavedValue<bool>(OVERRIDE_SPIDER_ENABLED, false);
		swing_override.enabled = mod->getSavedValue<bool>(OVERRIDE_SWING_ENABLED, false);

		bool override_inner_cube = mod->getSavedValue<bool>(OVERRIDE_INNER_CUBE_ENABLED, true);

		OverridePlayer player_override = {
			.m_cube = cube_override,
			.m_ship = ship_override,
			.m_ball = ball_override,
			.m_ufo = ufo_override,
			.m_wave = wave_override,
			.m_robot = robot_override,
			.m_spider = spider_override,
			.m_swing = swing_override,
			.m_override_inner_cube = override_inner_cube,
		};

		log::info("saving new values !");

		// erase old values
		mod->getSaveContainer().erase(CUBE_OVERRIDE);
		mod->getSaveContainer().erase(SHIP_OVERRIDE);
		mod->getSaveContainer().erase(BALL_OVERRIDE);
		mod->getSaveContainer().erase(UFO_OVERRIDE);
		mod->getSaveContainer().erase(WAVE_OVERRIDE);
		mod->getSaveContainer().erase(ROBOT_OVERRIDE);
		mod->getSaveContainer().erase(SPIDER_OVERRIDE);
		mod->getSaveContainer().erase(SWING_OVERRIDE);
		mod->getSaveContainer().erase(OVERRIDE_CUBE_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_SHIP_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_BALL_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_UFO_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_WAVE_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_ROBOT_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_SPIDER_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_SWING_ENABLED);
		mod->getSaveContainer().erase(OVERRIDE_INNER_CUBE_ENABLED);

		mod->setSavedValue<OverridePlayer>(P1_OVERRIDE, player_override);
		mod->setSavedValue<OverridePlayer>(P2_OVERRIDE, player_override);

		mod->setSavedValue<int>("format", 2);

		auto saved = mod->saveData();
		if (saved.isOk()) {
			log::info("data migrated to format 2 !");
		} else {
			log::error("failed to migrate data: {}", saved.unwrapErr());
		}
	} else {
		log::info("data format up to date !");
	}

	// load players
	settings->m_overrides[0] = mod->getSavedValue<OverridePlayer>("player1_override", OverridePlayer {});
	settings->m_overrides[1] = mod->getSavedValue<OverridePlayer>("player2_override", OverridePlayer {});
}

$on_mod(Loaded) {
	log::info("mod loaded");
	auto gameManager = GameManager::get();

	Settings* settings = Settings::sharedInstance();
	settings->m_defaultColor = gameManager->m_playerColor;
	settings->m_defaultColor2 = gameManager->m_playerColor2;
#if defined(GEODE_IS_MACOS) && false
	static_assert(GEODE_COMP_GD_VERSION == 22000, "Mod needs to target 2.200 on mac"); // thanks to cvolton for this (misc bugfixes) <3

	// thank you dankmeme for telling me what function flashPlayer is inlined in <3
	log::info("running on macOS ~ patching out inlined flashPlayer calls !");

	auto mod = Mod::get();

	// --- playSpiderEffect patch ---
	// MOV        byte ptr [RBX + 0x7e2],0xff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa1b), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        word ptr [RBX + 0x7e0],0xffff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa22), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        byte ptr [RBX + 0x7e5],0xff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa32), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        word ptr [RBX + 0x7e3],0xffff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa39), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa48), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa5b), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa6e), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       GJRobotSprite::updateColor02
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa8e), {0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       GJRobotSprite::updateColor02
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efaad), {0x90, 0x90, 0x90, 0x90, 0x90});
	// MOVSD      qword ptr [RBX + 0x7d0],XMM0
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efaba), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOVSD      qword ptr [RBX + 0x7d8],XMM0
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efaca), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// --- end of playSpiderEffect patch ---
	// --- startDashing patch ---
	// MOV        byte ptr [RBX + 0x7e2],0xff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2b9a), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        word ptr [RBX + 0x7e0],0xffff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2ba1), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        byte ptr [RBX + 0x7e5],0xff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2bb1), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOV        word ptr [RBX + 0x7e3],0xffff
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2bb8), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2bc7), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2bda), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       qword ptr [RAX + 0x3b0]
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2bed), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       GJRobotSprite::updateColor02
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2c0d), {0x90, 0x90, 0x90, 0x90, 0x90});
	// CALL       GJRobotSprite::updateColor02
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2c2c), {0x90, 0x90, 0x90, 0x90, 0x90});
	// MOVSD      qword ptr [RBX + 0x7d0],XMM0
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2c39), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
	// MOVSD      qword ptr [RBX + 0x7d8],XMM0
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3f2c49), {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90});
#endif
}