#pragma once
#include <vector>
#include <numeric>
#include <functional>
namespace Kamaitachi {
  struct Statisttics
  {
    static float Mean(const std::vector<float>& data) {
      return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static float SampleVariance(const std::vector<float>& data, float mean) {
        float besselCorrection = 1.0f / (data.size() - 1);
        float sum = 0.0f;
        for (size_t i = 0; i < data.size(); i++)
        {
          float temp = data[i] - mean;
          sum += temp * temp;
        }
        return sum * besselCorrection;
    }

    static float SampleStandarDeviation(const std::vector<float>& data, float mean) {
      return std::sqrt(SampleVariance(data,mean));
    }

    static float PopulationVariance(const std::vector<float>& data, float mean) {
      float term = 1.0f / (data.size());
      float sum = 0.0f;
      for (size_t i = 0; i < data.size(); i++)
      {
        float temp = data[i] - mean;
        sum += temp * temp;
      }
      return sum * term;
    }

    static float PopulationStandarDeviation(const std::vector<float>& data, float mean) {
      return std::sqrt(PopulationVariance(data, mean));
    }

    static void GradientDescent(std::function<float(const std::vector<float>& params,
                                                    const std::vector<std::vector<float>>& x, 
                                                    const std::vector<float>& y, 
                                                    const float j)> costFunctionDerivate,
                                const std::vector<std::vector<float>>& x,
                                const std::vector<float>& y,
                                const float learningRate,
                                const int iterations,
                                std::vector<float>& params) {

      for (size_t i = 0; i < iterations; i++)
      {
        std::vector<float> tempParams = params;
        for (size_t j = 0; j < params.size(); j++)
        {
          float term = costFunctionDerivate(params, x, y, j) * learningRate;
          tempParams[j] = params[j] - term;
        }
        params = tempParams;
      }
    }

  };
}