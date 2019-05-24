#pragma once
#include <vector>
#include "kt_statistics.h"
namespace Kamaitachi {



  class LinearRegressionTrainer {
    //TODO: 
    //Train();
  public:
    LinearRegressionTrainer() = default;
    ~LinearRegressionTrainer() = default;

    /**
    * x must contains a bideimentional array [i,j] where i indicates index of the traning example
    * and j indicates the feature in the ith traning example.
    */
    void Train(const std::vector<std::vector<float>>& x,
               const std::vector<float>& y,
               const int iterations,
               const float learningRate);

    /**
    * \Return: The y value of the Hypothesis using xi parameters and the 
    * previous trained parameters.
    */
    float Regress(const std::vector<float>& xi);

    /**
    * x must contains a bideimentional array [i,j] where i indicates index of the traning example
    * and j indicates the feature in the ith traning example.
    * \Return: a float number indicating the cost using the parameters
    */
    static float GetCost(const std::vector<float>& params,
                         const std::vector<std::vector<float>>& x,
                         const std::vector<float>& y);
  private:
    /**
    * a vector of parameters containing "θi" Where :
    * y = θ0 * X0 + θ1 * X1 + θ2 * X2 and X0 is always equal to 1
    */
    std::vector<float> m_params;


    static float CostDerivate(const std::vector<float>& params, 
                              const std::vector<std::vector<float>>& x, 
                              const std::vector<float>& y, 
                              const float j);

    static float Hypothesis(const std::vector<float>& params, 
                            const std::vector<float>& xi);
  };
}