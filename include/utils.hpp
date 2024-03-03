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

#define CUBE_OVERRIDE_PRIMARY "cube_override"
#define CUBE_OVERRIDE_SECONDARY "cube_override2"

#define SHIP_OVERRIDE_PRIMARY "ship_override"
#define SHIP_OVERRIDE_SECONDARY "ship_override2"

#define BALL_OVERRIDE_PRIMARY "ball_override"
#define BALL_OVERRIDE_SECONDARY "ball_override2"

#define UFO_OVERRIDE_PRIMARY "ufo_override"
#define UFO_OVERRIDE_SECONDARY "ufo_override2"

#define WAVE_OVERRIDE_PRIMARY "wave_override"
#define WAVE_OVERRIDE_SECONDARY "wave_override2"

#define ROBOT_OVERRIDE_PRIMARY "robot_override"
#define ROBOT_OVERRIDE_SECONDARY "robot_override2"

#define SPIDER_OVERRIDE_PRIMARY "spider_override"
#define SPIDER_OVERRIDE_SECONDARY "spider_override2"

#define SWING_OVERRIDE_PRIMARY "swing_override"
#define SWING_OVERRIDE_SECONDARY "swing_override2"

#define OVERRIDE_CUBE_ENABLED "override_cube"
#define OVERRIDE_SHIP_ENABLED "override_ship"
#define OVERRIDE_BALL_ENABLED "override_ball"
#define OVERRIDE_UFO_ENABLED "override_ufo"
#define OVERRIDE_WAVE_ENABLED "override_wave"
#define OVERRIDE_ROBOT_ENABLED "override_robot"
#define OVERRIDE_SPIDER_ENABLED "override_spider"
#define OVERRIDE_SWING_ENABLED "override_swing"

#define TEXTURE_BUTTON_ENABLED "GJ_button_01.png"
#define TEXTURE_BUTTON_DISABLED "GJ_button_04.png"
#define TEXTURE_SELECTED_FRAME "GJ_select_001.png"
#define TEXTURE_PAINT_BUTTON "GJ_paintBtn_001.png"