#include "include.hpp"
#include "settings.hpp"

using namespace geode::prelude;

Settings* Settings::sharedInstance() {
    static auto instance = new Settings();
    return instance;
}

// if someone knows a way to make this less ugly and repetitive, please tell me i will love you forever
void Settings::setOverrideColor(GameMode mode, int color, ColorType type, bool p2) {
    auto mod = Mod::get();

    bool valid_gamemode = true;

    switch (mode) {
        case CUBE:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_cube.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_cube.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_cube.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case SHIP:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ship.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ship.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ship.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case BALL:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ball.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ball.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ball.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case UFO:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ufo.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ufo.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_ufo.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case WAVE:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_wave.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_wave.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_wave.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case ROBOT:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_robot.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_robot.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_robot.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case SPIDER:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_spider.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_spider.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_spider.glow = color;
                    break;
                default:
                    break;
            }
            break;
        case SWING:
            switch (type) {
                case PRIMARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_swing.primary = color;
                    break;
                case SECONDARY:
                    this->m_overrides[CGC_PLAYER_INDEX].m_swing.secondary = color;
                    break;
                case GLOW:
                    this->m_overrides[CGC_PLAYER_INDEX].m_swing.glow = color;
                    break;
                default:
                    break;
            }
            break;
        default:
            // there's no gamemode set yet because the user didn't select one
            valid_gamemode = false;
            Notification::create("You didn't select a gamemode (click a sprite!)", NotificationIcon::Warning)->show();

            break;
    }

    this->save();

    if (valid_gamemode && !isOverrideEnabled(mode)) {
        Notification::create(
            fmt::format(" enable overrides for {} using\n the small buttons at the top!", CustomCharacterColorPage::getGameModeName(mode)),
            NotificationIcon::Warning
        )->show();
    }
}

bool Settings::isOverrideEnabled(GameMode mode, bool p2) {
    switch (mode) {
        case CUBE:
            return this->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled;
        case SHIP:
            return this->m_overrides[CGC_PLAYER_INDEX].m_ship.enabled;
        case BALL:
            return this->m_overrides[CGC_PLAYER_INDEX].m_ball.enabled;
        case UFO:
            return this->m_overrides[CGC_PLAYER_INDEX].m_ufo.enabled;
        case WAVE:
            return this->m_overrides[CGC_PLAYER_INDEX].m_wave.enabled;
        case ROBOT:
            return this->m_overrides[CGC_PLAYER_INDEX].m_robot.enabled;
        case SPIDER:
            return this->m_overrides[CGC_PLAYER_INDEX].m_spider.enabled;
        case SWING:
            return this->m_overrides[CGC_PLAYER_INDEX].m_swing.enabled;
        default:
            return false;
    }
}

void Settings::toggleOverride(GameMode mode, bool p2) {
    auto mod = Mod::get();

    switch (mode) {
        case CUBE:
            this->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_cube.enabled;
            break;
        case SHIP:
            this->m_overrides[CGC_PLAYER_INDEX].m_ship.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_ship.enabled;
            break;
        case BALL:
            this->m_overrides[CGC_PLAYER_INDEX].m_ball.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_ball.enabled;
            break;
        case UFO:
            this->m_overrides[CGC_PLAYER_INDEX].m_ufo.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_ufo.enabled;
            break;
        case WAVE:
            this->m_overrides[CGC_PLAYER_INDEX].m_wave.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_wave.enabled;
            break;
        case ROBOT:
            this->m_overrides[CGC_PLAYER_INDEX].m_robot.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_robot.enabled;
            break;
        case SPIDER:
            this->m_overrides[CGC_PLAYER_INDEX].m_spider.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_spider.enabled;
            break;
        case SWING:
            this->m_overrides[CGC_PLAYER_INDEX].m_swing.enabled = !this->m_overrides[CGC_PLAYER_INDEX].m_swing.enabled;
            break;
        default:
            break;
    }

    this->save();
}

void Settings::save() {
    auto mod = Mod::get();

    mod->setSavedValue<OverridePlayer>(P1_OVERRIDE, this->m_overrides[0]);
    mod->setSavedValue<OverridePlayer>(P2_OVERRIDE, this->m_overrides[1]);
}