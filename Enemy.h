#pragma once

#include <raylib.h>
#include <complex>

#include "GameState.h"

extern GameState gameStateInstance;

class Enemy
{
public:
    void InitEnemies();
    void UpdateEnemies();
    void killEnemy();
    
    Vector2 position;
    float health;
    float speed;
};
