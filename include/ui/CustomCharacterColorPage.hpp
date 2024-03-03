#pragma once

#include <Geode/modify/CharacterColorPage.hpp>

#include "include.hpp"

using namespace geode::prelude;

class CustomCharacterColorPage : public CharacterColorPage {
protected:
    void onColorClicked(CCObject*);

    void onPlayerClicked(CCObject*);

    void onColorTypeButtonClicked(CCObject*);

    bool loadSimpsAndSelectionSprites();

    void close(CCObject*);

    CCMenuItemSpriteExtra* createPlayerButton(SimplePlayer *player, GameMode game_mode);

    void updatePlayerColors();

    void updateColorSelectionSprite(CCSprite* sprite, ColorType type);

    CCPoint getPositionOfColor(int color_id);
public:
    static CustomCharacterColorPage* customCreate();
};