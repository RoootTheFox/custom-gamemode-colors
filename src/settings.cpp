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
                    this->m_cube_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_cube_override.secondary = color;
                    break;
                case GLOW:
                    this->m_cube_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(CUBE_OVERRIDE, this->m_cube_override);
            break;
        case SHIP:
            switch (type) {
                case PRIMARY:
                    this->m_ship_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_ship_override.secondary = color;
                    break;
                case GLOW:
                    this->m_ship_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(SHIP_OVERRIDE, this->m_ship_override);
            break;
        case BALL:
            switch (type) {
                case PRIMARY:
                    this->m_ball_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_ball_override.secondary = color;
                    break;
                case GLOW:
                    this->m_ball_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(BALL_OVERRIDE, this->m_ball_override);
            break;
        case UFO:
            switch (type) {
                case PRIMARY:
                    this->m_ufo_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_ufo_override.secondary = color;
                    break;
                case GLOW:
                    this->m_ufo_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(UFO_OVERRIDE, this->m_ufo_override);
            break;
        case WAVE:
            switch (type) {
                case PRIMARY:
                    this->m_wave_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_wave_override.secondary = color;
                    break;
                case GLOW:
                    this->m_wave_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(WAVE_OVERRIDE, this->m_wave_override);
            break;
        case ROBOT:
            switch (type) {
                case PRIMARY:
                    this->m_robot_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_robot_override.secondary = color;
                    break;
                case GLOW:
                    this->m_robot_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(ROBOT_OVERRIDE, this->m_robot_override);
            break;
        case SPIDER:
            switch (type) {
                case PRIMARY:
                    this->m_spider_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_spider_override.secondary = color;
                    break;
                case GLOW:
                    this->m_spider_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(SPIDER_OVERRIDE, this->m_spider_override);
            break;
        case SWING:
            switch (type) {
                case PRIMARY:
                    this->m_swing_override.primary = color;
                    break;
                case SECONDARY:
                    this->m_swing_override.secondary = color;
                    break;
                case GLOW:
                    this->m_swing_override.glow = color;
                    break;
                default:
                    break;
            }
            mod->setSavedValue(SWING_OVERRIDE, this->m_swing_override);
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
            this->m_override_ufo = !this->m_override_ufo;
            mod->setSavedValue(OVERRIDE_UFO_ENABLED, this->m_override_ufo);
            break;
        case WAVE:
            this->m_override_wave = !this->m_override_wave;
            mod->setSavedValue(OVERRIDE_WAVE_ENABLED, this->m_override_wave);
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