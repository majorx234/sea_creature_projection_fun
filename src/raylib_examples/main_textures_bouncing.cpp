#include "raylib.h"

int main(void){
  const int screen_width = 800;
  const int screen_height = 640;
  const int fps = 60;
  InitWindow(800,600, "raylib test");

  Texture2D sebastacean = LoadTexture("sebastacean.png");

  int rotation = 0;
  float scale_ratio = 0.2;

  int move_step = 0;
  int move_steo_jump = 20;

  // Source rectangle (part of the texture to use for drawing)
  Rectangle source_rec = { 0.0f, 0.0f, (float)sebastacean.width, (float)sebastacean.height };
  // Destination rectangle (screen rectangle where drawing part of texture)

  SetTargetFPS(fps);

  float x = screen_width/2.0;
  float y = screen_height/2.0;

  float dx = 200;
  float dy = 200;
  float dt = 1.0f/fps;

  int counter = 0;
  while(!WindowShouldClose()){
    if (counter == move_steo_jump){
      counter = 0;
      move_step += 1;
    }
    else {
      counter += 1;
    }

    float nx = x + dx*dt;
    if (0.0 < nx - sebastacean.width/(2.0/scale_ratio) && nx + sebastacean.width/(2.0/scale_ratio) < screen_width) {
      x = nx;
    } else {
      dx = -dx;
    }

    float ny = y + dy*dt;
    if (0 < ny - sebastacean.height/(2.0/scale_ratio) && ny + sebastacean.height/(2.0/scale_ratio) < screen_height) {
      y = ny;
    } else {
      dy = -dy;
    }

    Rectangle dest_rec = {screen_width, screen_height, sebastacean.width*scale_ratio, sebastacean.height*scale_ratio };

    BeginDrawing();
    /* start drawing loop */
    ClearBackground(RAYWHITE);
    Vector2 origin = { x + sebastacean.width * scale_ratio/2.0f, y + sebastacean.height * scale_ratio/2.0f };

    DrawTexturePro(sebastacean, source_rec, dest_rec, origin, (float)rotation, WHITE);
    EndDrawing();
  }
  UnloadTexture(sebastacean);
  CloseWindow();
  return 0;
}
