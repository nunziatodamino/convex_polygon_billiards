#include <raylib.h>
#include "polygon.cpp"

int main() 
{
  const int screenWidth = 800;
  const int screenHeight = 600;

  Vector2 center{screenWidth /2.0f, screenHeight/2.0f};
  const int vert{6};
  const float apot{225.0};
  Polygon poly(center, vert, apot);
  std::vector<Vector2> vertices{poly.getPolygonVertixes()};
  
  InitWindow(screenWidth, screenHeight, "Convex Polygon Billiards");

  SetTargetFPS(60);

  while (!WindowShouldClose()) 
  {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    
    for (int i = 0; i < vert; ++i) 
    {
      DrawLineV(vertices[i], vertices[(i + 1) % vert], BLACK);
    }

    DrawText("Ciao piccola Sarina!", center.x ,center.y, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
