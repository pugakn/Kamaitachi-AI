#ifndef _DATA_IMPL_H
#define _DATA_IMPL_H
#include "kt_data_io.h"
#include <fstream>
#include <sstream>
namespace Kamaitachi {
  template<class T>
  void DataFile<T>::Load(std::string path)
  {
    std::ifstream infile(path);
    while (infile)
    {
      std::string s;
      if (!getline(infile, s)) break;

      std::istringstream ss(s);
      std::vector <T> record;
      while (ss)
      {
        std::string s;
        if (!getline(ss, s, ',')) break;
        std::stringstream tString(s);
        T var;
        tString >> var;
        record.push_back(var);
      }

      m_dataMatrix.push_back(record);
    }
    if (!infile.eof())
    {
      std::cerr << "Error!\n";
    }
  }
  template<class T>
  std::vector<T> DataFile<T>::GetField(int i, int j)
  {
    return std::vector<T>();
  }
  template<class T>
  std::vector<T> DataFile<T>::GetRow(int i)
  {
    return std::vector<T>();
  }
  template<class T>
  std::vector<T> DataFile<T>::GetColumn(int j)
  {
    std::vector<T>column;
    for (size_t i = 0; i < m_dataMatrix.size(); i++)
    {
      column.push_back(m_dataMatrix[i][j]);
    }
    return column;
  }
  template<class T>
  int DataFile<T>::Rows() const{
    return m_dataMatrix.size();
  }
  template<class T>
  int DataFile<T>::Cols() const {
    return m_dataMatrix.back().size();
  }
}

#endif