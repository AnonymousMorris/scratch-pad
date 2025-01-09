#include <raylib.h>

typedef struct {
    int x;
    int y;
} pos;

void draw(pos from, pos to, Color color) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawLine(from.x, from.y, to.x, to.y, color);
    EndDrawing();
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    const Color penColor = BLACK;
    const Color bgColor = LIGHTGRAY;

    const float lineWidth = 3.0f;

    InitWindow(screenWidth, screenHeight, "Scratch Pad");
    SetTargetFPS(60);

    pos last_position = {GetMouseX(), GetMouseY()};
    RenderTexture texture = LoadRenderTexture(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // update
        pos cur_position = {GetMouseX(), GetMouseY()};
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

            BeginTextureMode(texture);
            DrawLineEx((Vector2){last_position.x, screenHeight - last_position.y}, 
                       (Vector2) {cur_position.x, screenHeight - cur_position.y}, 
                       lineWidth,
                       penColor);
            EndTextureMode();
            // draw(last_position, cur_position, penColor);
        }
        last_position = cur_position;

        BeginDrawing();
        ClearBackground(bgColor);
        DrawTexture(texture.texture, 0, 0, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
