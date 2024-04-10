#include "raylib.h"

int main(void){
  InitWindow(800,600, "raylib test");
  SetTargetFPS(60);
  while(!WindowShouldClose()){
    BeginDrawing();
    /* start drawing loop */
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}
