#include <raylib.h>
#include <cmath>
#include <vector>

class Polygon
{
private:
  Vector2 m_center;
  int m_sides;
  std::vector<Vector2> m_vertixes;
  float m_apothema;
public:
  Polygon(Vector2 center, int sides, float apothema)
  :m_center{center}
  ,m_sides{sides}
  ,m_apothema{apothema}
  {  
    setPolygonVertixes();
  };
  ~Polygon()
  {
  };
  
  void setPolygonVertixes()
  {
    for (int k = 0; k < m_sides; ++k) 
    {
      double angle = 2.0 * PI * k / m_sides;
      float x = m_center.x + m_apothema * cos(angle);
      float y = m_center.y + m_apothema * sin(angle);
      m_vertixes.push_back({x, y});
    }
  }
  std::vector<Vector2> getPolygonVertixes()
  {
    return m_vertixes;
  }
};
