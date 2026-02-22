#include "ui/CustomCharacterColorPage.hpp"

using namespace geode::prelude;

CustomCharacterColorPage* CustomCharacterColorPage::create(bool p2) {
    auto ret = new CustomCharacterColorPage();
    if (ret->init(p2)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool CustomCharacterColorPage::init(bool p2) {
    if (!CharacterColorPage::init()) return false;

    setID("gamemode-colors-page"_spr);

    if (!m_buttonMenu) {
        log::error("didn't find color menu");
        return true;
    }
    auto state = State::sharedInstance();

    state->m_current_p2 = p2;

    // crash prevention :3
    // should technically do this for all other buttons too but
    // a: im lazy, and b: not needed for them as they're not used in updateUI()
    state->m_button_togglep2 = nullptr;

    int buttons_found = 0;

    for (auto node : CCArrayExt<CCNode*>(m_buttonMenu->getChildren())) {
        auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(node);
        if (!btn) continue;

        for (auto btnChild : CCArrayExt<CCNode*>(btn->getChildren())) {
            if (typeinfo_cast<ColorChannelSprite*>(btnChild)) {
                btn->setTarget(this, menu_selector(CustomCharacterColorPage::onColorClicked));
            }
            if (typeinfo_cast<ButtonSprite*>(btnChild)) {
                if (buttons_found > 2) {
                    // this is mainly here to remove the "Rand" button added by Capeling's randomizer mod
                    log::warn("found too many buttons, removing");
                    node->removeFromParentAndCleanup(true);
                    continue;
                }
                buttons_found++;
            }
        }
    }

    state->m_button_primary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("col1-button"));
    state->m_button_secondary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("col2-button"));
    state->m_button_glow_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("glow-button"));

    // what an ugly if statement
    if (state->m_button_primary_color == nullptr || state->m_button_secondary_color == nullptr || state->m_button_glow_color == nullptr) {
        log::error("DID NOT FIND ALL BUTTONS");
        return true;
    } else {
        state->m_button_primary_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
        state->m_button_secondary_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
        state->m_button_glow_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
    }

    // END
    // murder 2nd child from self if it exists (added by an icon hack mod, using it crashes the game)
    if (getChildrenCount() > 1) {
        removeChild(static_cast<CCNode*>(getChildren()->objectAtIndex(1)));
    }

    // gotta catch 'em all!
    if (loadSimpsAndSelectionSprites()) {
        // find the ship button BEFORE all other player buttons are added
        auto ship_player = findFirstChildRecursive<SimplePlayer>(m_buttonMenu, [](auto node) {
            return typeinfo_cast<SimplePlayer*>(node) != nullptr;
        });
        state->m_player_ship = ship_player;
        auto ship_button = typeinfo_cast<CCMenuItemSprite*>(ship_player->getParent());
        ship_button->setTag(SHIP);
        ship_button->setTarget(this, menu_selector(CustomCharacterColorPage::onPlayerClicked));

        // cube button
        auto cube_button = createPlayerButton(state->m_player_cube, CUBE);
        m_buttonMenu->addChild(cube_button);

        auto ball_button = createPlayerButton(state->m_player_ball, BALL);
        m_buttonMenu->addChild(ball_button);

        auto ufo_button = createPlayerButton(state->m_player_ufo, UFO);
        m_buttonMenu->addChild(ufo_button);

        auto wave_button = createPlayerButton(state->m_player_wave, WAVE);
        m_buttonMenu->addChild(wave_button);

        auto robot_button = createPlayerButton(state->m_player_robot, ROBOT);
        m_buttonMenu->addChild(robot_button);

        auto spider_button = createPlayerButton(state->m_player_spider, SPIDER);
        m_buttonMenu->addChild(spider_button);

        auto swing_button = createPlayerButton(state->m_player_swing, SWING);
        m_buttonMenu->addChild(swing_button);

        float button_width = 33.0f;
        auto cube_toggle_button = createGameModeButton(CUBE, {button_width, -7});
        m_buttonMenu->addChild(cube_toggle_button);

        auto ship_toggle_button = createGameModeButton(SHIP, {button_width * 2, -7});
        m_buttonMenu->addChild(ship_toggle_button);

        auto ball_toggle_button = createGameModeButton(BALL, {button_width * 3, -7});
        m_buttonMenu->addChild(ball_toggle_button);

        auto ufo_toggle_button = createGameModeButton(UFO, {button_width * 4, -7});
        m_buttonMenu->addChild(ufo_toggle_button);

        auto wave_toggle_button = createGameModeButton(WAVE, {button_width * 5, -7});
        m_buttonMenu->addChild(wave_toggle_button);

        auto robot_toggle_button = createGameModeButton(ROBOT, {button_width * 6, -7});
        m_buttonMenu->addChild(robot_toggle_button);

        auto spider_toggle_button = createGameModeButton(SPIDER, {button_width * 7, -7});
        m_buttonMenu->addChild(spider_toggle_button);

        auto swing_toggle_button = createGameModeButton(SWING, {button_width * 8, -7});
        m_buttonMenu->addChild(swing_toggle_button);

        // sprite to show current player
        auto current_gamemode_sprite = CCSprite::createWithSpriteFrameName(TEXTURE_SELECTED_FRAME);
        current_gamemode_sprite->setContentSize({32, 32});
        current_gamemode_sprite->setScale(1.15f);
        m_mainLayer->addChild(current_gamemode_sprite);
        state->m_current_gamemode_sprite = current_gamemode_sprite;

        updateUI();
    } else {
        log::error("failed to load icons and selection sprites (this should never happen)");
    }

    auto inner_button = ButtonSprite::create("color cube in ship/ufo", 77, true, "bigFont.fnt",
            state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED, 20.0f, 4.0f);
    auto button = CCMenuItemSpriteExtra::create(
        inner_button,
        this,
        menu_selector(CustomCharacterColorPage::onCubeInShipUfoToggleButtonClicked)
    );
    m_buttonMenu->addChild(button);
    button->setPosition({53.5f, -265});

    // 2p support without SDI
    if (!Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
        state->m_button_togglep2 = ButtonSprite::create(state->m_current_p2 ? "P2" : "P1", 22, true, "bigFont.fnt",
            TEXTURE_BUTTON_ENABLED, 20.0f, 4.0f);
        auto ass = CCMenuItemSpriteExtra::create(
            state->m_button_togglep2,
            this,
            menu_selector(CustomCharacterColorPage::onP2Toggled)
        );
        m_buttonMenu->addChild(ass);
        ass->setPosition({234.5f, -267});
    }

    updateUI(); // call AT END OF INIT !!!!!!!

    return true;
}

CCMenuItemSpriteExtra* CustomCharacterColorPage::createPlayerButton(SimplePlayer* player, GameMode game_mode) {
    auto player_pos = player->getParent()->convertToWorldSpaceAR(player->getPosition());
    player->removeFromParent();

    auto button = CCMenuItemSpriteExtra::create(
        player,
        this,
        menu_selector(CustomCharacterColorPage::onPlayerClicked)
    );
    button->setContentSize({30, 30});
    player->setPosition({15, 15});

    button->setPosition(this->m_buttonMenu->convertToNodeSpaceAR(player_pos));
    button->setTag(game_mode);

    return button;
}

CCMenuItemSpriteExtra* CustomCharacterColorPage::createGameModeButton(GameMode game_mode, CCPoint position) {
    auto inner_button = ButtonSprite::create(this->getGameModeName(game_mode).c_str(), 16, true, "bigFont.fnt", TEXTURE_BUTTON_ENABLED, 20.0f, 2.0f);
    auto button = CCMenuItemSpriteExtra::create(
        inner_button,
        this,
        menu_selector(CustomCharacterColorPage::onGameModeToggleButtonClicked)
    );

    switch (game_mode) {
        case CUBE:
            State::sharedInstance()->m_button_cube = inner_button;
            break;
        case SHIP:
            State::sharedInstance()->m_button_ship = inner_button;
            break;
        case BALL:
            State::sharedInstance()->m_button_ball = inner_button;
            break;
        case UFO:
            State::sharedInstance()->m_button_ufo = inner_button;
            break;
        case WAVE:
            State::sharedInstance()->m_button_wave = inner_button;
            break;
        case ROBOT:
            State::sharedInstance()->m_button_robot = inner_button;
            break;
        case SPIDER:
            State::sharedInstance()->m_button_spider = inner_button;
            break;
        case SWING:
            State::sharedInstance()->m_button_swing = inner_button;
            break;
        default:
            break;
    }

    auto state = State::sharedInstance();

    button->setTag(game_mode);
    button->setPosition(position);
    return button;
}

bool CustomCharacterColorPage::loadSimpsAndSelectionSprites() {
    auto meow = this->m_mainLayer;
    auto state = State::sharedInstance();

    state->m_player_cube = typeinfo_cast<SimplePlayer*>(meow->getChildByID("cube-icon"));
    state->m_player_ball = typeinfo_cast<SimplePlayer*>(meow->getChildByID("ball-icon"));
    state->m_player_ufo = typeinfo_cast<SimplePlayer*>(meow->getChildByID("ufo-icon"));
    state->m_player_wave = typeinfo_cast<SimplePlayer*>(meow->getChildByID("wave-icon"));
    state->m_player_robot = typeinfo_cast<SimplePlayer*>(meow->getChildByID("robot-icon"));
    state->m_player_spider = typeinfo_cast<SimplePlayer*>(meow->getChildByID("spider-icon"));
    state->m_player_swing = typeinfo_cast<SimplePlayer*>(meow->getChildByID("swing-icon"));

    state->m_current_color_primary_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-col1"));
    state->m_current_color_secondary_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-col2"));
    state->m_current_color_glow_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-glow"));

    // yeah this is ugly
    if (!state->m_player_cube || !state->m_player_ball || !state->m_player_ufo || !state->m_player_wave
            || !state->m_player_robot || !state->m_player_spider || !state->m_player_swing) {
        log::error("failed to find all simps");
        return false;
    }

    if (!state->m_current_color_primary_sprite || !state->m_current_color_secondary_sprite || !state->m_current_color_glow_sprite) {
        log::error("failed to find all selection sprites");
        return false;
    }

    return true;
}

void CustomCharacterColorPage::updateUI() {
    auto state = State::sharedInstance();
    auto gameManager = GameManager::get();
    bool p2 = state->m_current_p2;

    if(state->m_player_cube) {
        int col1 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).glow      : state->m_defaultColorGlow;

        state->m_player_cube->setColor(gameManager->colorForIdx(col1));
        state->m_player_cube->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_cube->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_ship) {
        int col1 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).glow      : state->m_defaultColorGlow;

        state->m_player_ship->setColor(gameManager->colorForIdx(col1));
        state->m_player_ship->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_ship->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_ball) {
        int col1 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).glow      : state->m_defaultColorGlow;

        state->m_player_ball->setColor(gameManager->colorForIdx(col1));
        state->m_player_ball->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_ball->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_ufo) {
        int col1 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).glow      : state->m_defaultColorGlow;

        state->m_player_ufo->setColor(gameManager->colorForIdx(col1));
        state->m_player_ufo->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_ufo->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_wave) {
        int col1 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).glow      : state->m_defaultColorGlow;

        state->m_player_wave->setColor(gameManager->colorForIdx(col1));
        state->m_player_wave->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_wave->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_robot) {
        int col1 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).glow      : state->m_defaultColorGlow;

        state->m_player_robot->setColor(gameManager->colorForIdx(col1));
        state->m_player_robot->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_robot->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_spider) {
        int col1 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).glow      : state->m_defaultColorGlow;

        state->m_player_spider->setColor(gameManager->colorForIdx(col1));
        state->m_player_spider->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_spider->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_player_swing) {
        int col1 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).primary   : state->m_defaultColor;
        int col2 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).secondary : state->m_defaultColor2;
        int colg = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).glow      : state->m_defaultColorGlow;

        state->m_player_swing->setColor(gameManager->colorForIdx(col1));
        state->m_player_swing->setSecondColor(gameManager->colorForIdx(col2));

        if (gameManager->m_playerGlow) state->m_player_swing->setGlowOutline(gameManager->colorForIdx(colg));
    }

    if(state->m_current_color_primary_sprite) {
        if (state->m_current_mode == NONE) {
            state->m_current_color_primary_sprite->setVisible(false);
        } else {
            this->updateColorSelectionSprite(state->m_current_color_primary_sprite, PRIMARY);
        }
    }

    if(state->m_current_color_secondary_sprite) {
        if (state->m_current_mode == NONE) {
            state->m_current_color_secondary_sprite->setVisible(false);
        } else {
            this->updateColorSelectionSprite(state->m_current_color_secondary_sprite, SECONDARY);
        }
    }

    if(state->m_current_color_glow_sprite) {
        if (state->m_current_mode == NONE) {
            state->m_current_color_glow_sprite->setVisible(false);
        } else {
            this->updateColorSelectionSprite(state->m_current_color_glow_sprite, GLOW);
        }
    }

    if (state->m_button_cube) {
        state->m_button_cube->updateBGImage(CGC_OVERRIDE(cube).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_ship) {
        state->m_button_ship->updateBGImage(CGC_OVERRIDE(ship).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_ball) {
        state->m_button_ball->updateBGImage(CGC_OVERRIDE(ball).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_ufo) {
        state->m_button_ufo->updateBGImage(CGC_OVERRIDE(ufo).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_wave) {
        state->m_button_wave->updateBGImage(CGC_OVERRIDE(wave).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_robot) {
        state->m_button_robot->updateBGImage(CGC_OVERRIDE(robot).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_spider) {
        state->m_button_spider->updateBGImage(CGC_OVERRIDE(spider).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (state->m_button_swing) {
        state->m_button_swing->updateBGImage(CGC_OVERRIDE(swing).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (state->m_current_gamemode_sprite) {
        this->updateGameModeSelectionSprite();
    }

    if (state->m_garage_layer) {
        state->m_garage_layer->updatePlayerColors();
    }

    if (state->m_button_togglep2) {
        state->m_button_togglep2->setString(p2 ? "P2" : "P1");
    }
}

void CustomCharacterColorPage::updateColorSelectionSprite(CCSprite* sprite, ColorType type) {
    auto state = State::sharedInstance();
    bool p2 = state->m_current_p2;

    int color = 0;

    switch (state->m_current_mode) {
        case CUBE:
        color = type == PRIMARY ? CGC_OVERRIDE(cube).primary : (type == SECONDARY ? CGC_OVERRIDE(cube).secondary : CGC_OVERRIDE(cube).glow);
            break;
        case SHIP:
            color = type == PRIMARY ? CGC_OVERRIDE(ship).primary : (type == SECONDARY ? CGC_OVERRIDE(ship).secondary : CGC_OVERRIDE(ship).glow);
            break;
        case BALL:
            color = type == PRIMARY ? CGC_OVERRIDE(ball).primary : (type == SECONDARY ? CGC_OVERRIDE(ball).secondary : CGC_OVERRIDE(ball).glow);
            break;
        case UFO:
            color = type == PRIMARY ? CGC_OVERRIDE(ufo).primary : (type == SECONDARY ? CGC_OVERRIDE(ufo).secondary : CGC_OVERRIDE(ufo).glow);
            break;
        case WAVE:
            color = type == PRIMARY ? CGC_OVERRIDE(wave).primary : (type == SECONDARY ? CGC_OVERRIDE(wave).secondary : CGC_OVERRIDE(wave).glow);
            break;
        case ROBOT:
            color = type == PRIMARY ? CGC_OVERRIDE(robot).primary : (type == SECONDARY ? CGC_OVERRIDE(robot).secondary : CGC_OVERRIDE(robot).glow);
            break;
        case SPIDER:
            color = type == PRIMARY ? CGC_OVERRIDE(spider).primary : (type == SECONDARY ? CGC_OVERRIDE(spider).secondary : CGC_OVERRIDE(spider).glow);
            break;
        case SWING:
            color = type == PRIMARY ? CGC_OVERRIDE(swing).primary : (type == SECONDARY ? CGC_OVERRIDE(swing).secondary : CGC_OVERRIDE(swing).glow);
            break;
        default:
            break;
    }

    if (type != state->m_current_color_type) {
        sprite->setColor(ccc3(50, 50, 50));
    } else {
        sprite->setColor(ccc3(255, 255, 255));
    }

    auto target_pos = this->m_mainLayer->convertToNodeSpaceAR(this->getPositionOfColor(color));
    sprite->setPosition(target_pos);
    sprite->setVisible(true);
}

void CustomCharacterColorPage::updateGameModeSelectionSprite() {
    auto state = State::sharedInstance();

    auto sprite = state->m_current_gamemode_sprite;
    if (state->m_current_mode == NONE) {
        sprite->setVisible(false);
        return;
    } else {
        sprite->setVisible(true);
    }

    SimplePlayer* player = nullptr;

    switch (state->m_current_mode) {
        case CUBE:
            player = state->m_player_cube;
            break;
        case SHIP:
            player = state->m_player_ship;
            break;
        case BALL:
            player = state->m_player_ball;
            break;
        case UFO:
            player = state->m_player_ufo;
            break;
        case WAVE:
            player = state->m_player_wave;
            break;
        case ROBOT:
            player = state->m_player_robot;
            break;
        case SPIDER:
            player = state->m_player_spider;
            break;
        case SWING:
            player = state->m_player_swing;
            break;
        default:
            break;
    }

    if (!player) {
        log::error("failed to find player for current mode");
        return;
    }

    // all simpleplayers (except ship) are initially children of m_mainLayer,
    // but since we moved them to buttons inside the menu, we need to convert the position

    auto pos = this->m_mainLayer->convertToNodeSpaceAR(this->m_buttonMenu->convertToWorldSpaceAR(player->getParent()->getPosition()));

    // pos is slightly off, so we need to fix it
    auto fixed_pos = ccpAdd(pos, ccp(-3.5, -3));

    sprite->setPosition(fixed_pos);
}

CCPoint CustomCharacterColorPage::getPositionOfColor(int color_id) {
    auto child = findFirstChildRecursive<CCMenuItemSpriteExtra>(this->m_buttonMenu, [color_id](auto node) {
        return typeinfo_cast<ColorChannelSprite*>(node->getChildren()->objectAtIndex(0)) && node->getTag() == color_id;
    });
    if (!child) {
        log::error("failed to find child with tag: {}", color_id);
        return {0, 0};
    } else {
        return this->m_buttonMenu->convertToWorldSpaceAR(child->getPosition());
    }
}

void CustomCharacterColorPage::onColorClicked(CCObject* sender) {
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }
    int tag = node->getTag();

    auto state = State::sharedInstance();

    state->setOverrideColor(state->m_current_mode, tag, state->m_current_color_type, state->m_current_p2);

    this->updateUI();
}

void CustomCharacterColorPage::onPlayerClicked(CCObject* sender) {
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }
    int tag = node->getTag();

    if (tag < 1 || tag > 8) {
        log::error("invalid tag: {}", tag);
        return;
    }

    State::sharedInstance()->m_current_mode = static_cast<GameMode>(tag);

    this->updateUI();
}

void CustomCharacterColorPage::onColorTypeButtonClicked(CCObject* sender) {
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }
    int tag = node->getTag();

    if (tag < 0 || tag > 2) {
        log::error("invalid tag: {}", tag);
        return;
    }

    auto state = State::sharedInstance();

    state->m_current_color_type = static_cast<ColorType>(tag);

    // set buttons
    auto type = state->m_current_color_type;
    static_cast<ButtonSprite*>(state->m_button_primary_color->getChildren()->objectAtIndex(0))->updateBGImage(type == PRIMARY ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    static_cast<ButtonSprite*>(state->m_button_secondary_color->getChildren()->objectAtIndex(0))->updateBGImage(type == SECONDARY ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    static_cast<ButtonSprite*>(state->m_button_glow_color->getChildren()->objectAtIndex(0))->updateBGImage(type == GLOW ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);

    this->updateUI();
}

void CustomCharacterColorPage::onGameModeToggleButtonClicked(CCObject* sender) {
    int tag = sender->getTag();

    if (tag < 1 || tag > 8) {
        log::error("invalid tag: {}", tag);
        return;
    }

    auto game_mode = static_cast<GameMode>(tag);

    auto state = State::sharedInstance();
    state->toggleOverride(game_mode, state->m_current_p2);
    updateUI();
}

void CustomCharacterColorPage::onCubeInShipUfoToggleButtonClicked(CCObject* sender) {
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }

    // todo !!
    bool p2 = false;

    auto state = State::sharedInstance();
    state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube = !state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube;
    Mod::get()->setSavedValue(OVERRIDE_INNER_CUBE_ENABLED, state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube);

    if (auto button = typeinfo_cast<ButtonSprite*>(node->getChildren()->objectAtIndex(0))) {
        button->updateBGImage(state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (state->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube) {
        Notification::create("cube in ship/ufo enabled", NotificationIcon::Success)->show();
    } else {
        Notification::create("cube in ship/ufo disabled", NotificationIcon::Success)->show();
    }
}

void CustomCharacterColorPage::onP2Toggled(CCObject* sender) {
    log::info("toggling p2");
    auto state = State::sharedInstance();
    state->m_current_p2 = !state->m_current_p2;

    this->updateUI();
}

// todo: move this to a utils class
std::string CustomCharacterColorPage::getGameModeName(GameMode mode) {
    switch (mode) {
        case CUBE:
            return "cube";
        case SHIP:
            return "ship";
        case BALL:
            return "ball";
        case UFO:
            return "ufo";
        case WAVE:
            return "wave";
        case ROBOT:
            return "robot";
        case SPIDER:
            return "spider";
        case SWING:
            return "swing";
        default:
            return "none";
    }
}
