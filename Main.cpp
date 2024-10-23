#include <raylib.h>

#include "GameState.h"

enum{ RES = 5 }; // 0=160x120, 1=360x240, 4=640x480
#define SCREEN_WIDTH (160 * RES)
#define SCREEN_HEIGHT (120 * RES)
#define PIXEL_SCALE (4 / RES)

void DrawGame()
{
    // Draw player
    DrawCircleV(gameStateInstance.player.position, 10, BLUE);

    // Draw enemies
    for (Enemy& enemy : gameStateInstance.enemies)
    {
        DrawCircleV(enemy.position, 10, RED);
    }
}


int main()
{
    UI ui;
    
    // Init the window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "mini Doom");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())); // Set FPS to the refresh rate of the monitor
    
    gameStateInstance.currentLevel.LoadLevel("level1.txt");
    
    gameStateInstance.player.InitPlayer();
    for (Enemy& value : gameStateInstance.enemies)
    {
        value.InitEnemies();
    }
    
    
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
