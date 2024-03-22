#pragma once

#include "include.hpp"
#include "ui/CustomCharacterColorPage.hpp"

class Settings {
    public:
        int m_defaultColor;
        int m_defaultColor2;

        ColorOverride m_cube_override;
        ColorOverride m_ship_override;
        ColorOverride m_ball_override;
        ColorOverride m_ufo_override;
        ColorOverride m_wave_override;
        ColorOverride m_robot_override;
        ColorOverride m_spider_override;
        ColorOverride m_swing_override;

        bool m_override_cube;
        bool m_override_ship;
        bool m_override_ball;
        bool m_override_ufo;
        bool m_override_wave;
        bool m_override_robot;
        bool m_override_spider;
        bool m_override_swing;

        bool m_override_inner_cube;

        // not actual settings, but they're still needed
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

        GameMode m_current_mode = NONE;
        ColorType m_current_color_type = PRIMARY;

        geode::prelude::CCSprite* m_current_gamemode_sprite = nullptr;

        geode::prelude::CCSprite* m_current_color_primary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_secondary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_glow_sprite = nullptr;

        CCMenuItemSpriteExtra* m_button_primary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_secondary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_glow_color = nullptr;

        bool isOverrideEnabled(GameMode mode);

        void toggleOverride(GameMode mode);
        void setOverrideColor(GameMode mode, int color, ColorType type);

        static Settings* sharedInstance();
};