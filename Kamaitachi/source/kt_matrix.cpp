#include "kt_matrix.h"
namespace Kamaitachi {
  DataMatrix::DataMatrix(std::vector<std::vector<float>> matrix) {
    m_elements.resize(matrix.size());
    for (size_t i = 0; i < m_elements.size(); i++)
    {
      m_elements[i] = matrix[i];
    }
  }

  DataMatrix::DataMatrix(const DataVector& _vec, int _rows)
  {
    m_elements.resize(_rows);
    for (auto& row : m_elements) {
      row = _vec;
    }
  }
  void DataMatrix::Resize(const size_t _rows, const size_t _cols)
  {
    m_elements.resize(_rows);
    for (size_t i = 0; i < m_elements.size(); i++)
    {
      m_elements[i].Resize(_cols);
    }
  }
  void DataMatrix::AddColumn(const size_t _pos, const float value, const int _rows)
  {
    if (m_elements.size() == 0) {
      m_elements.resize(_rows);
    }
    for (size_t i = 0; i < _rows; i++)
    {
      m_elements[i].AddFeature(_pos, value);
    }
  }
  void DataMatrix::AddColumn(const size_t _pos, const std::vector<float>& value)
  {
    if (m_elements.size() == 0) {
      m_elements.resize(value.size());
    }
    for (size_t i = 0; i < value.size(); i++)
    {
      m_elements[i].AddFeature(_pos, value[i]);
    }
  }
  void DataMatrix::AddRow(const size_t _pos, const float value)
  {
    m_elements.insert(m_elements.begin() + _pos, DataVector(value, Cols()));
  }
  DataVector DataMatrix::GetColumn(const size_t _pos) const
  {
    DataVector temp;
    for (size_t i = 0; i < m_elements.size(); i++)
    {
      temp.AddFeature(i,m_elements[i].GetFeature(_pos));
    }
    return temp;
  }

  DataMatrix DataMatrix::Inverse() const
  {
    DataMatrix inverted;
    float deter = Determinant(*this, Rows());
    //DR_ASSERT(deter != 0);
    DataMatrix adj = Adjoint();
    inverted = adj * (1.f / deter);
    return inverted;
  }
}