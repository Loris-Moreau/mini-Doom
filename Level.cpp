#include "Level.h"
#include "GameState.h"

bool Level::LoadLevel(const std::string& levelFilePath)
{
    std::ifstream file(levelFilePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << levelFilePath << '\n';
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Skip comment lines
        if (line[0] == '#') continue;

        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':'))
        {
            if (key == "player_start_x")
            {
                iss >> gameStateInstance.player.position.x;
            }
            else if (key == "player_start_y")
            {
                iss >> gameStateInstance.player.position.y;
            }
            else if (key == "enemy")
            {
                // Start parsing enemy block
                std::string enemyLine;
                while (std::getline(file, enemyLine) && enemyLine[0] == '-')
                {
                    Enemy enemy;
                    //sscanf_s(enemyLine.c_str(), "- x: %f, y: %f", &enemy.position.x, &enemy.position.y); // TODO add type later
                    if (sscanf_s(enemyLine.c_str(), "- x: %f, y: %f", &enemy.position.x, &enemy.position.y) == 2)
                    {
                        gameStateInstance.enemies.push_back(enemy);
                    }
                    else 
                    {
                        std::cerr << "Error parsing enemy data \n";
                    }
                    //gameStateInstance.enemies.push_back(enemy);
                }
            }
            else if (key == "walls")
            {
                std::string wallLine;
                while (std::getline(file, wallLine) && wallLine[0] == '-')
                {
                    Wall wall;
                    if (sscanf_s(wallLine.c_str(), "- x: %f, y: %f, width: %f, height: %f", &wall.rect.x, &wall.rect.y, &wall.rect.width, &wall.rect.height) == 4)
                    {
                        walls.push_back(wall);
                    }
                    else 
                    {
                        std::cerr << "Error parsing wall data \n";
                    }
                }
            }
            else if (key == "level_end_x")
            {
                iss >> gameStateInstance.level_end_x;
            }
            else if (key == "level_end_y")
            {
                iss >> gameStateInstance.level_end_y;
            }
        }
    }
    return true;
}
