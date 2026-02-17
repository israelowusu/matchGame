#include "raylib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5
#define SCORE_FONT_SIZE 42

const char tile_chars[TILE_TYPES] = { '#', '@', '$', '%', '&' };

char board[BOARD_SIZE][BOARD_SIZE];

int score = 200;
Vector2 grid_origin;
Texture2D background;
Font score_font;

char random_tile() {
    return tile_chars[rand() % TILE_TYPES];
}

void init_board() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = random_tile();
        }
    }

    int grid_width = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;

    grid_origin = (Vector2){
        (GetScreenWidth() - grid_width) / 2,
        (GetScreenHeight() - grid_height) / 2
    };
}

int main(void) {
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "Raylib 2D MATCH");
    SetTargetFPS(60);
    srand(time(NULL));

    background = LoadTexture("assets/background.jpg");
    score_font = LoadFontEx("assets/04B_03__.TTF", SCORE_FONT_SIZE, NULL, 0);

    init_board();

    while (!WindowShouldClose()) {
        // game logic

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            background,
            (Rectangle) {
                0, 0, background.width, background.height},
            (Rectangle) {
                0, 0, GetScreenWidth(), GetScreenHeight()
            },
            (Vector2) { 0, 0 },
            0.0f,
            WHITE
        );

        for (int y = 0; y < BOARD_SIZE; y++) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                Rectangle rect = {
                    grid_origin . x + (x * TILE_SIZE),
                    grid_origin . y + (y * TILE_SIZE),
                    TILE_SIZE,
                    TILE_SIZE
                };

                DrawRectangleLinesEx(rect, 1, DARKGRAY);

                DrawTextEx(GetFontDefault(),
                    TextFormat("%c", board[y][x]),
                    (Vector2) {
                        rect.x + 12,
                        rect.y +8
                    },
                    20, 1, WHITE);
            }
        }

        DrawTextEx(
            score_font,
            TextFormat("SCORE: %d", score),
            (Vector2) {
                20, 20
            },
            SCORE_FONT_SIZE,
            1.0f,
            YELLOW
        );

        // DrawText(TextFormat("SCORE: %d", score), 20, 20, 24, BLUE);

        EndDrawing();
    }

    UnloadTexture(background);
    UnloadFont(score_font);

    CloseWindow();
    return 0;
}
