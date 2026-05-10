#include <raylib.h>
#include <vector>
#include <algorithm>
const int sw = 480, sh = 480;
struct Cell
{
    float a = 1.0f, b = 0.0f;
};
float laplace(int x, int y, const Cell *grid, const float mat[], bool forA)
{
    float sum = 0;
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = x + dx;
            int ny = y + dy;
            sum += (forA ? grid[ny * sw + nx].a : grid[ny * sw + nx].b) * mat[(dy + 1) * 3 + dx + 1];
        }
    }
    return sum;
}
int main()
{
    int fps = 60;
    Cell *grid = new Cell[sw * sh];
    Cell *next = new Cell[sw * sh];
    for (int x = -100; x < 100; x++)
    {
        for (int y = -100; y < 100; y++)
        {
            grid[(sh / 2 + y) * sw + (sw / 2 + x)].b = 1.0f;
        }
    }
    InitWindow(sw, sh, "Reaction-Diffusion");
    SetTargetFPS(fps);
    float dt = 1.0f / fps;
    float dA = 1.0f, dB = 0.5f, f = 0.055f, k = 0.062f;
    float mat[] = {0.05, 0.2, 0.05, 0.2, -1, 0.2, 0.05, 0.2, 0.05};
    Texture2D tex = LoadTextureFromImage(GenImageColor(sw, sh, BLACK));
    int *pixels = new int[sw * sh];
    while (!WindowShouldClose())
    {
        for (int y = 1; y < sh - 1; y++)
        {
            for (int x = 1; x < sw - 1; x++)
            {
                float a = grid[y * sw + x].a, b = grid[y * sw + x].b;
                next[y * sw + x].a = std::clamp(a + (dA * laplace(x, y, grid, mat, true) - a * b * b + f * (1 - a)) * 1.15f, 0.0f, 1.0f);
                next[y * sw + x].b = std::clamp(b + (dB * laplace(x, y, grid, mat, false) + a * b * b - (k + f) * b) * 1.15f, 0.0f, 1.0f);
                int c = std::clamp((int)((next[y * sw + x].a - next[y * sw + x].b) * 255), 0, 255);
                pixels[y * sw + x] = 255 << 24 | c << 16 | c << 8 | c;
            }
        }
        UpdateTexture(tex, pixels);
        std::swap(grid, next);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(tex, 0, 0, WHITE);
        EndDrawing();
    }
    CloseWindow();
    delete[] pixels;
    delete[] grid;
    delete[] next;
    return 0;
}