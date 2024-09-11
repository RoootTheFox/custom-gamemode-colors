#pragma once

enum GameMode : int {
    NONE = 0,
    CUBE = 1,
    SHIP = 2,
    BALL = 3,
    UFO = 4,
    WAVE = 5,
    ROBOT = 6,
    SPIDER = 7,
    SWING = 8,
};

enum ColorType : int {
    PRIMARY = 0,
    SECONDARY = 1,
    GLOW = 2, // will be supported in the future
};

struct ColorOverride {
    bool enabled = false;
    int primary = 0;
    int secondary = 0;
    int glow = 0;
};

template<>
struct matjson::Serialize<ColorOverride> {
    static ColorOverride from_json(matjson::Value const& value) {
        return ColorOverride {
            .enabled = value.contains("enabled") ? value["enabled"].as_bool() : false,
            .primary = value["primary"].as_int(),
            .secondary = value["secondary"].as_int(),
            .glow = value["glow"].as_int(),
        };
    }

    static matjson::Value to_json(ColorOverride const& value) {
        auto obj = matjson::Object();
        obj["enabled"] = value.enabled;
        obj["primary"] = value.primary;
        obj["secondary"] = value.secondary;
        obj["glow"] = value.glow;
        return obj;
    }

    // this is needed, else it'll just get ignored
    static bool is_json(const matjson::Value& value) {
        return true;
    }
};

// the _SECONDARY ones are deprecated and only exist to migrate old values
#define CUBE_OVERRIDE "cube_override"
#define CUBE_OVERRIDE_SECONDARY "cube_override2"

#define SHIP_OVERRIDE "ship_override"
#define SHIP_OVERRIDE_SECONDARY "ship_override2"

#define BALL_OVERRIDE "ball_override"
#define BALL_OVERRIDE_SECONDARY "ball_override2"

#define UFO_OVERRIDE "ufo_override"
#define UFO_OVERRIDE_SECONDARY "ufo_override2"

#define WAVE_OVERRIDE "wave_override"
#define WAVE_OVERRIDE_SECONDARY "wave_override2"

#define ROBOT_OVERRIDE "robot_override"
#define ROBOT_OVERRIDE_SECONDARY "robot_override2"

#define SPIDER_OVERRIDE "spider_override"
#define SPIDER_OVERRIDE_SECONDARY "spider_override2"

#define SWING_OVERRIDE "swing_override"
#define SWING_OVERRIDE_SECONDARY "swing_override2"

#define OVERRIDE_CUBE_ENABLED "override_cube"
#define OVERRIDE_SHIP_ENABLED "override_ship"
#define OVERRIDE_BALL_ENABLED "override_ball"
#define OVERRIDE_UFO_ENABLED "override_ufo"
#define OVERRIDE_WAVE_ENABLED "override_wave"
#define OVERRIDE_ROBOT_ENABLED "override_robot"
#define OVERRIDE_SPIDER_ENABLED "override_spider"
#define OVERRIDE_SWING_ENABLED "override_swing"

#define OVERRIDE_INNER_CUBE_ENABLED "override_inner_cube"

#define P1_OVERRIDE "player1_override"
#define P2_OVERRIDE "player2_override"

#define TEXTURE_BUTTON_ENABLED "GJ_button_01.png"
#define TEXTURE_BUTTON_DISABLED "GJ_button_04.png"
#define TEXTURE_SELECTED_FRAME "GJ_select_001.png"
#define TEXTURE_PAINT_BUTTON "GJ_paintBtn_001.png"

// funny macro hell :3
#define CGC_PLAYER_INDEX p2 ? 1 : 0
#define CGC_OVERRIDE_ENABLED(...) settings->m_overrides[CGC_PLAYER_INDEX].m_##__VA_ARGS__.enabled