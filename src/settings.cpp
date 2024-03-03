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
                    Mod::get()->setSavedValue("cube_override", color);
                    break;
                case SECONDARY:
                    this->m_cube_override2 = color;
                    Mod::get()->setSavedValue("cube_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case SHIP:
            switch (type) {
                case PRIMARY:
                    this->m_ship_override = color;
                    Mod::get()->setSavedValue("ship_override", color);
                    break;
                case SECONDARY:
                    this->m_ship_override2 = color;
                    Mod::get()->setSavedValue("ship_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case BALL:
            switch (type) {
                case PRIMARY:
                    this->m_ball_override = color;
                    Mod::get()->setSavedValue("ball_override", color);
                    break;
                case SECONDARY:
                    this->m_ball_override2 = color;
                    Mod::get()->setSavedValue("ball_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case UFO:
            switch (type) {
                case PRIMARY:
                    this->m_bird_override = color;
                    Mod::get()->setSavedValue("bird_override", color);
                    break;
                case SECONDARY:
                    this->m_bird_override2 = color;
                    Mod::get()->setSavedValue("bird_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case WAVE:
            switch (type) {
                case PRIMARY:
                    this->m_dart_override = color;
                    Mod::get()->setSavedValue("dart_override", color);
                    break;
                case SECONDARY:
                    this->m_dart_override2 = color;
                    Mod::get()->setSavedValue("dart_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case ROBOT:
            switch (type) {
                case PRIMARY:
                    this->m_robot_override = color;
                    Mod::get()->setSavedValue("robot_override", color);
                    break;
                case SECONDARY:
                    this->m_robot_override2 = color;
                    Mod::get()->setSavedValue("robot_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case SPIDER:
            switch (type) {
                case PRIMARY:
                    this->m_spider_override = color;
                    Mod::get()->setSavedValue("spider_override", color);
                    break;
                case SECONDARY:
                    this->m_spider_override2 = color;
                    Mod::get()->setSavedValue("spider_override2", color);
                    break;
                default:
                    break;
            }
            break;
        case SWING:
            switch (type) {
                case PRIMARY:
                    this->m_swing_override = color;
                    Mod::get()->setSavedValue("swing_override", color);
                    break;
                case SECONDARY:
                    this->m_swing_override2 = color;
                    Mod::get()->setSavedValue("swing_override2", color);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
