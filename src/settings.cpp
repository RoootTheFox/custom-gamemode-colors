#include "include.hpp"

using namespace geode::prelude;

Settings* Settings::sharedInstance() {
    static auto instance = new Settings();
    return instance;
}

void Settings::setOverrideCube(bool value) {
    this->m_override_cube = value;
    Mod::get()->setSavedValue("override_cube", value);
}