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
            CGC_SETTINGS_SET_OVERRIDE(cube, type, color);
            break;
        case SHIP:
            CGC_SETTINGS_SET_OVERRIDE(ship, type, color);
            break;
        case BALL:
            CGC_SETTINGS_SET_OVERRIDE(ball, type, color);
            break;
        case UFO:
            CGC_SETTINGS_SET_OVERRIDE(ufo, type, color);
            break;
        case WAVE:
            CGC_SETTINGS_SET_OVERRIDE(wave, type, color);
            break;
        case ROBOT:
            CGC_SETTINGS_SET_OVERRIDE(robot, type, color);
            break;
        case SPIDER:
            CGC_SETTINGS_SET_OVERRIDE(spider, type, color);
            break;
        case SWING:
            CGC_SETTINGS_SET_OVERRIDE(swing, type, color);
            break;
        default:
            // there's no gamemode set yet because the user didn't select one
            valid_gamemode = false;
            Notification::create("You didn't select a gamemode (click a sprite!)", NotificationIcon::Warning)->show();

            break;
    }

    this->save();

    if (valid_gamemode && !isOverrideEnabled(mode, p2)) {
        Notification::create(
            fmt::format(" enable overrides for {} using\n the small buttons at the top!", CustomCharacterColorPage::getGameModeName(mode)),
            NotificationIcon::Warning
        )->show();
    }
}

bool Settings::isOverrideEnabled(GameMode mode, bool p2) {
    switch (mode) {
        case CUBE:
            return CGC_OVERRIDE_THIS(cube).enabled;
        case SHIP:
            return CGC_OVERRIDE_THIS(ship).enabled;
        case BALL:
            return CGC_OVERRIDE_THIS(ball).enabled;
        case UFO:
            return CGC_OVERRIDE_THIS(ufo).enabled;
        case WAVE:
            return CGC_OVERRIDE_THIS(wave).enabled;
        case ROBOT:
            return CGC_OVERRIDE_THIS(robot).enabled;
        case SPIDER:
            return CGC_OVERRIDE_THIS(spider).enabled;
        case SWING:
            return CGC_OVERRIDE_THIS(swing).enabled;
        default:
            return false;
    }
}

void Settings::toggleOverride(GameMode mode, bool p2) {
    auto mod = Mod::get();

    switch (mode) {
        case CUBE:
            CGC_OVERRIDE_THIS(cube).enabled = !CGC_OVERRIDE_THIS(cube).enabled;
            break;
        case SHIP:
            CGC_OVERRIDE_THIS(ship).enabled = !CGC_OVERRIDE_THIS(ship).enabled;
            break;
        case BALL:
            CGC_OVERRIDE_THIS(ball).enabled = !CGC_OVERRIDE_THIS(ball).enabled;
            break;
        case UFO:
            CGC_OVERRIDE_THIS(ufo).enabled = !CGC_OVERRIDE_THIS(ufo).enabled;
            break;
        case WAVE:
            CGC_OVERRIDE_THIS(wave).enabled = !CGC_OVERRIDE_THIS(wave).enabled;
            break;
        case ROBOT:
            CGC_OVERRIDE_THIS(robot).enabled = !CGC_OVERRIDE_THIS(robot).enabled;
            break;
        case SPIDER:
            CGC_OVERRIDE_THIS(spider).enabled = !CGC_OVERRIDE_THIS(spider).enabled;
            break;
        case SWING:
            CGC_OVERRIDE_THIS(swing).enabled = !CGC_OVERRIDE_THIS(swing).enabled;
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
