#include "kt_regression.h"
#include <functional>
#include <iostream> //Debug
namespace Kamaitachi {
  //void LinearRegression::RegressStatistically(const DataSet& data)
  //{
  //  //Calculate mean
  //  float xMean, yMean;
  //  xMean = Statisttics::Mean(data.x);
  //  yMean = Statisttics::Mean(data.y);

  //  //Calculatte standar deviation
  //  m_standarDeviationX = Statisttics::PopulationStandarDeviation(data.x, xMean);
  //  m_standarDeviationY = Statisttics::PopulationStandarDeviation(data.y, yMean);

  //  //Calculate correlation coeficient (slope)
  //  float sum = 0.0f;
  //  for (size_t i = 0; i < data.x.size(); i++)
  //  {
  //    sum += ((data.x[i] - xMean)/ m_standarDeviationX) * ((data.y[i] - yMean) / m_standarDeviationY);
  //  }
  //  float div = 1.0f / data.x.size();
  //  m_correlationCoefficient = sum * div;
  //  m = (m_standarDeviationX / m_standarDeviationY)* m_correlationCoefficient;
  //  //b = 
  //}

  void LinearRegressionTrainer::Train(const std::vector<std::vector<float>>& x,
                                      const std::vector<float>& y,
                                      const int iterations,
                                      const float learningRate)
  {
    m_params.resize(x.back().size());
   auto m = std::bind(&LinearRegressionTrainer::CostDerivate, 
                      std::placeholders::_1, 
                      std::placeholders::_2, 
                      std::placeholders::_3, 
                      std::placeholders::_4);

    Statisttics::GradientDescent(m,x,y,learningRate,iterations, m_params);
    for (size_t i = 0; i < m_params.size(); i++)
    {
      std::cout << m_params[i] << std::endl;
    }
  }

  float LinearRegressionTrainer::Regress(const std::vector<float>& xi)
  {
    return Hypothesis(m_params,xi);
  }

  float LinearRegressionTrainer::GetCost(const std::vector<float>& params,
                                  const std::vector<std::vector<float>>& x,
                                  const std::vector<float>& y)
  {
    float m = 1.0f / 2.0f*x.size();
    float sum = 0;
    for (size_t i = 0; i < x.size(); i++)
    {
      float temp = Hypothesis(params, x[i]) - y[i];
      sum += temp * temp;
    }
    return m * (sum);
  }

  //------------------------ Used on Gradient Descent ------------------------

  float LinearRegressionTrainer::Hypothesis(const std::vector<float>& params,
                                     const std::vector<float>& xi)
  {
    float ret = 0;
    for (size_t j = 0; j < xi.size(); j++)
    {
      ret += params[j] * xi[j];
    }
    return ret;
  }
  float LinearRegressionTrainer::CostDerivate(const std::vector<float>& params, 
                                       const std::vector<std::vector<float>>& x, 
                                       const std::vector<float>& y, 
                                       const float j)
  {
    float m = 1.0f / x.size();
    float sum = 0;
    for (size_t i = 0; i < x.size(); i++)
    {
      float h = Hypothesis(params, x[i]);
      sum += (h - y[i]) * x[i][j] ;
    }
    return m*sum;
  }
}

