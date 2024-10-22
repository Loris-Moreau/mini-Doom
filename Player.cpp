#include "Player.h"

void Player::InitPlayer()
{
    position = { 100, 100 };
    health = 100.0f;
    speed = 2.0f;
    rotation = 0.0f;
    isRunning = false;
}

void Player::UpdatePlayer()
{
    HandleInput();
    
    speed = isRunning ? speed * 2 : speed = 2.0;
}

void Player::HandleInput()
{
    // Mouse aiming
    Vector2 mousePosition = GetMousePosition();
    rotation = atan2(mousePosition.y - position.y, mousePosition.x - position.x);
    
    if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;
    else isRunning = false;

    speed = isRunning ? 4.0f : 2.0f;  // Speed adjustment

    if (IsKeyDown(KEY_Z)) position.y -= speed;  // Move forward
    if (IsKeyDown(KEY_S)) position.y += speed;  // Move backward
    if (IsKeyDown(KEY_Q)) position.x -= speed;  // Strafe left
    if (IsKeyDown(KEY_D)) position.x += speed;  // Strafe right
}