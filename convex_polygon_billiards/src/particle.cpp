#include <raylib.h>
#include <cmath>
#include <vector>

class Particle
{
private:
  Vector2 m_coordinates;
  Vector2 m_velocities;
public:
  Particle(Vector2 coordinates, Vector2 velocities)
  :m_coordinates{coordinates}
  ,m_velocities{velocities}
  {};
  ~Particle(){};
};
