#include "include.hpp"
#include "settings.hpp"

using namespace geode::prelude;

Settings* Settings::sharedInstance() {
    static auto instance = new Settings();
    return instance;
}

// if someone knows a way to make this less ugly and repetitive, please tell me i will love you forever
void Settings::setOverrideColor(GameMode mode, int color, ColorType type) {
    auto mod = Mod::get();

    switch (mode) {
        case CUBE:
            switch (type) {
                case PRIMARY:
                    this->m_cube_override = color;
                    mod->setSavedValue(CUBE_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_cube_override2 = color;
                    mod->setSavedValue(CUBE_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SHIP:
            switch (type) {
                case PRIMARY:
                    this->m_ship_override = color;
                    mod->setSavedValue(SHIP_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_ship_override2 = color;
                    mod->setSavedValue(SHIP_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case BALL:
            switch (type) {
                case PRIMARY:
                    this->m_ball_override = color;
                    mod->setSavedValue(BALL_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_ball_override2 = color;
                    mod->setSavedValue(BALL_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case UFO:
            switch (type) {
                case PRIMARY:
                    this->m_bird_override = color;
                    mod->setSavedValue(UFO_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_bird_override2 = color;
                    mod->setSavedValue(UFO_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case WAVE:
            switch (type) {
                case PRIMARY:
                    this->m_dart_override = color;
                    mod->setSavedValue(WAVE_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_dart_override2 = color;
                    mod->setSavedValue(WAVE_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case ROBOT:
            switch (type) {
                case PRIMARY:
                    this->m_robot_override = color;
                    mod->setSavedValue(ROBOT_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_robot_override2 = color;
                    mod->setSavedValue(ROBOT_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SPIDER:
            switch (type) {
                case PRIMARY:
                    this->m_spider_override = color;
                    mod->setSavedValue(SPIDER_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_spider_override2 = color;
                    mod->setSavedValue(SPIDER_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SWING:
            switch (type) {
                case PRIMARY:
                    this->m_swing_override = color;
                    mod->setSavedValue(SWING_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_swing_override2 = color;
                    mod->setSavedValue(SWING_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Settings::toggleOverride(GameMode mode) {
    auto mod = Mod::get();

    switch (mode) {
        case CUBE:
            this->m_override_cube = !this->m_override_cube;
            mod->setSavedValue(OVERRIDE_CUBE_ENABLED, this->m_override_cube);
            break;
        case SHIP:
            this->m_override_ship = !this->m_override_ship;
            mod->setSavedValue(OVERRIDE_SHIP_ENABLED, this->m_override_ship);
            break;
        case BALL:
            this->m_override_ball = !this->m_override_ball;
            mod->setSavedValue(OVERRIDE_BALL_ENABLED, this->m_override_ball);
            break;
        case UFO:
            this->m_override_bird = !this->m_override_bird;
            mod->setSavedValue(OVERRIDE_UFO_ENABLED, this->m_override_bird);
            break;
        case WAVE:
            this->m_override_dart = !this->m_override_dart;
            mod->setSavedValue(OVERRIDE_WAVE_ENABLED, this->m_override_dart);
            break;
        case ROBOT:
            this->m_override_robot = !this->m_override_robot;
            mod->setSavedValue(OVERRIDE_ROBOT_ENABLED, this->m_override_robot);
            break;
        case SPIDER:
            this->m_override_spider = !this->m_override_spider;
            mod->setSavedValue(OVERRIDE_SPIDER_ENABLED, this->m_override_spider);
            break;
        case SWING:
            this->m_override_swing = !this->m_override_swing;
            mod->setSavedValue(OVERRIDE_SWING_ENABLED, this->m_override_swing);
            break;
        default:
            break;
    }
}