using namespace std;

#include <raylib.h>
#include <vector>
#include <iostream>

#include "GameState.h"

#define res 5 // 0=160x120, 1=360x240, 4=640x480
#define screenWidth 160 * res
#define screenHeight 120 * res
#define pixelScale 4/res

void DrawGame()
{
    // Draw player
    DrawCircleV(gameStateInstance.player.position, 10, BLUE);

    // Draw enemies
    for (Enemy& enemy : gameStateInstance.enemies)
        {
        if (enemy.health > 0)
        {
            DrawCircleV(enemy.position, 10, RED);
        }
    }
}

int main()
{
    UI ui;
    
    // Init the window
    InitWindow(screenWidth, screenHeight, "mini Doom");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())); // Set FPS to the refresh rate of the monitor
    
    gameStateInstance.player.InitPlayer();
    for (Enemy value : gameStateInstance.enemies)
    {
        value.InitEnemies();
    }
    gameStateInstance.currentLevel.LoadLevel("level1.txt");

    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        /// Gaem Logic
        switch (gameStateInstance.currentState)
        {
        case MENU:
            ui.DrawMenu();
            break;
        case OPTIONS:
            ui.DrawOptions();
            break;
        case PLAYING:
            gameStateInstance.player.HandleInput();
            gameStateInstance.player.UpdatePlayer();
            for (Enemy value : gameStateInstance.enemies)
            {
                value.UpdateEnemies();
            }
            DrawGame();
            break;
        case EXIT:
            break;
        }

        // Runtime performance info
        DrawText(TextFormat("%02i FPS", GetFPS()), 15, 15, 20, RED);
        DrawText(TextFormat("%03.03f ms", GetFrameTime()), 15, 45, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
