#include "kt_regression.h"
#include <functional>
#include <iostream> //Debug
namespace Kamaitachi {

  void LinearRegressionTrainer::TrainWithNormalEquation(const DataMatrix& x,
                                                        const DataVector& y) {
    m_params = (x.transpose()*x).Inverse() * x.transpose() * y;
  }
  void LinearRegressionTrainer::TrainWithGradientDescent(const DataMatrix& x,
                                      const DataVector& y,
                                      const int iterations,
                                      const float learningRate,
                                      const bool meanNormalization)
  {
    m_usingMeanNormailation = meanNormalization;
    m_params = DataVector(0.0f,x.Cols());
   auto m = std::bind(&LinearRegressionTrainer::CostDerivate, 
                      std::placeholders::_1, 
                      std::placeholders::_2, 
                      std::placeholders::_3);

   if (m_usingMeanNormailation) {
     DataMatrix x2;
     for (size_t i = 0; i < x.Cols(); i++)
     {
       DataVector col = x.GetColumn(i);
       if (i != 0) {
         m_mean = Statisttics::Mean(col.GetStdVector()); 
         m_sd = Statisttics::PopulationStandarDeviation(col.GetStdVector(), m_mean);

         col = FeattureScaling::MeanNormalizationSd(m_mean,m_sd,col);
       }
       x2.AddColumn(i,col.GetStdVector());
     }
     Statisttics::GradientDescent(m, x2, y, learningRate, iterations, m_params);
   }
   else {
     Statisttics::GradientDescent(m, x, y, learningRate, iterations, m_params);
   }

  }

  float LinearRegressionTrainer::Predict(const DataVector& xi)
  {
    if (m_usingMeanNormailation) {
      DataVector xN;
      xN = FeattureScaling::MeanNormalizationSd(m_mean,m_sd,xi);
      return Hypothesis(m_params, xN);
    }
    return Hypothesis(m_params,xi);
  }

  DataVector LinearRegressionTrainer::GetParams() {
    return m_params;
  }

  float LinearRegressionTrainer::GetCost(const DataVector& params,
                                  const DataMatrix& x,
                                  const DataVector& y)
  {
    float m = 1.0f / (2.0f*y.Features());
    DataVector h = Hypothesis(params, x);
    return m *((h-y).dot(h - y));
  }

  //------------------------ Used on Gradient Descent ------------------------

  DataVector LinearRegressionTrainer::Hypothesis(const DataVector& params,
                                                 const DataMatrix& x)
  {
    return x*params;
  }

  float LinearRegressionTrainer::Hypothesis(const DataVector& params,
                                            const DataVector& xi) {
    return xi.dot(params);
  }

  DataVector LinearRegressionTrainer::CostDerivate(const DataVector& params,
                                       const DataMatrix& x, 
                                       const DataVector& y)
  {
    float m = 1.0f / x.Rows();
    DataVector h = Hypothesis(params, x);
    return m * (x.transpose() * (h-y));
  }
}

