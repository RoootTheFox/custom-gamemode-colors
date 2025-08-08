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
    auto settings = Settings::sharedInstance();

    settings->m_current_p2 = p2;

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

    settings->m_button_primary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("col1-button"));
    settings->m_button_secondary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("col2-button"));
    settings->m_button_glow_color = typeinfo_cast<CCMenuItemSpriteExtra*>(m_buttonMenu->getChildByID("glow-button"));

    // what an ugly if statement
    if (settings->m_button_primary_color == nullptr || settings->m_button_secondary_color == nullptr || settings->m_button_glow_color == nullptr) {
        log::error("DID NOT FIND ALL BUTTONS");
        return true;
    } else {
        settings->m_button_primary_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
        settings->m_button_secondary_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
        settings->m_button_glow_color->setTarget(this, menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked));
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
        settings->m_player_ship = ship_player;
        auto ship_button = typeinfo_cast<CCMenuItemSprite*>(ship_player->getParent());
        ship_button->setTag(SHIP);
        ship_button->setTarget(this, menu_selector(CustomCharacterColorPage::onPlayerClicked));

        // cube button
        auto cube_button = createPlayerButton(settings->m_player_cube, CUBE);
        m_buttonMenu->addChild(cube_button);

        auto ball_button = createPlayerButton(settings->m_player_ball, BALL);
        m_buttonMenu->addChild(ball_button);

        auto ufo_button = createPlayerButton(settings->m_player_ufo, UFO);
        m_buttonMenu->addChild(ufo_button);

        auto wave_button = createPlayerButton(settings->m_player_wave, WAVE);
        m_buttonMenu->addChild(wave_button);

        auto robot_button = createPlayerButton(settings->m_player_robot, ROBOT);
        m_buttonMenu->addChild(robot_button);

        auto spider_button = createPlayerButton(settings->m_player_spider, SPIDER);
        m_buttonMenu->addChild(spider_button);

        auto swing_button = createPlayerButton(settings->m_player_swing, SWING);
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
        settings->m_current_gamemode_sprite = current_gamemode_sprite;

        updateUI();
    } else {
        log::error("failed to load icons and selection sprites (this should never happen)");
    }

    auto inner_button = ButtonSprite::create("color cube in ship/ufo", 77, true, "bigFont.fnt",
            settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED, 20.0f, 4.0f);
    auto button = CCMenuItemSpriteExtra::create(
        inner_button,
        this,
        menu_selector(CustomCharacterColorPage::onCubeInShipUfoToggleButtonClicked)
    );
    m_buttonMenu->addChild(button);
    button->setPosition({53.5f, -265});

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
            Settings::sharedInstance()->m_button_cube = inner_button;
            break;
        case SHIP:
            Settings::sharedInstance()->m_button_ship = inner_button;
            break;
        case BALL:
            Settings::sharedInstance()->m_button_ball = inner_button;
            break;
        case UFO:
            Settings::sharedInstance()->m_button_ufo = inner_button;
            break;
        case WAVE:
            Settings::sharedInstance()->m_button_wave = inner_button;
            break;
        case ROBOT:
            Settings::sharedInstance()->m_button_robot = inner_button;
            break;
        case SPIDER:
            Settings::sharedInstance()->m_button_spider = inner_button;
            break;
        case SWING:
            Settings::sharedInstance()->m_button_swing = inner_button;
            break;
        default:
            break;
    }

    auto settings = Settings::sharedInstance();

    button->setTag(game_mode);
    button->setPosition(position);
    return button;
}

bool CustomCharacterColorPage::loadSimpsAndSelectionSprites() {
    auto meow = this->m_mainLayer;
    auto settings = Settings::sharedInstance();

    settings->m_player_cube = typeinfo_cast<SimplePlayer*>(meow->getChildByID("cube-icon"));
    settings->m_player_ball = typeinfo_cast<SimplePlayer*>(meow->getChildByID("ball-icon"));
    settings->m_player_ufo = typeinfo_cast<SimplePlayer*>(meow->getChildByID("ufo-icon"));
    settings->m_player_wave = typeinfo_cast<SimplePlayer*>(meow->getChildByID("wave-icon"));
    settings->m_player_robot = typeinfo_cast<SimplePlayer*>(meow->getChildByID("robot-icon"));
    settings->m_player_spider = typeinfo_cast<SimplePlayer*>(meow->getChildByID("spider-icon"));
    settings->m_player_swing = typeinfo_cast<SimplePlayer*>(meow->getChildByID("swing-icon"));

    settings->m_current_color_primary_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-col1"));
    settings->m_current_color_secondary_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-col2"));
    settings->m_current_color_glow_sprite = typeinfo_cast<CCSprite*>(meow->getChildByID("cursor-glow"));

    // yeah this is ugly
    if (!settings->m_player_cube || !settings->m_player_ball || !settings->m_player_ufo || !settings->m_player_wave
            || !settings->m_player_robot || !settings->m_player_spider || !settings->m_player_swing) {
        log::error("failed to find all simps");
        return false;
    }

    if (!settings->m_current_color_primary_sprite || !settings->m_current_color_secondary_sprite || !settings->m_current_color_glow_sprite) {
        log::error("failed to find all selection sprites");
        return false;
    }

    return true;
}

void CustomCharacterColorPage::updateUI() {
    auto settings = Settings::sharedInstance();
    auto gameManager = GameManager::get();
    bool p2 = settings->m_current_p2;

    if(settings->m_player_cube) {
        int col1 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(cube).enabled ? CGC_OVERRIDE(cube).secondary : settings->m_defaultColor2;

        settings->m_player_cube->setColor(gameManager->colorForIdx(col1));
        settings->m_player_cube->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ship) {
        int col1 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(ship).enabled ? CGC_OVERRIDE(ship).secondary : settings->m_defaultColor2;

        settings->m_player_ship->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ship->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ball) {
        int col1 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(ball).enabled ? CGC_OVERRIDE(ball).secondary : settings->m_defaultColor2;

        settings->m_player_ball->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ball->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ufo) {
        int col1 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(ufo).enabled ? CGC_OVERRIDE(ufo).secondary : settings->m_defaultColor2;

        settings->m_player_ufo->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ufo->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_wave) {
        int col1 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(wave).enabled ? CGC_OVERRIDE(wave).secondary : settings->m_defaultColor2;

        settings->m_player_wave->setColor(gameManager->colorForIdx(col1));
        settings->m_player_wave->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_robot) {
        int col1 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(robot).enabled ? CGC_OVERRIDE(robot).secondary : settings->m_defaultColor2;

        settings->m_player_robot->setColor(gameManager->colorForIdx(col1));
        settings->m_player_robot->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_spider) {
        int col1 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(spider).enabled ? CGC_OVERRIDE(spider).secondary : settings->m_defaultColor2;

        settings->m_player_spider->setColor(gameManager->colorForIdx(col1));
        settings->m_player_spider->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_swing) {
        int col1 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).primary   : settings->m_defaultColor;
        int col2 = CGC_OVERRIDE(swing).enabled ? CGC_OVERRIDE(swing).secondary : settings->m_defaultColor2;

        settings->m_player_swing->setColor(gameManager->colorForIdx(col1));
        settings->m_player_swing->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_current_color_primary_sprite) {
        if (settings->m_current_mode == NONE) {
            settings->m_current_color_primary_sprite->setVisible(false);
        } else {
            this->updateColorSelectionSprite(settings->m_current_color_primary_sprite, PRIMARY);
        }
    }

    if(settings->m_current_color_secondary_sprite) {
        if (settings->m_current_mode == NONE) {
            settings->m_current_color_secondary_sprite->setVisible(false);
        } else {
            this->updateColorSelectionSprite(settings->m_current_color_secondary_sprite, SECONDARY);
        }
    }

    if(settings->m_current_color_glow_sprite) {
        // not supported yet
        settings->m_current_color_glow_sprite->setVisible(false);
    }

    if (settings->m_button_cube) {
        settings->m_button_cube->updateBGImage(CGC_OVERRIDE(cube).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ship) {
        settings->m_button_ship->updateBGImage(CGC_OVERRIDE(ship).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ball) {
        settings->m_button_ball->updateBGImage(CGC_OVERRIDE(ball).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ufo) {
        settings->m_button_ufo->updateBGImage(CGC_OVERRIDE(ufo).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_wave) {
        settings->m_button_wave->updateBGImage(CGC_OVERRIDE(wave).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_robot) {
        settings->m_button_robot->updateBGImage(CGC_OVERRIDE(robot).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_spider) {
        settings->m_button_spider->updateBGImage(CGC_OVERRIDE(spider).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_swing) {
        settings->m_button_swing->updateBGImage(CGC_OVERRIDE(swing).enabled ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (settings->m_current_gamemode_sprite) {
        this->updateGameModeSelectionSprite();
    }

    if (settings->m_garage_layer) {
        settings->m_garage_layer->updatePlayerColors();
    }
}

void CustomCharacterColorPage::updateColorSelectionSprite(CCSprite* sprite, ColorType type) {
    auto settings = Settings::sharedInstance();
    bool p2 = settings->m_current_p2;

    int color = 0;

    switch (settings->m_current_mode) {
        case CUBE:
            color = type == PRIMARY ? CGC_OVERRIDE(cube).primary : CGC_OVERRIDE(cube).secondary;
            break;
        case SHIP:
            color = type == PRIMARY ? CGC_OVERRIDE(ship).primary : CGC_OVERRIDE(ship).secondary;
            break;
        case BALL:
            color = type == PRIMARY ? CGC_OVERRIDE(ball).primary : CGC_OVERRIDE(ball).secondary;
            break;
        case UFO:
            color = type == PRIMARY ? CGC_OVERRIDE(ufo).primary : CGC_OVERRIDE(ufo).secondary;
            break;
        case WAVE:
            color = type == PRIMARY ? CGC_OVERRIDE(wave).primary : CGC_OVERRIDE(wave).secondary;
            break;
        case ROBOT:
            color = type == PRIMARY ? CGC_OVERRIDE(robot).primary : CGC_OVERRIDE(robot).secondary;
            break;
        case SPIDER:
            color = type == PRIMARY ? CGC_OVERRIDE(spider).primary : CGC_OVERRIDE(spider).secondary;
            break;
        case SWING:
            color = type == PRIMARY ? CGC_OVERRIDE(swing).primary : CGC_OVERRIDE(swing).secondary;
            break;
        default:
            break;
    }

    if (type != settings->m_current_color_type) {
        sprite->setColor(ccc3(50, 50, 50));
    } else {
        sprite->setColor(ccc3(255, 255, 255));
    }

    auto target_pos = this->m_mainLayer->convertToNodeSpaceAR(this->getPositionOfColor(color));
    sprite->setPosition(target_pos);
    sprite->setVisible(true);
}

void CustomCharacterColorPage::updateGameModeSelectionSprite() {
    auto settings = Settings::sharedInstance();

    auto sprite = settings->m_current_gamemode_sprite;
    if (settings->m_current_mode == NONE) {
        sprite->setVisible(false);
        return;
    } else {
        sprite->setVisible(true);
    }

    SimplePlayer* player = nullptr;

    switch (settings->m_current_mode) {
        case CUBE:
            player = settings->m_player_cube;
            break;
        case SHIP:
            player = settings->m_player_ship;
            break;
        case BALL:
            player = settings->m_player_ball;
            break;
        case UFO:
            player = settings->m_player_ufo;
            break;
        case WAVE:
            player = settings->m_player_wave;
            break;
        case ROBOT:
            player = settings->m_player_robot;
            break;
        case SPIDER:
            player = settings->m_player_spider;
            break;
        case SWING:
            player = settings->m_player_swing;
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

    auto settings = Settings::sharedInstance();

    settings->setOverrideColor(settings->m_current_mode, tag, settings->m_current_color_type, settings->m_current_p2);

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

    Settings::sharedInstance()->m_current_mode = static_cast<GameMode>(tag);

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

    if (tag == 2) {
        log::warn("changing glow isn't supported yet");
        Notification::create("changing glow isn't supported yet", NotificationIcon::Error)->show();
        return;
    }

    auto settings = Settings::sharedInstance();

    settings->m_current_color_type = static_cast<ColorType>(tag);

    // set buttons
    auto type = settings->m_current_color_type;
    static_cast<ButtonSprite*>(settings->m_button_primary_color->getChildren()->objectAtIndex(0))->updateBGImage(type == PRIMARY ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    static_cast<ButtonSprite*>(settings->m_button_secondary_color->getChildren()->objectAtIndex(0))->updateBGImage(type == SECONDARY ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    static_cast<ButtonSprite*>(settings->m_button_glow_color->getChildren()->objectAtIndex(0))->updateBGImage(type == GLOW ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);

    this->updateUI();
}

void CustomCharacterColorPage::onGameModeToggleButtonClicked(CCObject* sender) {
    int tag = sender->getTag();

    if (tag < 1 || tag > 8) {
        log::error("invalid tag: {}", tag);
        return;
    }

    auto game_mode = static_cast<GameMode>(tag);

    auto settings = Settings::sharedInstance();
    settings->toggleOverride(game_mode, settings->m_current_p2);
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

    auto settings = Settings::sharedInstance();
    settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube = !settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube;
    Mod::get()->setSavedValue(OVERRIDE_INNER_CUBE_ENABLED, settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube);

    if (auto button = typeinfo_cast<ButtonSprite*>(node->getChildren()->objectAtIndex(0))) {
        button->updateBGImage(settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (settings->m_overrides[CGC_PLAYER_INDEX].m_override_inner_cube) {
        Notification::create("cube in ship/ufo enabled", NotificationIcon::Success)->show();
    } else {
        Notification::create("cube in ship/ufo disabled", NotificationIcon::Success)->show();
    }
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
