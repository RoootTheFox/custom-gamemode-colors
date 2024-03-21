#include "include.hpp"

using namespace geode::prelude;

$execute {
	auto mod = Mod::get();

	// initialize settings (please don't stab me)
	auto settings = Settings::sharedInstance();

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
			log::error("failed to migrate data: {}", saved.error());
		}
	} else {
		log::info("data format up to date !");
	}

	settings->m_cube_override = mod->getSavedValue<ColorOverride>(CUBE_OVERRIDE, ColorOverride {});
	settings->m_ship_override = mod->getSavedValue<ColorOverride>(SHIP_OVERRIDE, ColorOverride {});
	settings->m_ball_override = mod->getSavedValue<ColorOverride>(BALL_OVERRIDE, ColorOverride {});
	settings->m_ufo_override = mod->getSavedValue<ColorOverride>(UFO_OVERRIDE, ColorOverride {});
	settings->m_wave_override = mod->getSavedValue<ColorOverride>(WAVE_OVERRIDE, ColorOverride {});
	settings->m_robot_override = mod->getSavedValue<ColorOverride>(ROBOT_OVERRIDE, ColorOverride {});
	settings->m_spider_override = mod->getSavedValue<ColorOverride>(SPIDER_OVERRIDE, ColorOverride {});
	settings->m_swing_override = mod->getSavedValue<ColorOverride>(SWING_OVERRIDE, ColorOverride {});

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

#ifdef GEODE_MACOS
	log::info("patching playSpiderEffect !");
	auto mod = Mod::get();
	mod->patch(reinterpret_cast<void*>(geode::base::get() + 0x3efa14), {0x66, 0xe9, 0xba, 0x00});
#endif
}