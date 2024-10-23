#pragma once

#include <raylib.h>
#include <cmath>

class Player
{
public:
    void InitPlayer();
    void UpdatePlayer();
    void HandleInput();
    
    Vector2 position = {100, 100};
    float health = 100.0f;
    float speed = 1.0f;
    float rotation = 0.0f;
    bool isRunning = false;
};
