#pragma once

#include <Geode/modify/CharacterColorPage.hpp>

#include "include.hpp"

using namespace geode::prelude;

class CustomCharacterColorPage : public CharacterColorPage {
protected:
    void onColorClicked(CCObject*);

    void onPlayerClicked(CCObject*);

    bool loadSimpsIn(CCNode*);

    void close(CCObject*);

    CCMenuItemSpriteExtra* createPlayerButton(SimplePlayer *player, GameMode game_mode);

    void updatePlayerColors();
public:
    static CustomCharacterColorPage* customCreate();

    GameMode m_current_mode = NONE;
};