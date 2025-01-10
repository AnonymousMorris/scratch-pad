#include <raylib.h>

typedef struct {
    int x;
    int y;
} pos;

int main() {
    int screenWidth = 800;
    int screenHeight = 450;

    const Color fgColor = BLACK;
    const Color bgColor = LIGHTGRAY;

    const float lineWidth = 4.0f;
    const float eraserWidth = 24.0f;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Scratch Pad");
    SetTargetFPS(60);

    pos last_position = {GetMouseX(), GetMouseY()};
    RenderTexture texture = LoadRenderTexture(screenWidth, screenHeight);
    bool eraser_on = false;

    while (!WindowShouldClose()) {
        // update
        if (IsWindowResized()) {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();
            // texture = texture
            RenderTexture newTexture = LoadRenderTexture(screenWidth, screenHeight);
            BeginTextureMode(newTexture);
            DrawTexture(texture.texture, 0, 0, WHITE);
            EndTextureMode();
            texture = newTexture;
        }
        
        pos cur_position = {GetMouseX(), GetMouseY()};
        eraser_on = IsKeyDown(KEY_SPACE);

        if (IsKeyDown(KEY_N)) {
            texture = LoadRenderTexture(screenWidth, screenHeight);
        }

        // draw to texture
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            BeginTextureMode(texture);
            Color draw_color = eraser_on? bgColor : fgColor;
            float draw_width = eraser_on? eraserWidth : lineWidth;
            DrawLineEx((Vector2){last_position.x, screenHeight - last_position.y}, 
                       (Vector2) {cur_position.x, screenHeight - cur_position.y}, 
                       draw_width,
                       draw_color);
            EndTextureMode();
        }
        last_position = cur_position;

        // draw to screen
        BeginDrawing();
        ClearBackground(bgColor);
        DrawTexture(texture.texture, 0, 0, WHITE);
        if (eraser_on) {
            DrawCircle(cur_position.x, cur_position.y, eraserWidth / 2, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
