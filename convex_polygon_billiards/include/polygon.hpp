#pragma once
#include <raylib.h>
#include <cmath>
#include <vector>

class Polygon
{
  private:
    Vector2 m_center;
    int m_sides;
    std::vector<Vector2> m_vertices;
    float m_radius;
  public:
    Polygon(Vector2 center, int sides, float radius)
    :m_center{center}
    ,m_sides{sides}
    ,m_radius{radius}
    {  
      setPolygonVertices();
    };
    ~Polygon()
    {
    };
    
    void setPolygonVertices()
    {
      for (int k = 0; k < m_sides; ++k) 
      {
        double angle = 2.0 * PI * k / m_sides;
        float x = m_center.x + m_radius * cos(angle);
        float y = m_center.y + m_radius * sin(angle);
        m_vertices.push_back({x, y});
      }
    }
    std::vector<Vector2> getPolygonVertices()
    {
      return m_vertices;
    }

};
