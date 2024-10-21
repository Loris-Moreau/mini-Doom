using namespace std;

#include <raylib.h>
#include <math.h>
#include <gl/GLU.h>

#define res 5                                   // 0=160x120, 1=360x240, 4=640x480
#define screenWidth 160 * res
#define screenHeight 120 * res
#define screenWidth2 (screenWidth/2)
#define screenHeight2 (screenHeight/2)
#define pixelScale 4/res
#define GLSWidth (screenWidth * pixelScale)    // OpenGl Window Width
#define GLSHeight (screenHeight * pixelScale) // OpenGl Window Height

typedef struct
{
    int fr1, fr2; // Frame 1 Frame2, to creat a constant frame rate
} time;

time T;

typedef struct
{
    int z, q, s, d;
    int strafeL, strafeR;
    int m;
} keys;

keys K;

void pixel(int x, int y, int c)
{
    Color color;
    if (c == 0) { color = YELLOW; }
    if (c == 1) { color = ORANGE; }
    if (c == 2) { color = GREEN; }
    if (c == 3) { color = DARKGREEN; }
    if (c == 4) { color = SKYBLUE; }
    if (c == 5) { color = BLUE; }
    if (c == 6) { color = BROWN; }
    if (c == 7) { color = DARKBROWN; }
    if (c == 8) { color = LIGHTGRAY; } //BG
    int rgb[3];
    rgb[0] = color.r;
    rgb[1] = color.g;
    rgb[2] = color.b;
    glColor3ub(rgb[0], rgb[0], rgb[0]);
    glBegin(GL_POINTS);
    glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
    glEnd();
}

void movePlayer()
{
    //ZQSD
    
    //Strafe

    //Look
}

int tick;

void draw3D()
{
    int x, y, c = 0;
    for (y = 0; y < screenHeight2; y++)
    {
        for (x = 0; x < screenHeight2; x++)
        {
            pixel(x, y, c);
            c += 1;
            if (c > 8)
            {
                c = 0;
            }
        }
    }
    // frame rate
    tick += 1;
    if (tick > 20)
    {
        tick = 0;
    }
    pixel(screenWidth2, screenHeight2 + tick, 0);
}

void display()
{
    int x, y, c = 0;
    if (T.fr1-T.fr2 >= 50)
    {
        ClearBackground(LIGHTGRAY);
        movePlayer();
        draw3D();

        T.fr2 = T.fr1;
        SwapScreenBuffer();
        SetWindowSize(GLSWidth, GLSHeight);
    }

    T.fr1 = GetFrameTime();
}

int main()
{
    // Init the window
    InitWindow(screenWidth, screenHeight, "mini Doom");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())); // Set FPS to the refresh rate of the monitor

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        /// Gaem Logic


        /// end Gaem

        // Runtime performance info
        DrawText(TextFormat("%02i FPS", GetFPS()), 15, 15, 20, RED);
        DrawText(TextFormat("%03.03f ms", GetFrameTime()), 15, 45, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
