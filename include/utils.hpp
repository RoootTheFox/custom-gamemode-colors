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