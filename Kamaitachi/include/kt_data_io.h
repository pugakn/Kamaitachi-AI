#pragma once

#include <string>
#include <vector>
#include "kt_matrix.h"
namespace Kamaitachi {
  template <class T>
  class DataFile {
  public:
    void Load(std::string path);
    std::vector<T> GetField(int i, int j);
    std::vector<T> GetRow(int i);
    std::vector<T> GetColumn(int j);
    int Rows() const;
    int Cols() const;
  private:
    std::vector<std::vector<T>> m_dataMatrix;
  };
}
#include "../source/kt_data_io.cpp"