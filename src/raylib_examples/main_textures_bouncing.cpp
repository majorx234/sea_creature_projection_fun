#include "raylib.h"

int main(void){
  const int screen_width = 800;
  const int screen_height = 640;
  InitWindow(800,600, "raylib test");

  Texture2D sebastacean = LoadTexture("sebastacean.png");
  Vector2 origin = { (float)0, (float)0 };

  int rotation = 0;

  // Source rectangle (part of the texture to use for drawing)
  Rectangle source_rec = { 0.0f, 0.0f, (float)sebastacean.width, (float)sebastacean.height };
  // Destination rectangle (screen rectangle where drawing part of texture)
  Rectangle dest_rec = {0, 0, screen_width, screen_height };

  SetTargetFPS(60);

  while(!WindowShouldClose()){

    BeginDrawing();
    /* start drawing loop */
    ClearBackground(RAYWHITE);
    DrawTexturePro(sebastacean, source_rec, dest_rec, origin, (float)rotation, WHITE);
    EndDrawing();
  }
  UnloadTexture(sebastacean);
  CloseWindow();
  return 0;
}
