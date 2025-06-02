#include <raylib.h>
#include "rng.cpp"
#include "raymath.h"


bool Vec2checkIntersection (Vector2& P1, Vector2& P2, Vector2& Q1, Vector2& Q2)
{
  // lines intersection is given by the condition
  // P1 + t deltaP = Q1 + u deltaQ 
  // this can happen only if d=Vector2CrossProduct(deltaP, deltaQ) != 0 (not parallel)
  // Solving using Cramer Method
  Vector2 deltaP=Vector2Subtract(P2,P1);
  Vector2 deltaQ=Vector2Subtract(Q2,Q1);
  Vector2 deltaPQ=Vector2Subtract(Q1,P1);
  float denom = Vector2CrossProduct(deltaP, deltaQ);
  if (denom == 0) {return false;}
  float t = Vector2CrossProduct(deltaPQ, deltaQ) / denom;
  float u = Vector2CrossProduct(deltaPQ, deltaP) / denom;
  return t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f;
}

class Particle
{
private:
  const double m_limit_velocity{150.0};
  Vector2 m_coordinates;
  Vector2 m_velocities;
public:
  Particle(Vector2 center, double apothem)
  { 
    // Generation of random position and velocity inside circle of
    // center C=center and radius r = apothem
    Random_number_generator rng;
    m_coordinates.x = center.x + apothem;
    m_coordinates.y = center.y + apothem;
    while (Vector2Distance(m_coordinates, center) > apothem)
    {
       m_coordinates.x = center.x + rng.getRNGinRangeDouble(-apothem,+apothem);
       m_coordinates.y = center.y + rng.getRNGinRangeDouble(-apothem,+apothem);
    }
    m_velocities.x = rng.getRNGinRangeDouble(-m_limit_velocity,+m_limit_velocity);
    m_velocities.y = rng.getRNGinRangeDouble(-m_limit_velocity,+m_limit_velocity);
  };
  ~Particle()
  { 
  };

  Vector2 getPosition() const {return m_coordinates;}
  Vector2 getVelocity() const {return m_velocities;}
   
  void update(float dt, std::vector<Vector2>& vertices )
  {
    Vector2 pos = m_coordinates;
    Vector2 next_pos =  Vector2Add(m_coordinates, Vector2Scale(m_velocities, dt)); 
    size_t n{vertices.size()};
    for (size_t i = 0; i< n; ++i)
    {
      bool collided = false;
      if (Vec2checkIntersection(pos, next_pos, vertices[i],vertices[(i + 1) % n] ))
      {
        Vector2 edge = Vector2Subtract( vertices[(i + 1) % n] , vertices[i]);
        Vector2 perpendicular = { -edge.y, edge.x };
        Vector2 normal = Vector2Normalize(perpendicular);
        m_velocities = Vector2Subtract(m_velocities, Vector2Scale(normal, 2 * Vector2DotProduct(m_velocities, normal)));
        m_coordinates=Vector2Add(pos, Vector2Scale(m_velocities, dt));
        collided = true;
        break;
      }
      if (!collided)
      {
        m_coordinates = next_pos;
      }
    }
  } 
    
};
