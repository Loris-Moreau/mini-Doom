#include <raylib.h>

#include "GameState.h"

enum{ RES = 5 }; // 0=160x120, 1=360x240, 4=640x480
#define SCREEN_WIDTH (160 * RES)
#define SCREEN_HEIGHT (120 * RES)
#define PIXEL_SCALE (4 / RES)

void DrawGame()
{
    // Begin drawing 3D or 2D elements
    BeginMode3D(gameStateInstance.camera);
    
    // Draw player
    DrawCircleV(gameStateInstance.player.position, 10, BLUE);

    // Draw enemies
    for (Enemy& enemy : gameStateInstance.enemies)
    {
        DrawCircleV(enemy.position, 10, RED);
    }
    
    // Draw walls
    for (Wall& wall : gameStateInstance.currentLevel.walls)
    {
        DrawRectangleRec(wall.rect, DARKGRAY);
    }
    
    EndMode3D();
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
    
    // Initialize the camera in first-person view mode
    gameStateInstance.camera.position = Vector3{ gameStateInstance.player.position.x, gameStateInstance.player.position.y, 2.0f };  // Camera starts at player's position
    gameStateInstance.camera.target = Vector3{ gameStateInstance.player.position.x + 1.0f, gameStateInstance.player.position.y, 2.0f };  // Looking forward
    gameStateInstance.camera.up = Vector3{ 0.0f, 0.0f, 1.0f };  // Z = up
    gameStateInstance.camera.fovy = 45.0f;  // Field of view in degrees
    gameStateInstance.camera.projection = CAMERA_FIRST_PERSON;  // Set camera mode to first-person
    // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

    
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
            
            // Update the camera position to follow the player
            gameStateInstance.camera.position = Vector3{ gameStateInstance.player.position.x, gameStateInstance.player.position.y, 2.0f };
            gameStateInstance.camera.target = Vector3{ gameStateInstance.player.position.x + 1.0f, gameStateInstance.player.position.y, 2.0f };
            // Set the camera mode
            UpdateCamera(&gameStateInstance.camera, CAMERA_FIRST_PERSON);  // Update first-person camera
            BeginMode3D(gameStateInstance.camera);  // Start 3D drawing with the camera

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
        EndMode3D(); 
    }

    CloseWindow();
    return 0;
}
