#include "Enemy.h"
#include "GameState.h"

GameState gameStateInstance;

void Enemy::InitEnemies()
{
    Enemy enemy;
    enemy.position = { position.x, position.y };
    enemy.health = 50.0f;
    enemy.speed = 0.5f;
    
    //gameStateInstance.enemies.emplace_back(enemy);
}

void Enemy::UpdateEnemies()
{
    auto& enemies = gameStateInstance.enemies;
    
    // Using erase idiom to remove dead enemies
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](Enemy& enemy)
        {
            if (enemy.health <= 0)
            {
                return true;  // Remove enemy
            }
            else
            {
                // Move towards player
                Vector2 direction = { gameStateInstance.player.position.x - enemy.position.x, gameStateInstance.player.position.y - enemy.position.y };
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0.0f)
                {
                    direction.x /= length;
                    direction.y /= length;
                }
                
                enemy.position.x += direction.x * enemy.speed;
                enemy.position.y += direction.y * enemy.speed;
                
                return false;
            }
        }),
        enemies.end());
    
    /*for (Enemy& enemy : gameStateInstance.enemies)
    {
        if (enemy.health <= 0) // Dead
        {
            killEnemy();
            continue;
        }

        // Move towards the player
        Vector2 direction = { gameStateInstance.player.position.x - enemy.position.x, gameStateInstance.player.position.y - enemy.position.y };
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            direction.x /= length;
            direction.y /= length;
        }
        enemy.position.x += direction.x * enemy.speed;
        enemy.position.y += direction.y * enemy.speed;
    }*/
}

/*void Enemy::killEnemy()
{
    Enemy* enemy = this;
}*/
