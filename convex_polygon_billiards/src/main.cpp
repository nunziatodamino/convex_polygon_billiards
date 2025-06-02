#include <raylib.h>
#include "polygon.cpp"
#include "particle.cpp"

int main() 
{
  const int screenWidth = 800;
  const int screenHeight = 600;

  Vector2 center{screenWidth /2.0f, screenHeight/2.0f};
  const int vert{13};
  const float radius{225.0};
  const float apothem{radius * cos(PI/vert)};
  Polygon poly(center, vert, radius);
  std::vector<Vector2> vertices{poly.getPolygonVertices()};

  int n_particles {500};

  std::vector<Particle> particles{};

  for (int j = 0; j < n_particles; ++j) 
  {
    Particle particle(center, apothem);
    particles.push_back(particle);
  }  

  InitWindow(screenWidth, screenHeight, "Convex Polygon Billiards");
  SetTargetFPS(60);
  while (!WindowShouldClose()) 
  {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    
    for (int i = 0; i < vert; ++i) 
    {
      DrawLineV(vertices[i], vertices[(i + 1) % vert], BLACK);
    }


    float dt = GetFrameTime();
    for (int j = 0; j < n_particles; ++j) 
    {
      particles[j].update(dt, vertices);   
      Vector2 coordinates = particles[j].getPosition();
      DrawCircleV(coordinates, 4.0f, RED);
    }  

    const char* message = "Ciao piccola Sarina pipi!";
    int fontSize = 20;
    int textWidth = MeasureText(message, fontSize);
    DrawText(message, center.x - textWidth / 2, center.y - fontSize / 2, fontSize, BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
