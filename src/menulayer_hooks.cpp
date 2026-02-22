#include <Geode/modify/MenuLayer.hpp>

#include "state.hpp"
using namespace geode::prelude;

class $modify(MenuLayer) {
    struct Fields {
        bool overriden = false;
    };

    bool init() {
        // this is **TEMPORARY** - this will be removed once SDI doesn't hook setColor anymore (lmao)
        if (Loader::get()->isModLoaded("weebify.separate_dual_icons") && !m_fields->overriden) {
            for (Hook* h : Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getHooks()) {
                auto function_name = h->getDisplayName();
                if (function_name == "PlayerObject::setColor" || function_name == "PlayerObject::setSecondColor") {
                    auto res = h->disable();
                    if (res.isOk()) {
                        log::info("sdi hook for {} disabled !!", function_name);
                    } else {
                        log::error("failed to disable sdi hook for {}: {}", function_name, res.unwrapErr());
                    }
                }
            }

            m_fields->overriden = true;
        }

        return MenuLayer::init();
    }
};
