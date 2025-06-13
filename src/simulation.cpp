#include <raylib.h>
#include <iostream>
#include "polygon.hpp"
#include "particle.hpp"


struct simulationParam
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  int nVertices;
  int nParticles;
  const Vector2 center{screenWidth / 2.0f, screenHeight / 2.0f};
  const float polygon_radius{250.0};
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
  static float lastTime = 0.0f;
  float currentTime = GetTime();  
  float deltaTime = currentTime - lastTime;
  lastTime = currentTime;
  deltaTime = std::min(deltaTime, 1.0f/100.0f);
  
  for (int j = 0; j < nParticles; ++j)
  {
    particles[j].update(deltaTime, vertices, particles);
    Vector2 coordinates = particles[j].getPosition();
    float particles_radius = particles[j].getRadius();
    DrawCircleV(coordinates, particles_radius, RED);
  }
}

void enforceParticleLimit(const int nVertices, int& nParticles)
{
  // for these values the simulation can populate
  // the polygon safely without crashing
  switch (nVertices)
  {
  case 3:
    if (nParticles>80) nParticles = 80;
    break;
  case 4:
    if (nParticles>120) nParticles = 120;
    break;
  case 5:
    if (nParticles>130) nParticles = 130;
    break;  
  default:
    break;
  }
}

int userAskNumber (const char *text, int min, int max)
{
  std::string input = "";
  int userNumber = 0;
  bool inputDone = false;
  std::string errorMessage = "";

  while (!inputDone && !WindowShouldClose ())
    {
      BeginDrawing ();
      ClearBackground (SKYBLUE);

      int key = GetCharPressed ();
      while (key > 0)
        {
          if (std::isdigit (key))
            {
              input += (char) key;
            }
          key = GetCharPressed ();
        }

      if (IsKeyPressed (KEY_BACKSPACE) && !input.empty ())
        {
          input.pop_back ();
        }

      if (IsKeyPressed (KEY_ENTER) && !input.empty ())
        {
          try
            {
              userNumber = std::stoi (input);
              if (userNumber >= min && userNumber <= max)
                {
                  inputDone = true;
                }
              else
                {
                  errorMessage = "Error, please retry";
                  input = "";
                }
            }
          catch (...)
            {
              errorMessage = "Error, please retry";
              input = "";
            }
        }

      DrawText (text, 100, 100, 20, DARKGRAY);
      DrawText (input.c_str (), 100, 140, 30, MAROON);
      if (!errorMessage.empty ())
        {
          DrawText (errorMessage.c_str (), 100, 180, 20, RED);
        }

      EndDrawing ();
    }

  return userNumber;
}

void simulation()
{
  simulationParam sysParam{};
  sysParam.nVertices = userAskNumber("Enter number of vertices (3-20) (Press ENTER to confirm):", 3, 20);
  Polygon polygon(sysParam.center, sysParam.nVertices, sysParam.polygon_radius);
  std::vector<Vector2> vertices{polygon.getPolygonVertices()};
  std::vector<Particle> particles{};
  sysParam.apothemEval();
  sysParam.nParticles = userAskNumber("Enter number of particles (1-200) (Press ENTER to confirm):", 1, 200);
  enforceParticleLimit(sysParam.nVertices, sysParam.nParticles);
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