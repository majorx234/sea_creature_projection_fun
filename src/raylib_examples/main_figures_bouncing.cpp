#include "raylib.h"
#include <cmath>

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

void move_bumble_upwards(Figure *figure, int screen_width, int screen_height) {
  figure->state.dy = 0.1;
  figure->state.dx = 2.0 * std::sin(0.1 * figure->state.dt);
  figure->y += figure->state.dy;
  figure->x += figure->state.dx;
}

int main(void){
  const int screen_width = 800;
  const int screen_height = 640;
  const int fps = 60;
  InitWindow(screen_width, screen_height, "raylib test");

  Texture2D sebastacean = LoadTexture("sebastacean.png");
  MoveState sebastacean_state = {.dx = 200, .dy = 200, .dt =  1.0f/fps};
  Figure sebastacean_fig = {
    .texture = sebastacean,
    .state = sebastacean_state,
    .scale_ratio = 0.2,
    .x = screen_width/2.0,
    .y =  screen_height/2.0
  };

  Rectangle sebastacean_source_rec = { 0.0f, 0.0f, (float)sebastacean.width, (float)sebastacean.height };

  Texture2D bubble1 = LoadTexture("bubble.png");
  MoveState bubble1_state = {.dx = 20, .dy = 10, .dt = 1.0f/fps};
  Figure bubble1_fig = {
    .texture = sebastacean,
    .state = bubble1_state,
    .scale_ratio = 0.1,
    .x = 400,
    .y = 0
  };

  int rotation = 0;
  // Source rectangle (part of the texture to use for drawing)
  Rectangle bubble1_source_rec = { 0.0f, 0.0f, (float)bubble1.width, (float)bubble1.height };


  SetTargetFPS(fps);

  while(!WindowShouldClose()){
    move_simple(&sebastacean_fig, screen_width, screen_height);
    move_bumble_upwards(&bubble1_fig, screen_width, screen_height);
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle sebastacean_dest_rec = {
      screen_width,
      screen_height,
      sebastacean_fig.texture.width*sebastacean_fig.scale_ratio,
      sebastacean_fig.texture.height*sebastacean_fig.scale_ratio
    };
    Rectangle bubble1_dest_rec = {
      screen_width,
      screen_height,
      bubble1_fig.texture.width*bubble1_fig.scale_ratio,
      bubble1_fig.texture.height*bubble1_fig.scale_ratio
    };

    BeginDrawing();
    /* start drawing loop */
    ClearBackground(RAYWHITE);
    Vector2 sebastacean_origin = {
      sebastacean_fig.x + sebastacean.width * sebastacean_fig.scale_ratio/2.0f,
      sebastacean_fig.y + sebastacean.height * sebastacean_fig.scale_ratio/2.0f
    };
    Vector2 bubble1_origin = {
      bubble1_fig.x + bubble1.width * bubble1_fig.scale_ratio/2.0f,
      bubble1_fig.y + bubble1.height * bubble1_fig.scale_ratio/2.0f
    };

    DrawTexturePro(sebastacean, sebastacean_source_rec, sebastacean_dest_rec, sebastacean_origin, (float)rotation, WHITE);
    DrawTexturePro(bubble1, bubble1_source_rec, bubble1_dest_rec, bubble1_origin, (float)rotation, WHITE);
    EndDrawing();
  }
  UnloadTexture(sebastacean);
  CloseWindow();
  return 0;
}
