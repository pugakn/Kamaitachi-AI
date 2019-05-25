#pragma once
#include <vector>
#include <numeric>
#include <functional>
#include <cmath>
#include <limits>
#include <iostream> //Debug

#include "kt_matrix.h"
#include "kt_vector.h"
namespace Kamaitachi {
  struct FeattureScaling {
    static DataVector MeanNormalizationSd(float _mean, float sd, const DataVector& _features) {
      return (_features - DataVector(_mean, _features.Features())) / sd;
    }

    static DataVector MeanNormalizationRange(float _mean, float range, const DataVector& _features) {
      return (_features - DataVector(_mean, _features.Features())) / range;
    }
  };
  struct FloatUtils {
    static bool Equals(float a, float b) {
      return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
    }
    static bool Equals(float a, float b, float epsilon) {
      return std::fabs(a - b) < epsilon;
    }
  };
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

    static void GradientDescent(std::function<DataVector(const DataVector& params,
                                                    const DataMatrix& x, 
                                                    const DataVector& y)> costFunctionDerivate,
                                const DataMatrix& x,
                                const DataVector& y,
                                const float learningRate,
                                const int iterations,
                                DataVector& params) {

      for (size_t i = 0; i < iterations; i++)
      {
        DataVector tempParams = params;
        tempParams = params - (costFunctionDerivate(params, x, y) * learningRate);
        params = tempParams;
      }
    }

  };
}