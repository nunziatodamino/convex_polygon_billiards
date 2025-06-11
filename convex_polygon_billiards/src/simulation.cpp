#include <raylib.h>
#include <iostream>
#include "polygon.cpp"
#include "particle.cpp"


struct simulationParam
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  int nVertices;
  int nParticles;
  const Vector2 center{screenWidth / 2.0f, screenHeight / 2.0f};
  const float polygon_radius{225.0};
  float apothem;
  
  void apothemEval()
  {
    apothem = polygon_radius * std::cos(PI / nVertices);
  }
};

void initWindow()
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Convex Polygon Billiards");
  SetTargetFPS(60);
}

void particlesInit(float nParticles, Vector2 center, const float apothem, std::vector<Particle>& particles)
{
  for (int j = 0; j < nParticles; ++j)
  {
    Particle particle(center, apothem);
    particles.push_back(particle);
  }
  particleSystemInit(particles, center, apothem);
}

void drawPolygon(int nVertices, std::vector<Vector2>& vertices)
{
  for (int i = 0; i < nVertices; ++i)
  {
    DrawLineV(vertices[i], vertices[(i + 1) % nVertices], BLACK);
  }
}

void drawParticles (std::vector<Particle>& particles, int nParticles, std::vector<Vector2> vertices)
{
  const float dt = 1.0f/120.0f;
  for (int j = 0; j < nParticles; ++j)
  {
    particles[j].update(dt, vertices, particles);
    Vector2 coordinates = particles[j].getPosition();
    float particles_radius = particles[j].getRadius();
    DrawCircleV(coordinates, particles_radius, RED);
  }
}

int userAskNumber(const char* text) 
{
  std::string input = "";
  int userNumber = 0;
  bool inputDone = false;

  while (!inputDone && !WindowShouldClose()) {
      BeginDrawing();
      ClearBackground(SKYBLUE);

      // Handle input
      int key = GetCharPressed();
      while (key > 0) {
          if (std::isdigit(key)) 
          {
            input += (char)key;
          } 
          else if (key == KEY_BACKSPACE && !input.empty()) 
          {
            input.pop_back();
          }
          key = GetCharPressed();
      }
      if (IsKeyPressed(KEY_ENTER) && !input.empty()) 
      {
        userNumber = std::stoi(input);
        inputDone = true;
      }

      // Draw input UI
      DrawText(text, 100, 100, 20, DARKGRAY);
      DrawText(input.c_str(), 100, 140, 30, MAROON);

      EndDrawing();
    }

    return userNumber;
}

void simulation()
{
  simulationParam sysParam{};
  sysParam.nVertices = userAskNumber("Enter number of vertices (3-20) (Press ENTER to confirm):");
  Polygon polygon(sysParam.center, sysParam.nVertices, sysParam.polygon_radius);
  std::vector<Vector2> vertices{polygon.getPolygonVertices()};
  std::vector<Particle> particles{};
  sysParam.apothemEval();
  sysParam.nParticles = userAskNumber("Enter number of particles (1-200) (Press ENTER to confirm):");
  particlesInit(sysParam.nParticles, sysParam.center, sysParam.apothem, particles);
  
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    drawPolygon(sysParam.nVertices, vertices);
    drawParticles(particles, sysParam.nParticles, vertices);
    EndDrawing();
  }
}