#include "raylib.h"

struct MoveState{
  float dx;
  float dy;
  float dt;
};

struct Movement{
  float x;
  float y;
};

struct Figure{
  Texture2D texture;
  MoveState state;
  float scale_ratio;
  float x;
  float y;
};

void move_simple(Figure *figure, int screen_width, int screen_height) {
  float nx = figure->x + figure->state.dx*figure->state.dt;
  if (0.0 < nx - figure->texture.width/(2.0/figure->scale_ratio) && nx + figure->texture.width/(2.0/figure->scale_ratio) < screen_width) {
    figure->x = nx;
  } else {
    figure->state.dx = -figure->state.dx;
  }

  float ny = figure->y + figure->state.dy*figure->state.dt;

  if (0 < ny - figure->texture.height/(2.0/figure->scale_ratio) && ny + figure->texture.height/(2.0/figure->scale_ratio) < screen_height) {
    figure->y = ny;
  } else {
    figure->state.dy = -figure->state.dy;
  }
}

int main(void){
  const int screen_width = 800;
  const int screen_height = 640;
  const int fps = 60;
  InitWindow(screen_width, screen_height, "raylib test");

  Texture2D sebastacean = LoadTexture("sebastacean.png");
  MoveState sebastacean_state = {.dx = 200, .dy = 200, .dt =  1.0f/fps};
  Figure sebastacean_fig = {.texture = sebastacean, .state = sebastacean_state, .scale_ratio = 0.2, .x = screen_width/2.0, .y =  screen_height/2.0};
  int rotation = 0;

  // Source rectangle (part of the texture to use for drawing)
  Rectangle source_rec = { 0.0f, 0.0f, (float)sebastacean.width, (float)sebastacean.height };

  SetTargetFPS(fps);

  while(!WindowShouldClose()){
    move_simple(&sebastacean_fig, screen_width, screen_height);
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle dest_rec = {
      screen_width,
      screen_height,
      sebastacean_fig.texture.width*sebastacean_fig.scale_ratio,
      sebastacean_fig.texture.height*sebastacean_fig.scale_ratio
    };

    BeginDrawing();
    /* start drawing loop */
    ClearBackground(RAYWHITE);
    Vector2 origin = {
      sebastacean_fig.x + sebastacean.width * sebastacean_fig.scale_ratio/2.0f,
      sebastacean_fig.y + sebastacean.height * sebastacean_fig.scale_ratio/2.0f
    };

    DrawTexturePro(sebastacean, source_rec, dest_rec, origin, (float)rotation, WHITE);
    EndDrawing();
  }
  UnloadTexture(sebastacean);
  CloseWindow();
  return 0;
}
