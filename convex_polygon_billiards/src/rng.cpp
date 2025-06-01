#include <random>

class Random_number
{
private:
  std::mt19937 m_rng;
public:
  Random_number()
  :m_rng(std::random_device{}()){};
  ~Random_number(){};

  double getRNGinRangeDouble(double d_min, double d_max)
  {
    std::uniform_real_distribution<> dis(d_min,d_max);
    double rng = dis(m_rng); 
    return rng; 
  }

};