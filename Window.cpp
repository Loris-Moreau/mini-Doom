using namespace std;

#include <raylib.h> 

constexpr int screenWidth = 1080;
constexpr int screenHeight = 960;

bool startSelected = false;
bool endSelected = false;

int main()
{
    // Init the window
    InitWindow(screenWidth, screenHeight, "Intermediate AI");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())); // Set FPS to the refresh rate of the monitor
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        // Runtime performance info
        DrawText(TextFormat("%02i FPS", GetFPS()), 15, 15, 20, RED);
        DrawText(TextFormat("%03.03f ms", GetFrameTime()), 15, 45, 20, RED);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
