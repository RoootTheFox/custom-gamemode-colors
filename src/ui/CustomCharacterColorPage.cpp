#include "ui/CustomCharacterColorPage.hpp"

#ifdef GEODE_IS_IOS
#include <Geode/platform/ItaniumCast.hpp>
#endif
using namespace geode::prelude;

CustomCharacterColorPage* CustomCharacterColorPage::customCreate() {
    auto settings = Settings::sharedInstance();

    // i want to properly inherit but everything except this crashes, so: FUCK IT, WE BALL.
    #ifdef GEODE_IS_WINDOWS
    /*auto _fuck = (CharacterColorPage*)operator new(0x2c0);
    if (!_fuck && !static_cast<CustomCharacterColorPage*>(_fuck)->init()) return nullptr;
    auto self = static_cast<CustomCharacterColorPage*>(_fuck);*/
    auto _sex = new CharacterColorPage();
    auto self = static_cast<CustomCharacterColorPage*>(_sex);
    if (!_sex || !_sex->init()) return nullptr;
    #else
    //auto self = static_cast<CustomCharacterColorPage*>(new CharacterColorPage());
    #endif

    if (!self) {
        log::error("failed to create CustomCharacterColorPage");
        return nullptr;
    }

    CCMenu* menu = self->m_buttonMenu;
    
    if (menu == nullptr) {
        log::error("didn't find color menu");
        return self;
    }

    // fix a crash that occurs when clicking the x button manually - doesn't happen in 2.206 anymore??
    /*auto x_button = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("close-button"));
    if (x_button) {
        log::debug("found close button ! :3");
        x_button->m_pfnSelector = menu_selector(CustomCharacterColorPage::close);
    }*/

    int buttons_found = 0;

    for (int i = 0; i < menu->getChildrenCount(); i++) {
        auto child = menu->getChildren()->objectAtIndex(i);
        auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(child);
        if (!node) {
            continue;
        }

        for (int j = 0; j < node->getChildrenCount(); j++) {
            auto node_child = node->getChildren()->objectAtIndex(j);
            if (typeinfo_cast<ColorChannelSprite*>(node_child)) {
                node->m_pfnSelector = menu_selector(CustomCharacterColorPage::onColorClicked);
            }
            if (typeinfo_cast<ButtonSprite*>(node_child)) {
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

    settings->m_button_primary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("col1-button"));
    settings->m_button_secondary_color = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("col2-button"));
    settings->m_button_glow_color = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildByID("glow-button"));

    // what an ugly if statement
    if (settings->m_button_primary_color == nullptr || settings->m_button_secondary_color == nullptr || settings->m_button_glow_color == nullptr) {
        log::error("DID NOT FIND ALL BUTTONS");
        return self;
    } else {
        settings->m_button_primary_color->m_pfnSelector = menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked);
        settings->m_button_secondary_color->m_pfnSelector = menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked);
        settings->m_button_glow_color->m_pfnSelector = menu_selector(CustomCharacterColorPage::onColorTypeButtonClicked);
    }

    // END
    // murder 2nd child from self if it exists (added by an icon hack mod, using it crashes the game)
    if (self->getChildrenCount() > 1) {
        self->removeChild(static_cast<CCNode*>(self->getChildren()->objectAtIndex(1)));
    }

    // gotta catch 'em all!
    if (self->loadSimpsAndSelectionSprites()) {
        // find the ship button BEFORE all other player buttons are added
        auto ship_player = findFirstChildRecursive<SimplePlayer>(menu, [](auto node) {
            return typeinfo_cast<SimplePlayer*>(node) != nullptr;
        });
        settings->m_player_ship = ship_player;
        auto ship_button = typeinfo_cast<CCMenuItemSprite*>(ship_player->getParent());
        ship_button->setTag(SHIP);
        ship_button->m_pfnSelector = menu_selector(CustomCharacterColorPage::onPlayerClicked);

        // cube button
        auto cube_button = self->createPlayerButton(settings->m_player_cube, CUBE);
        menu->addChild(cube_button);

        auto ball_button = self->createPlayerButton(settings->m_player_ball, BALL);
        menu->addChild(ball_button);

        auto ufo_button = self->createPlayerButton(settings->m_player_ufo, UFO);
        menu->addChild(ufo_button);

        auto wave_button = self->createPlayerButton(settings->m_player_wave, WAVE);
        menu->addChild(wave_button);

        auto robot_button = self->createPlayerButton(settings->m_player_robot, ROBOT);
        menu->addChild(robot_button);

        auto spider_button = self->createPlayerButton(settings->m_player_spider, SPIDER);
        menu->addChild(spider_button);

        auto swing_button = self->createPlayerButton(settings->m_player_swing, SWING);
        menu->addChild(swing_button);

        float button_width = 33.0f;
        auto cube_toggle_button = self->createGameModeButton(CUBE, {button_width, -7});
        menu->addChild(cube_toggle_button);

        auto ship_toggle_button = self->createGameModeButton(SHIP, {button_width * 2, -7});
        menu->addChild(ship_toggle_button);

        auto ball_toggle_button = self->createGameModeButton(BALL, {button_width * 3, -7});
        menu->addChild(ball_toggle_button);

        auto ufo_toggle_button = self->createGameModeButton(UFO, {button_width * 4, -7});
        menu->addChild(ufo_toggle_button);

        auto wave_toggle_button = self->createGameModeButton(WAVE, {button_width * 5, -7});
        menu->addChild(wave_toggle_button);

        auto robot_toggle_button = self->createGameModeButton(ROBOT, {button_width * 6, -7});
        menu->addChild(robot_toggle_button);

        auto spider_toggle_button = self->createGameModeButton(SPIDER, {button_width * 7, -7});
        menu->addChild(spider_toggle_button);

        auto swing_toggle_button = self->createGameModeButton(SWING, {button_width * 8, -7});
        menu->addChild(swing_toggle_button);

        // sprite to show current player
        auto current_gamemode_sprite = CCSprite::createWithSpriteFrameName(TEXTURE_SELECTED_FRAME);
        current_gamemode_sprite->setContentSize({32, 32});
        current_gamemode_sprite->setScale(1.15f);
        self->m_mainLayer->addChild(current_gamemode_sprite);
        settings->m_current_gamemode_sprite = current_gamemode_sprite;

        self->updateUI();
    } else {
        log::error("failed to load icons and selection sprites (this should never happen)");
    }

    auto inner_button = ButtonSprite::create("color cube in ship/ufo", 77, true, "bigFont.fnt",
            settings->m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED, 20.0f, 4.0f);
    auto button = CCMenuItemSpriteExtra::create(
        inner_button,
        self,
        menu_selector(CustomCharacterColorPage::onCubeInShipUfoToggleButtonClicked)
    );
    self->m_buttonMenu->addChild(button);
    button->setPosition({53.5f, -265});

    //self->autorelease();
    //log::debug("CustomCharacterColorPage::create returning self");
    return self;
}

CCMenuItemSpriteExtra* CustomCharacterColorPage::createPlayerButton(SimplePlayer* player, GameMode game_mode) {
    #if defined(GEODE_IS_MACOS) || defined(GEODE_IS_IOS)
    auto player_pos = player->getParent()->convertToWorldSpace(player->getPosition()) + player->getParent()->getAnchorPointInPoints();
    #else
    auto player_pos = player->getParent()->convertToWorldSpaceAR(player->getPosition());
    #endif
    player->removeFromParent();

    auto button = CCMenuItemSpriteExtra::create(
        player,
        this,
        menu_selector(CustomCharacterColorPage::onPlayerClicked)
    );
    button->setContentSize({30, 30});
    player->setPosition({15, 15});

    #if defined(GEODE_IS_MACOS) || defined(GEODE_IS_IOS)
    button->setPosition(this->m_buttonMenu->convertToNodeSpace(player_pos) - this->m_buttonMenu->getAnchorPointInPoints());
    #else
    button->setPosition(this->m_buttonMenu->convertToNodeSpaceAR(player_pos));
    #endif
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

void CustomCharacterColorPage::close(CCObject* sender) {
    this->removeAllChildrenWithCleanup(true);
    // prevent crash, hacky but works for now
    // a user is probably not going to close this menu so often that this would make any difference
    this->retain();
    
    this->removeFromParentAndCleanup(true);
}

void CustomCharacterColorPage::updateUI() {
    auto settings = Settings::sharedInstance();
    auto gameManager = GameManager::get();

    if(settings->m_player_cube) {
        int col1 = settings->m_override_cube ? settings->m_cube_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_cube ? settings->m_cube_override.secondary : settings->m_defaultColor2;

        settings->m_player_cube->setColor(gameManager->colorForIdx(col1));
        settings->m_player_cube->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ship) {
        int col1 = settings->m_override_ship ? settings->m_ship_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_ship ? settings->m_ship_override.secondary : settings->m_defaultColor2;

        settings->m_player_ship->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ship->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ball) {
        int col1 = settings->m_override_ball ? settings->m_ball_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_ball ? settings->m_ball_override.secondary : settings->m_defaultColor2;

        settings->m_player_ball->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ball->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ufo) {
        int col1 = settings->m_override_ufo ? settings->m_ufo_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_ufo ? settings->m_ufo_override.secondary : settings->m_defaultColor2;

        settings->m_player_ufo->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ufo->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_wave) {
        int col1 = settings->m_override_wave ? settings->m_wave_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_wave ? settings->m_wave_override.secondary : settings->m_defaultColor2;

        settings->m_player_wave->setColor(gameManager->colorForIdx(col1));
        settings->m_player_wave->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_robot) {
        int col1 = settings->m_override_robot ? settings->m_robot_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_robot ? settings->m_robot_override.secondary : settings->m_defaultColor2;

        settings->m_player_robot->setColor(gameManager->colorForIdx(col1));
        settings->m_player_robot->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_spider) {
        int col1 = settings->m_override_spider ? settings->m_spider_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_spider ? settings->m_spider_override.secondary : settings->m_defaultColor2;

        settings->m_player_spider->setColor(gameManager->colorForIdx(col1));
        settings->m_player_spider->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_swing) {
        int col1 = settings->m_override_swing ? settings->m_swing_override.primary  : settings->m_defaultColor;
        int col2 = settings->m_override_swing ? settings->m_swing_override.secondary : settings->m_defaultColor2;

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
        settings->m_button_cube->updateBGImage(settings->m_override_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ship) {
        settings->m_button_ship->updateBGImage(settings->m_override_ship ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ball) {
        settings->m_button_ball->updateBGImage(settings->m_override_ball ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_ufo) {
        settings->m_button_ufo->updateBGImage(settings->m_override_ufo ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_wave) {
        settings->m_button_wave->updateBGImage(settings->m_override_wave ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_robot) {
        settings->m_button_robot->updateBGImage(settings->m_override_robot ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_spider) {
        settings->m_button_spider->updateBGImage(settings->m_override_spider ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }
    if (settings->m_button_swing) {
        settings->m_button_swing->updateBGImage(settings->m_override_swing ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (settings->m_current_gamemode_sprite) {
        this->updateGameModeSelectionSprite();
    }
}

void CustomCharacterColorPage::updateColorSelectionSprite(CCSprite* sprite, ColorType type) {
    auto settings = Settings::sharedInstance();

    int color = 0;

    switch (settings->m_current_mode) {
        case CUBE:
            color = type == PRIMARY ? settings->m_cube_override.primary : settings->m_cube_override.secondary;
            break;
        case SHIP:
            color = type == PRIMARY ? settings->m_ship_override.primary : settings->m_ship_override.secondary;
            break;
        case BALL:
            color = type == PRIMARY ? settings->m_ball_override.primary : settings->m_ball_override.secondary;
            break;
        case UFO:
            color = type == PRIMARY ? settings->m_ufo_override.primary : settings->m_ufo_override.secondary;
            break;
        case WAVE:
            color = type == PRIMARY ? settings->m_wave_override.primary : settings->m_wave_override.secondary;
            break;
        case ROBOT:
            color = type == PRIMARY ? settings->m_robot_override.primary : settings->m_robot_override.secondary;
            break;
        case SPIDER:
            color = type == PRIMARY ? settings->m_spider_override.primary : settings->m_spider_override.secondary;
            break;
        case SWING:
            color = type == PRIMARY ? settings->m_swing_override.primary : settings->m_swing_override.secondary;
            break;
        default:
            break;
    }

    if (type != settings->m_current_color_type) {
        sprite->setColor(ccc3(50, 50, 50));
    } else {
        sprite->setColor(ccc3(255, 255, 255));
    }

    #if defined(GEODE_IS_MACOS) || defined(GEODE_IS_IOS)
    auto target_pos = this->m_mainLayer->convertToNodeSpace(this->getPositionOfColor(color)) - this->m_mainLayer->getAnchorPointInPoints();
    #else
    auto target_pos = this->m_mainLayer->convertToNodeSpaceAR(this->getPositionOfColor(color));
    #endif
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
    #if defined(GEODE_IS_MACOS) || defined(GEODE_IS_IOS)
    auto pos = this->m_mainLayer->convertToNodeSpace(this->m_buttonMenu->convertToWorldSpace(player->getParent()->getPosition() + this->m_buttonMenu->getAnchorPointInPoints())) - this->m_mainLayer->getAnchorPointInPoints();
    #else
    auto pos = this->m_mainLayer->convertToNodeSpaceAR(this->m_buttonMenu->convertToWorldSpaceAR(player->getParent()->getPosition()));
    #endif
    
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
        #if defined(GEODE_IS_MACOS) || defined(GEODE_IS_IOS)
        return this->m_buttonMenu->convertToWorldSpace(child->getPosition()) + this->m_buttonMenu->getAnchorPointInPoints();
        #else
        return this->m_buttonMenu->convertToWorldSpaceAR(child->getPosition());
        #endif
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

    settings->setOverrideColor(settings->m_current_mode, tag, settings->m_current_color_type);

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
    auto primary_button = settings->m_button_primary_color;
    auto secondary_button = settings->m_button_secondary_color;
    auto glow_button = settings->m_button_glow_color;

    switch (settings->m_current_color_type) {
        case PRIMARY:
            static_cast<ButtonSprite*>(primary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_ENABLED);
            static_cast<ButtonSprite*>(secondary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            static_cast<ButtonSprite*>(glow_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            break;
        case SECONDARY:
            static_cast<ButtonSprite*>(primary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            static_cast<ButtonSprite*>(secondary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_ENABLED);
            static_cast<ButtonSprite*>(glow_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            break;
        case GLOW:
            static_cast<ButtonSprite*>(primary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            static_cast<ButtonSprite*>(secondary_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_DISABLED);
            static_cast<ButtonSprite*>(glow_button->getChildren()->objectAtIndex(0))->updateBGImage(TEXTURE_BUTTON_ENABLED);
            break;
    }

    this->updateUI();
}

void CustomCharacterColorPage::onGameModeToggleButtonClicked(CCObject* sender) {
    int tag = sender->getTag();

    if (tag < 1 || tag > 8) {
        log::error("invalid tag: {}", tag);
        return;
    }

    auto game_mode = static_cast<GameMode>(tag);

    Settings::sharedInstance()->toggleOverride(game_mode);
    updateUI();
}

void CustomCharacterColorPage::onCubeInShipUfoToggleButtonClicked(CCObject* sender) {
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }

    auto settings = Settings::sharedInstance();
    settings->m_override_inner_cube = !settings->m_override_inner_cube;
    Mod::get()->setSavedValue(OVERRIDE_INNER_CUBE_ENABLED, settings->m_override_inner_cube);

    if (auto button = typeinfo_cast<ButtonSprite*>(node->getChildren()->objectAtIndex(0))) {
        button->updateBGImage(settings->m_override_inner_cube ? TEXTURE_BUTTON_ENABLED : TEXTURE_BUTTON_DISABLED);
    }

    if (settings->m_override_inner_cube) {
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