#include "UI.h"
#include "GameState.h"

void UI::DrawMenu()
{
    DrawText("mini DOOM", 200, 100, 40, BLACK);
    DrawText("Press Enter to Start", 200, 200, 20, BLACK);
    if (IsKeyPressed(KEY_ENTER)) gameStateInstance.currentState = PLAYING;
}

void UI::DrawOptions()
{
    DrawText("Options", 200, 100, 40, BLACK);
    DrawText("Mouse Sensitivity : ", 200, 200, 20, BLACK);
    DrawText("Controls : ZQSD (Movement), Right Click (Shoot), Shift (Run), Space (Use)", 200, 250, 20, BLACK);
    DrawText("Press ESC to go back", 200, 300, 20, BLACK);

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_ESCAPE))
    {
        gameStateInstance.currentState = MENU;
    }
}
