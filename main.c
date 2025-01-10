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

    HideCursor();

    while (!WindowShouldClose()) {
        // update
        if (IsWindowResized()) {
            int newScreenWidth = GetScreenWidth();
            int newScreenHeight = GetScreenHeight();
            // texture = texture
            RenderTexture newTexture = LoadRenderTexture(newScreenWidth, newScreenHeight);
            BeginTextureMode(newTexture);
            // DrawTextureEx(texture.texture, (Vector2){screenWidth, screenHeight}, -180, 1, WHITE);
            Rectangle source = (Rectangle) {0, 0, screenWidth, -screenHeight};
            DrawTextureRec(texture.texture, source, (Vector2) {0, 0}, WHITE);
            EndTextureMode();
            screenWidth = newScreenWidth;
            screenHeight = newScreenHeight;
            // UnloadTexture(texture.texture);
            texture = newTexture;
        }
        
        pos cur_position = {GetMouseX(), GetMouseY()};
        eraser_on = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_E);

        if (IsKeyDown(KEY_N) || IsKeyDown(KEY_C)) {
            texture = LoadRenderTexture(screenWidth, screenHeight);
        }

        // draw to texture
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            BeginTextureMode(texture);
            Color draw_color = eraser_on? bgColor : fgColor;
            float draw_width = eraser_on? eraserWidth : lineWidth;
            DrawLineEx((Vector2) {last_position.x, last_position.y}, 
                       (Vector2) {cur_position.x, cur_position.y}, 
                       draw_width,
                       draw_color);
            EndTextureMode();
        }
        last_position = cur_position;

        // draw to screen
        BeginDrawing();
        ClearBackground(bgColor);
        Rectangle source = (Rectangle) {0, 0, screenWidth, -screenHeight};
        DrawTextureRec(texture.texture, source, (Vector2) {0, 0}, WHITE);
        if (eraser_on) {
            DrawCircle(cur_position.x, cur_position.y, eraserWidth / 2, WHITE);
        }
        else {
            DrawCircle(cur_position.x, cur_position.y, lineWidth / 2, fgColor);
        }
        EndDrawing();
    }
    UnloadTexture(texture.texture);
    ShowCursor();
    CloseWindow();
    return 0;
}
