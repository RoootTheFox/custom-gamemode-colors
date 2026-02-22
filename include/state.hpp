#pragma once

#include "include.hpp"
#include "ui/CustomCharacterColorPage.hpp"
#include <Geode/Result.hpp>

struct OverridePlayer {
    ColorOverride m_cube;
    ColorOverride m_ship;
    ColorOverride m_ball;
    ColorOverride m_ufo;
    ColorOverride m_wave;
    ColorOverride m_robot;
    ColorOverride m_spider;
    ColorOverride m_swing;

    bool m_override_inner_cube;
};

template<>
struct matjson::Serialize<OverridePlayer> {
    static geode::Result<OverridePlayer> fromJson(matjson::Value const& value) {
        return geode::Ok(OverridePlayer {
            .m_cube = GEODE_UNWRAP(value["cube"].as<ColorOverride>()),
            .m_ship = GEODE_UNWRAP(value["ship"].as<ColorOverride>()),
            .m_ball = GEODE_UNWRAP(value["ball"].as<ColorOverride>()),
            .m_ufo = GEODE_UNWRAP(value["ufo"].as<ColorOverride>()),
            .m_wave = GEODE_UNWRAP(value["wave"].as<ColorOverride>()),
            .m_robot = GEODE_UNWRAP(value["robot"].as<ColorOverride>()),
            .m_spider = GEODE_UNWRAP(value["spider"].as<ColorOverride>()),
            .m_swing = GEODE_UNWRAP(value["swing"].as<ColorOverride>()),
            .m_override_inner_cube = GEODE_UNWRAP(value["override_inner_cube"].asBool()),
        });
    }

    static matjson::Value toJson(OverridePlayer const& value) {
        auto obj = matjson::Value();
        obj["cube"] = value.m_cube;
        obj["ship"] = value.m_ship;
        obj["ball"] = value.m_ball;
        obj["ufo"] = value.m_ufo;
        obj["wave"] = value.m_wave;
        obj["robot"] = value.m_robot;
        obj["spider"] = value.m_spider;
        obj["swing"] = value.m_swing;
        obj["override_inner_cube"] = value.m_override_inner_cube;
        return obj;
    }

    // this is needed, else it'll just get ignored
    static bool is_json(const matjson::Value& value) {
        return true;
    }
};

class State {
    public:
        int m_defaultColor;
        int m_defaultColor2;

        // overrides for each player
        OverridePlayer m_overrides[2] = {};

        // in-memory state
        SimplePlayer* m_player_cube;
        SimplePlayer* m_player_ship;
        SimplePlayer* m_player_ball;
        SimplePlayer* m_player_ufo;
        SimplePlayer* m_player_wave;
        SimplePlayer* m_player_robot;
        SimplePlayer* m_player_spider;
        SimplePlayer* m_player_swing;

        ButtonSprite* m_button_cube = nullptr;
        ButtonSprite* m_button_ship = nullptr;
        ButtonSprite* m_button_ball = nullptr;
        ButtonSprite* m_button_ufo = nullptr;
        ButtonSprite* m_button_wave = nullptr;
        ButtonSprite* m_button_robot = nullptr;
        ButtonSprite* m_button_spider = nullptr;
        ButtonSprite* m_button_swing = nullptr;

        ButtonSprite* m_button_togglep2 = nullptr;

        GameMode m_current_mode = NONE;
        ColorType m_current_color_type = PRIMARY;
        bool m_current_p2 = false;

        geode::Ref<GJGarageLayer> m_garage_layer = nullptr;

        geode::prelude::CCSprite* m_current_gamemode_sprite = nullptr;

        geode::prelude::CCSprite* m_current_color_primary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_secondary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_glow_sprite = nullptr;

        CCMenuItemSpriteExtra* m_button_primary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_secondary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_glow_color = nullptr;

        bool isOverrideEnabled(GameMode mode, bool p2);

        void toggleOverride(GameMode mode, bool p2);
        void setOverrideColor(GameMode mode, int color, ColorType type, bool p2);

        void save();

        static State* sharedInstance();
};
