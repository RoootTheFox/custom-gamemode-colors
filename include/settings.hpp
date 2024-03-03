#pragma once

#include "include.hpp"

class Settings {
    public:
        int m_defaultColor;
        int m_defaultColor2;

        int m_cube_override;
        int m_ship_override;
        int m_ball_override;
        int m_bird_override;
        int m_dart_override;
        int m_robot_override;
        int m_spider_override;
        int m_swing_override;

        int m_cube_override2;
        int m_ship_override2;
        int m_ball_override2;
        int m_bird_override2;
        int m_dart_override2;
        int m_robot_override2;
        int m_spider_override2;
        int m_swing_override2;

        bool m_override_cube;
        bool m_override_ship;
        bool m_override_ball;
        bool m_override_bird;
        bool m_override_dart;
        bool m_override_robot;
        bool m_override_spider;
        bool m_override_swing;

        // not actual settings, but they're still needed
        SimplePlayer* m_player_cube;
        SimplePlayer* m_player_ship;
        SimplePlayer* m_player_ball;
        SimplePlayer* m_player_bird;
        SimplePlayer* m_player_dart;
        SimplePlayer* m_player_robot;
        SimplePlayer* m_player_spider;
        SimplePlayer* m_player_swing;

        GameMode m_current_mode = NONE;
        ColorType m_current_color_type = PRIMARY;

        geode::prelude::CCSprite* m_current_color_primary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_secondary_sprite = nullptr;
        geode::prelude::CCSprite* m_current_color_glow_sprite = nullptr;

        CCMenuItemSpriteExtra* m_button_primary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_secondary_color = nullptr;
        CCMenuItemSpriteExtra* m_button_glow_color = nullptr;

        void setOverrideEnabled(GameMode mode, bool value);
        void setOverrideColor(GameMode mode, int color, ColorType type);

        static Settings* sharedInstance();
};