#include "kt_vector.h"
namespace Kamaitachi {
  DataVector::DataVector(std::vector<float> vector)
  {
    m_elements.resize(vector.size());
    m_elements = vector;
  }
  DataVector::DataVector(float _scalar, int _cols)
  {
    m_elements.resize(_cols);
    for (auto& element : m_elements) {
      element = _scalar;
    }
  }

  void DataVector::Resize(size_t _cols) {
    m_elements.resize(_cols);
  }

  void DataVector::AddFeature(size_t _pos, float value)
  {
    m_elements.insert(m_elements.begin()+ _pos,value);
  }

  float DataVector::GetFeature(size_t _pos) const
  {
    return m_elements[_pos];
  }

  const std::vector<float>& DataVector::GetStdVector() const
  {
    return m_elements;
  }

  size_t DataVector::Features() const
  {
    return m_elements.size();
  }

  float& DataVector::operator[](size_t index)
  {
    //DR_ASSERT(index < _elements);
    return m_elements[index];
  }

  const float& DataVector::operator[](size_t index) const
  {
    //DR_ASSERT(index < _elements);
    return m_elements[index];
  }

  float DataVector::dot(const DataVector& other) const
  {
    float sum = 0;

    //For each element on the vector
    for (int iElement = 0; iElement < m_elements.size(); ++iElement) {
      sum += m_elements[iElement] * other.m_elements[iElement];
    }

    return sum;
  }

  float DataVector::length() const
  {
    return sqrt(dot(*this));
  }

  float DataVector::lengthSqr() const
  {
    return dot(*this);
  }

  void DataVector::normalize()
  {
    float len = length();
    //DR_ASSERT(len != 0.0f);
    float invLength = 1.f / len;
    operator*=(invLength);
  }

  float* DataVector::ptr()
  {
    return &m_elements[0];
  }

  const float* DataVector::ptr() const
  {
    return &m_elements[0];
  }

  DataVector& DataVector::operator*=(float scalar)
  {
    //For each element on the vector do the multiplication assigment
    for (auto& element : m_elements) {
      element *= scalar;
    }

    return *this;
  }

  DataVector& DataVector::operator/=(float scalar)
  {
    //DR_ASSERT(scalar != 0.0f);
    //Multiply by reciprocal instead of multiple divisions
    float invScalar = 1.f / scalar;
    operator*=(invScalar);
    return *this;
  }

  DataVector& DataVector::operator+=(const DataVector& rhs)
  {
    //For each element on the vector do the addition assigment
    for (int iElement = 0; iElement < m_elements.size(); ++iElement) {
      m_elements[iElement] += rhs.m_elements[iElement];
    }

    return *this;
  }

  DataVector& DataVector::operator-=(const DataVector& rhs)
  {
    //For each element on the vector do the subtraction assigment
    for (int iElement = 0; iElement < m_elements.size(); ++iElement) {
      m_elements[iElement] -= rhs.m_elements[iElement];
    }
    return *this;
  }

  DataVector DataVector::operator-()
  {
    DataVector out;
    out.Resize(m_elements.size());
    for (int i = 0; i < m_elements.size(); ++i) {
      out[i] = -m_elements[i];
    }

    return out;
  }

  bool DataVector::operator==(const DataVector& rhs) const
  {
    //Compares each element in the first range (m_elements.begin()-m_elements.end())
    //to each element in the second range(rhs.m_elements.begin()-m_elements.end()
    return std::equal(m_elements.begin(),
      m_elements.end(),
      rhs.m_elements.begin(),
      rhs.m_elements.end());
  }

  bool DataVector::operator!=(const DataVector& rhs) const
  {
    return !(*this == rhs);
  }
}