#pragma once
#include <raylib.h>
#include "rng.hpp"
#include "raymath.h"

class Particle
{
  private:
    const double m_limit_velocity{100.0};
    float m_radius;
    Vector2 m_coordinates;
    Vector2 m_velocities;
    Random_number_generator m_rng;
  public:
    Particle(Vector2 center, double apothem)
    { 
      randPosition(center, apothem);
      randVelocity();
      randRadius();
    };
    ~Particle()
    { 
    };

    Vector2 getPosition() const {return m_coordinates;}
    Vector2 getVelocity() const {return m_velocities;}
    float   getRadius()   const {return m_radius;}
    void setPosition(Vector2 position) {m_coordinates = position;}
    void setVelocity(Vector2 velocity) {m_velocities = velocity;}
    void setRadius(float radius) {m_radius = radius;}
    
    void randPosition(Vector2 center, double apothem)
    {       
      m_coordinates.x = center.x + apothem;
      m_coordinates.y = center.y + apothem;
      while (Vector2Distance(m_coordinates, center) > apothem)
      {
        m_coordinates.x = center.x + m_rng.getRNGinRangeDouble(-apothem,+apothem);
        m_coordinates.y = center.y + m_rng.getRNGinRangeDouble(-apothem,+apothem);
      }
    }
    void randVelocity() 
    {
      m_velocities.x = m_rng.getRNGinRangeDouble(-m_limit_velocity,+m_limit_velocity);
      m_velocities.y = m_rng.getRNGinRangeDouble(-m_limit_velocity,+m_limit_velocity);
    }
    void randRadius() {m_radius = m_rng.getRNGinRangeDouble(2.0f, 6.0f);}
    
    void update(float dt, std::vector<Vector2>& vertices , std::vector<Particle>& particles)
    {
      bool collided = false;
      //edgeCollision(collided, dt, vertices);
      edgeCollisionWithRadius(collided, dt, vertices);
      vertexCollision(collided, dt, vertices);
      particlesElasticCollision(collided, dt, particles);
      m_coordinates = Vector2Add(m_coordinates, Vector2Scale(m_velocities, dt));
    } 

    float PointToLineDistance(Vector2 point, Vector2 lineStart, Vector2 lineEnd, float& t_collision)
    {
    Vector2 lineVec = Vector2Subtract(lineEnd, lineStart);
    Vector2 pointVec = Vector2Subtract(point, lineStart);
    float lineLengthSq = Vector2LengthSqr(lineVec);
    if (lineLengthSq == 0.0f){return Vector2Distance(point, lineStart);}
    t_collision = Vector2DotProduct(pointVec, lineVec) / lineLengthSq;
    t_collision = std::max(0.0f, std::min(1.0f, t_collision));
    Vector2 closestPoint = Vector2Add(lineStart, Vector2Scale(lineVec, t_collision));
    return Vector2Distance(point, closestPoint);
    }
    
    void edgeCollisionWithRadius(bool& collided, float dt, std::vector<Vector2>& vertices)
    {
      if(!collided)
      {
      size_t n{vertices.size()}; 
      Vector2 next_pos = Vector2Add(m_coordinates, Vector2Scale(m_velocities, dt));
        for (size_t i = 0; i< n; ++i)
        {
        float t_coll{};
        float distance = PointToLineDistance(m_coordinates, vertices[i],vertices[(i + 1) % n], t_coll);
        if (distance < m_radius)
        {
          float displacement = m_radius- distance;
          Vector2 edge = Vector2Subtract( vertices[(i + 1) % n] , vertices[i]);
          Vector2 collisionPoint = Vector2Add(vertices[i], Vector2Scale(edge, t_coll));
          Vector2 perpendicular = { -edge.y, edge.x };
          Vector2 normal = Vector2Normalize(perpendicular);
          Vector2 collisionNormal = Vector2Normalize(Vector2Subtract(m_coordinates, collisionPoint));
          m_coordinates = Vector2Add(m_coordinates, Vector2Scale(collisionNormal, displacement));
          m_velocities = Vector2Subtract(m_velocities, Vector2Scale(normal, 2 * Vector2DotProduct(m_velocities, normal)));
          collided = true;
          break;
        }
        }  
      } 
    }    

    bool Vec2checkIntersection (float dt, const Vector2& Q1,const Vector2& Q2)
    {
      // lines intersection is given by the condition
      // P1 + t deltaP = Q1 + u deltaQ 
      // this can happen only if d=Vector2CrossProduct(deltaP, deltaQ) != 0 (not parallel)
      // Solving using Cramer Method
      Vector2 P1 = m_coordinates;
      Vector2 P2 = Vector2Add(m_coordinates, Vector2Scale(m_velocities, dt));
      Vector2 deltaP=Vector2Subtract(P2,P1);
      Vector2 deltaQ=Vector2Subtract(Q2,Q1);
      Vector2 deltaPQ=Vector2Subtract(Q1,P1);
      float denom = Vector2CrossProduct(deltaP, deltaQ);
      if (denom == 0) {return false;}
      float t = Vector2CrossProduct(deltaPQ, deltaQ) / denom;
      float u = Vector2CrossProduct(deltaPQ, deltaP) / denom;
      return t >= 0.00f && t <= 1.00f && u >= 0.00f && u <= 1.00f;
    }

    void vertexCollision(bool& collided, float dt, std::vector<Vector2>& vertices )
    {
      if(!collided)
      {
        size_t n{vertices.size()};
        for (size_t i = 0; i< n; ++i)
        {
          if (Vector2Distance(m_coordinates, vertices[i]) < EPSILON)
          {
            Vector2 edge1 = Vector2Normalize(Vector2Subtract(vertices[(i + 1) % n], vertices[i]));
            Vector2 edge2 = Vector2Normalize(Vector2Subtract(vertices[i], vertices[(i + n - 1) % n]));
            Vector2 averageNormal = Vector2Normalize(Vector2Add(edge1, edge2));
            float dot = Vector2DotProduct(m_velocities, averageNormal);
            m_velocities = Vector2Subtract(m_velocities, Vector2Scale(averageNormal, 2.0f * dot));
            collided = true;
            break;
          }
        }
      }
    }
        
    void edgeCollision(bool& collided, float dt, std::vector<Vector2>& vertices)
    {
      if(!collided)
      {
      size_t n{vertices.size()}; 
      Vector2 next_pos = Vector2Add(m_coordinates, Vector2Scale(m_velocities, dt));
        for (size_t i = 0; i< n; ++i)
        {
        if (Vec2checkIntersection(dt, vertices[i],vertices[(i + 1) % n] ))
        {
          Vector2 edge = Vector2Subtract( vertices[(i + 1) % n] , vertices[i]);
          Vector2 perpendicular = { -edge.y, edge.x };
          Vector2 normal = Vector2Normalize(perpendicular);
          m_velocities = Vector2Subtract(m_velocities, Vector2Scale(normal, 2 * Vector2DotProduct(m_velocities, normal)));
          collided = true;
          break;
        }
        }  
      } 
    }
    
    void particlesElasticCollision(bool& collided, float dt, std::vector<Particle>& particles)
    {
      if (!collided)
      {
        size_t n{particles.size()};
        for (size_t i = 0; i < n; ++i)
        {
          Vector2 otherParticlePos = particles[i].getPosition();
          float otherRadius = particles[i].getRadius();
          float distance = Vector2Distance(m_coordinates, otherParticlePos);
          float minDistance = m_radius + otherRadius;
          if (m_coordinates == otherParticlePos) {continue;}
          if (distance < minDistance)
          {
            Vector2 collisionDirection = Vector2Normalize(Vector2Subtract(otherParticlePos, m_coordinates));
            // Overlap resolution
            float overlap = minDistance - distance;
            Vector2 separation = Vector2Scale(collisionDirection, overlap * 0.5f);
            m_coordinates = Vector2Subtract(m_coordinates, separation);
            particles[i].setPosition(Vector2Add(otherParticlePos, separation));
            // Velocity rescaling
            Vector2 otherParticleVel = particles[i].getVelocity();
            float otherParticleRad = particles[i].getRadius();
            float mass1 = m_radius * m_radius;
            float mass2 = otherParticleRad * otherParticleRad;
            Vector2 relativeVel = Vector2Subtract(otherParticleVel, m_velocities);
            float velAlongNormal = Vector2DotProduct(relativeVel, collisionDirection);    
            if (velAlongNormal > 0) {continue;}
            float restitution = 1.0f;
            float impulse = -(1.0f + restitution) * velAlongNormal;
            impulse /= (1.0f / mass1 + 1.0f / mass2);
            Vector2 impulseVector = Vector2Scale(collisionDirection, impulse);
            Vector2 newVel1 = Vector2Subtract(m_velocities, Vector2Scale(impulseVector, 1.0f / mass1));
            Vector2 newVel2 = Vector2Add(otherParticleVel, Vector2Scale(impulseVector, 1.0f / mass2));
            m_velocities=newVel1;      
            particles[i].setVelocity(newVel2);
            collided = true;
          }
        }
      }
    }
};

void particleSystemInit (std::vector<Particle>& particles, Vector2 center, double apothem)
{
  size_t n{particles.size()};
  for (size_t i = 0; i < n; ++i)
  {
    Vector2 x1 = particles[i].getPosition();
    float r1 = particles[i].getRadius();
    Vector2 x2 = particles[(i+1) % n].getPosition();
    float r2 = particles[(i+1) % n].getRadius();
    while (Vector2Distance(x1, x2) < (r1+r2))
    {
      particles[i].randPosition(center, apothem);
    }
  }  
}