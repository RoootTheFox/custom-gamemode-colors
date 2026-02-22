#pragma once

#include <Geode/modify/CharacterColorPage.hpp>

#include "include.hpp"

using namespace geode::prelude;

class CustomCharacterColorPage : public CharacterColorPage {
protected:
    void onColorClicked(CCObject*);
    void onPlayerClicked(CCObject*);
    void onColorTypeButtonClicked(CCObject*);
    void onGameModeToggleButtonClicked(CCObject*);
    void onCubeInShipUfoToggleButtonClicked(CCObject*);
    void onP2Toggled(CCObject* sender);
    bool loadSimpsAndSelectionSprites();
    CCMenuItemSpriteExtra* createPlayerButton(SimplePlayer *player, GameMode game_mode);
    CCMenuItemSpriteExtra* createGameModeButton(GameMode game_mode, CCPoint position);
    void updateUI();
    void updateColorSelectionSprite(CCSprite* sprite, ColorType type);
    void updateGameModeSelectionSprite();
    CCPoint getPositionOfColor(int color_id);
    bool init(bool p2);

public:
    static CustomCharacterColorPage* create(bool p2 = false);
    static std::string getGameModeName(GameMode game_mode);
};
