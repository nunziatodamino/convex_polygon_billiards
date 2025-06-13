#pragma once
#include <random>

class Random_number_generator
{
  private:
    std::mt19937 m_rng;
  public:
    Random_number_generator()
    :m_rng(std::random_device{}()){};
    ~Random_number_generator()
    {
    };

    double getRNGinRangeDouble(double d_min, double d_max)
    {
      std::uniform_real_distribution<> dis(d_min,d_max);
      double rng = dis(m_rng); 
      return rng; 
    }

};