#include <raylib.h>
#include <vector>
#include <algorithm>
struct Cell
{
    float a, b;
};
using Grid = std::vector<std::vector<Cell>>;
using Mat = std::vector<std::vector<float>>;
float laplace(int x, int y, const Grid &grid, const Mat &mat, bool forA)
{
    float sum = 0;
    int width = grid.size();
    int height = grid[x].size();
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;
            sum += (forA ? grid[nx][ny].a : grid[nx][ny].b) * mat[dx + 1][dy + 1];
        }
    }
    return sum;
}
int main()
{
    int sw = 360, sh = 360;
    int fps = 60;
    Grid grid(sw, std::vector<Cell>(sh, {1.0f, 0.0f}));
    Grid next(sw, std::vector<Cell>(sh, {1.0f, 0.0f}));
    for (int x = -25; x < 25; x++)
    {
        for (int y = -25; y < 25; y++)
        {
            grid[sw / 2 + x][sh / 2 + y].b = 1.0f;
        }
    }
    InitWindow(sw, sh, "Reaction-Diffusion");
    SetTargetFPS(fps);
    float dt = 1.0f / fps;
    float dA = 1.0f, dB = 0.5f, f = 0.055f, k = 0.062f;
    Mat mat = {{0.05, 0.2, 0.05}, {0.2, -1, 0.2}, {0.05, 0.2, 0.05}};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int x = 0; x < sw; x++)
        {
            for (int y = 0; y < sh; y++)
            {
                float a = grid[x][y].a, b = grid[x][y].b;
                next[x][y].a = std::clamp(a + (dA * laplace(x, y, grid, mat, true) - a * b * b + f * (1 - a)), 0.0f, 1.0f);
                next[x][y].b = std::clamp(b + (dB * laplace(x, y, grid, mat, false) + a * b * b - (k + f) * b), 0.0f, 1.0f);
                int c = std::clamp((int)((next[x][y].a - next[x][y].b) * 255), 0, 255);
                Color color((unsigned char)c, (unsigned char)c, (unsigned char)c, 255);
                DrawPixel(x, y, color);
            }
        }
        std::swap(grid, next);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}