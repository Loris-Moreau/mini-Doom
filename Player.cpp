#include "Player.h"
#include "GameState.h"

void Player::InitPlayer()
{
    position = {gameStateInstance.player.position.x , gameStateInstance.player.position.y };
    health = 100.0f;
    speed = 2.0f;
    rotation = 0.0f;
    isRunning = false;
}

void Player::UpdatePlayer()
{
    HandleInput();
    
    speed = isRunning ? speed = 4.0 : speed = 2.0;
}

void Player::HandleInput()
{
    // Mouse aiming
    Vector2 mousePosition = GetMousePosition();
    rotation = atan2(mousePosition.y - position.y, mousePosition.x - position.x);
    
    if (IsKeyDown(KEY_LEFT_SHIFT)) isRunning = true;
    else isRunning = false;

    speed = isRunning ? 4.0f : 2.0f;  // Speed adjustment

    //KEY_Z
    if (IsKeyDown(KEY_W)) position.y -= speed;  // Move forward
    if (IsKeyDown(KEY_S)) position.y += speed;  // Move backward
    if (IsKeyDown(KEY_A)) position.x -= speed;  // Strafe left
    if (IsKeyDown(KEY_D)) position.x += speed;  // Strafe right
}
