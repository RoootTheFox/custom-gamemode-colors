#include "ui/CustomCharacterColorPage.hpp"

using namespace geode::prelude;

CustomCharacterColorPage* CustomCharacterColorPage::customCreate() {
    auto settings = Settings::sharedInstance();

    log::debug("CustomCharacterColorPage::customCreate");

    // i want to properly inherit but everything except this crashes, so: FUCK IT, WE BALL.
    auto self = static_cast<CustomCharacterColorPage*>(CharacterColorPage::create());

    // kill all children brutally, no mercy
    self->removeAllChildrenWithCleanup(true);

    if (!self || !self->init()) {
        log::error("failed to create CustomCharacterColorPage");
        return nullptr;
    }

    log::debug("CustomCharacterColorPage::customCreate aa");

    // modify things
    log::debug("CustomCharacterColorPage::create: children count: {}", self->getChildrenCount());

    CCMenu* menu = self->m_buttonMenu;
    
    if (menu == nullptr) {
        log::error("didn't find color menu");
        return self;
    }

    log::debug("menu children count: {}", menu->getChildrenCount());

    // fix a crash that occurs when clicking the x button manually
    auto x_button = typeinfo_cast<CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(0));
    if (x_button) {
        x_button->m_pfnSelector = menu_selector(CustomCharacterColorPage::close);
    }

    for (int i = 0; i < menu->getChildrenCount(); i++) {
        auto child = menu->getChildren()->objectAtIndex(i);
        auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(child);
        if (!node) {
            log::debug("not a CCMenuItemSpriteExtra, ignoring");
            continue;
        }

        for (int j = 0; j < node->getChildrenCount(); j++) {
            if (typeinfo_cast<ColorChannelSprite*>(node->getChildren()->objectAtIndex(j))) {
                node->m_pfnSelector = menu_selector(CustomCharacterColorPage::onColorClicked);
            }
        }
    }

    log::debug("CustomCharacterColorPage::create: finished creating, calling autorelease");

    // END
    // murder 2nd child from self if it exists (added by an icon hack mod, using it crashes the game)
    if (self->getChildrenCount() > 1) {
        self->removeChild(static_cast<CCNode*>(self->getChildren()->objectAtIndex(1)));
    }

    auto layer = self->m_mainLayer;

    // gotta catch 'em all!
    if (self->loadSimpsIn(self->m_mainLayer)) {
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

        auto ufo_button = self->createPlayerButton(settings->m_player_bird, UFO);
        menu->addChild(ufo_button);

        auto wave_button = self->createPlayerButton(settings->m_player_dart, WAVE);
        menu->addChild(wave_button);

        auto robot_button = self->createPlayerButton(settings->m_player_robot, ROBOT);
        menu->addChild(robot_button);

        auto spider_button = self->createPlayerButton(settings->m_player_spider, SPIDER);
        menu->addChild(spider_button);

        auto swing_button = self->createPlayerButton(settings->m_player_swing, SWING);
        menu->addChild(swing_button);

        //handleTouchPriority(self, true);

        self->updatePlayerColors();
    } else {
        log::error("failed to load icons (this should never happen)");
    }

    //self->autorelease();
    log::debug("CustomCharacterColorPage::create returning self");
    return self;
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

bool CustomCharacterColorPage::loadSimpsIn(CCNode* meow) {
    int simps_found = 0;

    auto settings = Settings::sharedInstance();

    for (int i = 0; i < meow->getChildrenCount(); i++) {
        auto simple_player = typeinfo_cast<SimplePlayer*>(meow->getChildren()->objectAtIndex(i));

        if (simple_player) {
            switch (simps_found) {
                case 0:
                    log::debug("found cube");                   
                    settings->m_player_cube = simple_player;
                    break;
                case 1: // this is ball, because ship is inside the menu and not in the layer directly
                    log::debug("found balls");
                    settings->m_player_ball = simple_player;
                    break;
                case 2:
                    log::debug("found ufo");
                    settings->m_player_bird = simple_player;
                    break;
                case 3:
                    log::debug("found wave");
                    settings->m_player_dart = simple_player;
                    break;
                case 4:
                    log::debug("found robot");
                    settings->m_player_robot = simple_player;
                    break;
                case 5:
                    log::debug("found spider");
                    settings->m_player_spider = simple_player;
                    break;
                case 6:
                    log::debug("found swing");
                    settings->m_player_swing = simple_player;
                    break;
                default:
                    break;
            }

            simps_found++;
        }

        if (simps_found == 7) {
            break;
        }
    }

    return simps_found == 7;
}

void CustomCharacterColorPage::close(CCObject* sender) {
    this->removeAllChildrenWithCleanup(true);
    // prevent crash, hacky but works for now
    // a user is probably not going to close this menu so often that this would make any difference
    this->retain();
    
    this->removeFromParentAndCleanup(true);
    
    log::debug("real!! MEOW");
}

void CustomCharacterColorPage::updatePlayerColors() {
    log::debug("CustomCharacterColorPage::updatePlayerColors");
    auto settings = Settings::sharedInstance();
    auto gameManager = GameManager::get();

    if(settings->m_player_cube) {
        int col1 = settings->m_override_cube ? settings->m_cube_override  : settings->m_defaultColor;
        int col2 = settings->m_override_cube ? settings->m_cube_override2 : settings->m_defaultColor2;

        settings->m_player_cube->setColor(gameManager->colorForIdx(col1));
        settings->m_player_cube->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ship) {
        int col1 = settings->m_override_ship ? settings->m_ship_override  : settings->m_defaultColor;
        int col2 = settings->m_override_ship ? settings->m_ship_override2 : settings->m_defaultColor2;

        settings->m_player_ship->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ship->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_ball) {
        int col1 = settings->m_override_ball ? settings->m_ball_override  : settings->m_defaultColor;
        int col2 = settings->m_override_ball ? settings->m_ball_override2 : settings->m_defaultColor2;

        settings->m_player_ball->setColor(gameManager->colorForIdx(col1));
        settings->m_player_ball->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_bird) {
        int col1 = settings->m_override_bird ? settings->m_bird_override  : settings->m_defaultColor;
        int col2 = settings->m_override_bird ? settings->m_bird_override2 : settings->m_defaultColor2;

        settings->m_player_bird->setColor(gameManager->colorForIdx(col1));
        settings->m_player_bird->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_dart) {
        int col1 = settings->m_override_dart ? settings->m_dart_override  : settings->m_defaultColor;
        int col2 = settings->m_override_dart ? settings->m_dart_override2 : settings->m_defaultColor2;

        settings->m_player_dart->setColor(gameManager->colorForIdx(col1));
        settings->m_player_dart->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_robot) {
        int col1 = settings->m_override_robot ? settings->m_robot_override  : settings->m_defaultColor;
        int col2 = settings->m_override_robot ? settings->m_robot_override2 : settings->m_defaultColor2;

        settings->m_player_robot->setColor(gameManager->colorForIdx(col1));
        settings->m_player_robot->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_spider) {
        int col1 = settings->m_override_spider ? settings->m_spider_override  : settings->m_defaultColor;
        int col2 = settings->m_override_spider ? settings->m_spider_override2 : settings->m_defaultColor2;

        settings->m_player_spider->setColor(gameManager->colorForIdx(col1));
        settings->m_player_spider->setSecondColor(gameManager->colorForIdx(col2));
    }

    if(settings->m_player_swing) {
        int col1 = settings->m_override_swing ? settings->m_swing_override  : settings->m_defaultColor;
        int col2 = settings->m_override_swing ? settings->m_swing_override2 : settings->m_defaultColor2;

        settings->m_player_swing->setColor(gameManager->colorForIdx(col1));
        settings->m_player_swing->setSecondColor(gameManager->colorForIdx(col2));
    }
}

void CustomCharacterColorPage::onColorClicked(CCObject* sender) {
    log::debug("CustomCharacterColorPage::onColorClicked");
    auto node = typeinfo_cast<CCMenuItemSpriteExtra*>(sender);
    if (!node) {
        log::error("sender is not a CCMenuItemSpriteExtra");
        return;
    }
    int tag = node->getTag();

    log::debug("color clicked: {}", tag);

    auto settings = Settings::sharedInstance();

    switch (this->m_current_mode) {
        case CUBE:
            settings->m_cube_override = tag;
            break;
        case SHIP:
            settings->m_ship_override = tag;
            break;
        case BALL:
            settings->m_ball_override = tag;
            break;
        case UFO:
            settings->m_bird_override = tag;
            break;
        case WAVE:
            settings->m_dart_override = tag;
            break;
        case ROBOT:
            settings->m_robot_override = tag;
            break;
        case SPIDER:
            settings->m_spider_override = tag;
            break;
        case SWING:
            settings->m_swing_override = tag;
            break;
        default:
            break;
    }

    this->updatePlayerColors();
}

void CustomCharacterColorPage::onPlayerClicked(CCObject* sender) {
    log::debug("CustomCharacterColorPage::onPlayerClicked");
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

    this->m_current_mode = static_cast<GameMode>(tag);

    log::debug("player clicked: {}", tag);
    this->updatePlayerColors();
}