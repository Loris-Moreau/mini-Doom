#pragma once

#include <raylib.h>
#include <cmath>

class Player
{
public:
    void InitPlayer();
    void UpdatePlayer();
    void HandleInput();
    
    Vector2 position;
    float health;
    float speed;
    float rotation;
    bool isRunning;
};
