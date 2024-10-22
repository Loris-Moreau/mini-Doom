#pragma once

#include <vector>

#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include "UI.h"

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
    Level currentLevel;
};

extern GameState gameStateInstance;
