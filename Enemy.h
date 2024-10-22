#pragma once

#include <raylib.h>

class Enemy
{
public:
    void InitEnemies();
    void UpdateEnemies();
    //void killEnemy();
    
    Vector2 position;
    float health;
    float speed;
};
