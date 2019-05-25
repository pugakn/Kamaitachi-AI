#pragma once
#include <vector>
#include "kt_statistics.h"
#include "kt_matrix.h"
#include "kt_vector.h"
namespace Kamaitachi {
  class LinearRegressionTrainer {
  public:
    LinearRegressionTrainer() = default;
    ~LinearRegressionTrainer() = default;

    /**
    * x must contains a matrix[i,j] where i indicates index of the traning example
    * and j indicates the feature in the ith traning example.
    */
    void TrainWithNormalEquation(const DataMatrix& x,
                                 const DataVector& y);

    /**
    * x must contains a matrix[i,j] where i indicates index of the traning example
    * and j indicates the feature in the ith traning example.
    */
    void TrainWithGradientDescent(const DataMatrix& x,
                                  const DataVector& y,
                                  const int iterations,
                                  const float learningRate, 
                                  const bool meanNormalization = false);

    /**
    * \Return: The y value of the Hypothesis using xi parameters and the
    * previous trained parameters.
    */
    float Predict(const DataVector& xi);

   DataVector GetParams();

    /**
    * x must contains a bideimentional array [i,j] where i indicates index of the traning example
    * and j indicates the feature in the ith traning example.
    * \Return: a float number indicating the cost using the parameters
    */
    static float GetCost(const DataVector& params,
                         const DataMatrix& x,
                         const DataVector& y);
  private:
    float m_sd;
    float m_mean;
    bool m_usingMeanNormailation = false;
    /**
    * a vector of parameters containing "θi" Where :
    * y = θ0 * X0 + θ1 * X1 + θ2 * X2 and X0 is always equal to 1
    */
    DataVector m_params;

    static DataVector CostDerivate(const DataVector& params,
                              const DataMatrix& x,
                              const DataVector& y);

    static DataVector Hypothesis(const DataVector& params,
                                 const DataMatrix& x);

    static float Hypothesis(const DataVector& params,
                            const DataVector& xi);
  };
}