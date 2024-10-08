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


struct DeleteConstrain {
  int max_x;
  int min_x;
  int max_y;
  int min_y;
  bool active;
};

struct Figure{
  Texture2D texture;
  Texture2D* walk_cycle_textures;
  size_t walk_cycle_textures_size;
  Rectangle source_rect;
  MoveState state;
  float scale_ratio;
  float x;
  float y;
  DeleteConstrain delete_constrain;
  void (*move_fct_ptr)(Figure*, int, int);
  bool (*delete_fun_ptr)(Figure*);
  void (*reset_fun_ptr)(Figure*);
  float wobble_scaling_factor;
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

void move_bubble_upwards(Figure *figure, int screen_width, int screen_height) {
  // figure->state.dy = 0.1;
  figure->state.dx = 0.5 * std::sin(0.05 * figure->state.dt);
  figure->y += figure->state.dy;
  figure->x += figure->state.dx;
  figure->state.dt += 1;
}

bool delete_bubble(Figure *figure) {
  if (figure->y > 640){
    return true;
  }
  return false;
}

void reset_buble(Figure *figure) {
  figure->y = 0;
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
    .walk_cycle_textures = NULL,
    .walk_cycle_textures_size = 0,
    .source_rect = { 0.0f, 0.0f, (float)sebastacean.width, (float)sebastacean.height },
    .state = sebastacean_state,
    .scale_ratio = 0.2,
    .x = screen_width/2.0,
    .y =  screen_height/2.0,
    .delete_constrain = {0,0,0,0, false},
    .move_fct_ptr = move_simple,
    .delete_fun_ptr = NULL,
    .reset_fun_ptr = NULL
  };


  Texture2D bubble1 = LoadTexture("bubble.png");
  Texture2D bubble2 = LoadTexture("bubble.png");
  Texture2D bubble3 = LoadTexture("bubble.png");
  Texture2D bubble4 = LoadTexture("bubble.png");
  MoveState bubble1_state = {.dx = 0.20, .dy = 0.10, .dt = 1.0f/fps};
  MoveState bubble2_state = {.dx = 0.10, .dy = 0.11, .dt = 2.0f/fps};
  MoveState bubble3_state = {.dx = 0.17, .dy = 0.13, .dt = 1.3f/fps};
  MoveState bubble4_state = {.dx = 0.19, .dy = 0.12, .dt = 1.0f/fps};

  Figure bubble1_fig = {
    .texture = bubble1,
    .walk_cycle_textures = NULL,
    .walk_cycle_textures_size = 0,
    .source_rect = { 0.0f, 0.0f, (float)bubble1.width, (float)bubble1.height },
    .state = bubble1_state,
    .scale_ratio = 0.1,
    .x = 70,
    .y = 300,
    .delete_constrain = {0,0,0,0, false},
    .move_fct_ptr = move_bubble_upwards,
    .delete_fun_ptr = delete_bubble,
    .reset_fun_ptr = reset_buble,
    .wobble_scaling_factor = 1.0
  };

  Figure bubble2_fig = {
    .texture = bubble2,
    .walk_cycle_textures = NULL,
    .walk_cycle_textures_size = 0,
    .source_rect = { 0.0f, 0.0f, (float)bubble2.width, (float)bubble2.height },
    .state = bubble2_state,
    .scale_ratio = 0.2,
    .x = 200,
    .y = 0,
    .delete_constrain = {0,0,0,0, false},
    .move_fct_ptr = move_bubble_upwards,
    .delete_fun_ptr = delete_bubble,
    .reset_fun_ptr = reset_buble,
    .wobble_scaling_factor = 1.0
  };

  Figure bubble3_fig = {
    .texture = bubble3,
    .walk_cycle_textures = NULL,
    .walk_cycle_textures_size = 0,
    .source_rect = { 0.0f, 0.0f, (float)bubble3.width, (float)bubble3.height },
    .state = bubble3_state,
    .scale_ratio = 0.15,
    .x = 430,
    .y = 450,
    .delete_constrain = {0,0,0,0, false},
    .move_fct_ptr = move_bubble_upwards,
    .delete_fun_ptr = delete_bubble,
    .reset_fun_ptr = reset_buble,
    .wobble_scaling_factor = 1.0
  };

  Figure bubble4_fig = {
    .texture = bubble4,
    .walk_cycle_textures = NULL,
    .walk_cycle_textures_size = 0,
    .source_rect = { 0.0f, 0.0f, (float)bubble4.width, (float)bubble4.height },
    .state = bubble4_state,
    .scale_ratio = 0.13,
    .x = 590,
    .y = 540,
    .delete_constrain = {0,0,0,0, false},
    .move_fct_ptr = move_bubble_upwards,
    .delete_fun_ptr = delete_bubble,
    .reset_fun_ptr = reset_buble,
    .wobble_scaling_factor = 1.0
  };

  int rotation = 0;
  // Source rectangle (part of the texture to use for drawing)


  SetTargetFPS(fps);
  Figure figure_list[5] = {sebastacean_fig, bubble1_fig, bubble2_fig, bubble3_fig, bubble4_fig};

  int time = 0;
  while(!WindowShouldClose()){
    move_simple(&sebastacean_fig, screen_width, screen_height);
    move_bubble_upwards(&bubble1_fig, screen_width, screen_height);

    /* start drawing loop */
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Destination rectangle (screen rectangle where drawing part of texture)
    for (int i=0;i<sizeof(figure_list)/sizeof(figure_list[0]);i++){
      Rectangle figure_dest_rec = {
        screen_width,
        screen_height,
        figure_list[i].texture.width * figure_list[i].scale_ratio * figure_list[i].wobble_scaling_factor,
        figure_list[i].texture.height * figure_list[i].scale_ratio
      };
	  figure_list[i].wobble_scaling_factor = 1.0 + (0.1 * std::sin(0.05 * time));
      Vector2 figure_origin = {
        figure_list[i].x + figure_list[i].texture.width * figure_list[i].scale_ratio/2.0f,
        figure_list[i].y + figure_list[i].texture.height * figure_list[i].scale_ratio/2.0f
      };
      DrawTexturePro(figure_list[i].texture, figure_list[i].source_rect, figure_dest_rec, figure_origin, (float)rotation, WHITE);
      figure_list[i].move_fct_ptr(&figure_list[i], screen_width, screen_height);

      // ToDo check deletion constrain
      if(figure_list[i].delete_fun_ptr){
        if(figure_list[i].delete_fun_ptr(&figure_list[i])) {
          if (figure_list[i].reset_fun_ptr){
            figure_list[i].reset_fun_ptr(&figure_list[i]);
          }
        }
      }
    }
    EndDrawing();
	time += 1;
  }
  UnloadTexture(sebastacean);
  CloseWindow();
  return 0;
}
