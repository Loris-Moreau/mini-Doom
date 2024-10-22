#include "Enemy.h"

void Enemy::InitEnemies()
{
    Enemy enemy;
    position = { 200, 200 };
    health = 50.0f;
    speed = 1.75f;
    
    gameStateInstance.enemies.push_back(enemy);
}

void Enemy::UpdateEnemies()
{
    for (auto& enemy : gameStateInstance.enemies)
    {
        if (enemy.health <= 0) continue;  // Skip dead enemies

        // Move towards the player
        Vector2 direction = { gameStateInstance.player.position.x - enemy.position.x, gameStateInstance.player.position.y - enemy.position.y };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;

        enemy.position.x += direction.x * enemy.speed;
        enemy.position.y += direction.y * enemy.speed;
    }
}

void Enemy::killEnemy()
{
    Enemy* enemy = this;
    gameStateInstance.enemies.remove(enemy);
}
