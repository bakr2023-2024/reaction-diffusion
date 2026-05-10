#include <raylib.h>
int main()
{
    int sw = 960, sh = 720;
    InitWindow(sw, sh, "Program");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}