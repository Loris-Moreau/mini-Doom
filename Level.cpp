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
            // TODO Platforms
            /*else if (key == "platforms")
            {
                // Start parsing platform block
                std::string platformLine;
                while (std::getline(file, platformLine) && platformLine[0] == '-')
                {
                    Platform platform;
                    sscanf_s(platformLine.c_str(), "- x_start: %f, y_start: %f, x_end: %f, y_end: %f", &platform.x_start, &platform.y_start, &platform.x_end, &platform.y_end);
                    platforms.push_back(platform);
                }
            }
            // TODO Pickups
            else if (key == "items")
            {
                // Start parsing items block
                std::string itemLine;
                while (std::getline(file, itemLine) && itemLine[0] == '-')
                {
                    Item item;
                    sscanf_s(itemLine.c_str(), "- x: %f, y: %f, type: %s", &item.x, &item.y, &item.type[0]);
                    items.push_back(item);
                }
            }*/
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
