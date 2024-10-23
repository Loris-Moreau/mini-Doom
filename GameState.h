#pragma once

#include <vector>

#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include "UI.h"
#include "Wall.h"

enum gameState
{
    MENU,
    OPTIONS,
    PLAYING,
    EXIT
};

class GameState
{
public:
    gameState currentState = MENU;
    Player player;
    std::vector<Enemy> enemies;
    //std::vector<Platform> platforms;
    //std::vector<Item> items;
    float level_end_x, level_end_y;
    Level currentLevel;
    Camera camera;
};

extern GameState gameStateInstance;
