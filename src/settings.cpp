#include "include.hpp"
#include "settings.hpp"

using namespace geode::prelude;

Settings* Settings::sharedInstance() {
    static auto instance = new Settings();
    return instance;
}

// if someone knows a way to make this less ugly and repetitive, please tell me i will love you forever
void Settings::setOverrideColor(GameMode mode, int color, ColorType type) {
    switch (mode) {
        case CUBE:
            switch (type) {
                case PRIMARY:
                    this->m_cube_override = color;
                    Mod::get()->setSavedValue(CUBE_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_cube_override2 = color;
                    Mod::get()->setSavedValue(CUBE_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SHIP:
            switch (type) {
                case PRIMARY:
                    this->m_ship_override = color;
                    Mod::get()->setSavedValue(SHIP_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_ship_override2 = color;
                    Mod::get()->setSavedValue(SHIP_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case BALL:
            switch (type) {
                case PRIMARY:
                    this->m_ball_override = color;
                    Mod::get()->setSavedValue(BALL_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_ball_override2 = color;
                    Mod::get()->setSavedValue(BALL_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case UFO:
            switch (type) {
                case PRIMARY:
                    this->m_bird_override = color;
                    Mod::get()->setSavedValue(UFO_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_bird_override2 = color;
                    Mod::get()->setSavedValue(UFO_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case WAVE:
            switch (type) {
                case PRIMARY:
                    this->m_dart_override = color;
                    Mod::get()->setSavedValue(WAVE_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_dart_override2 = color;
                    Mod::get()->setSavedValue(WAVE_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case ROBOT:
            switch (type) {
                case PRIMARY:
                    this->m_robot_override = color;
                    Mod::get()->setSavedValue(ROBOT_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_robot_override2 = color;
                    Mod::get()->setSavedValue(ROBOT_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SPIDER:
            switch (type) {
                case PRIMARY:
                    this->m_spider_override = color;
                    Mod::get()->setSavedValue(SPIDER_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_spider_override2 = color;
                    Mod::get()->setSavedValue(SPIDER_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        case SWING:
            switch (type) {
                case PRIMARY:
                    this->m_swing_override = color;
                    Mod::get()->setSavedValue(SWING_OVERRIDE_PRIMARY, color);
                    break;
                case SECONDARY:
                    this->m_swing_override2 = color;
                    Mod::get()->setSavedValue(SWING_OVERRIDE_SECONDARY, color);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
