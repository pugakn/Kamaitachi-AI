#pragma once
#include <vector>
#include "kt_vector.h"
namespace Kamaitachi {
  class DataMatrix {
  public:
    DataMatrix() = default;
    ~DataMatrix() = default;


    DataMatrix(std::vector<std::vector<float>> matrix);

    /**
    *	@param _scalar
    *	 All the elements of the matrix are initialized to this value.
    */
    DataMatrix(float _scalar, int _rows, int _cols ) : DataMatrix(DataVector(_scalar, _cols), _rows) {}

    /**
    *	@param _vec
    *	 All the rows of the matrix are initialized to this vector.
    */
    DataMatrix(const DataVector& _vec, int _rows);

    void Resize(const size_t _rows, const size_t _cols);

    void AddColumn(const size_t _pos, const float value, const int _rows = 0);

    void AddColumn(const size_t _pos, const std::vector<float>& value);

    void AddRow(const size_t _pos, const float value);

    DataVector GetColumn(const size_t _pos) const;

    /**
    *	@param row
    *	 The index of the row.
    *
    * @return
    *	  A reference to the element at the [row] position.
    */
     DataVector& operator[](size_t row)
    {
      //DR_ASSERT(row < _rows);
      return m_elements[row];
    }

    /**
    *	@param row
    *	 The index of the row.
    *
    * @return
    *	  A const reference to the element at the [row] position.
    */
     const DataVector& operator[](size_t row) const
    {
      //DR_ASSERT(row < _rows);

      return m_elements[row];
    }

    /**
    *	@return
    *	  The number of rows in the matrix.
    */
     size_t Rows() const
    {
      return m_elements.size();
    }

    /**
    * @return
    *	  The number of columns in the matrix.
    */
     size_t Cols() const
    {
       if (m_elements.size()) {
         return m_elements.back().Features();
       }
       return 0;
    }

    /**
    *	@return
    *	  The matrix transposed.
    *
    */
     DataMatrix transpose() const
    {
      DataMatrix transposed;
      transposed.Resize(Cols(),Rows());
      for (int iRow = 0; iRow < Rows(); ++iRow) {
        for (int iCol = 0; iCol < Cols(); ++iCol) {
          transposed[iCol][iRow] = m_elements[iRow][iCol];
        }
      }
      return transposed;
    }

     DataMatrix Adjoint() const
     {
       DataMatrix adj;
       adj.Resize(Cols(), Rows());
       if (Rows() == 1)
       {
         adj[0][0] = 1;
         return adj;
       }

       DataMatrix temp;
       temp.Resize(Rows(),Cols());
       int sign = 1;

       for (int i = 0; i < Rows(); i++)
       {
         for (int j = 0; j < Cols(); j++)
         {
           temp = DataMatrix::GetCofactor(*this, i, j, Rows());
           sign = ((i + j) % 2 == 0) ? 1 : -1;
           adj[j][i] = (sign)*(Determinant(temp, Rows() - 1));
         }
       }
       return adj;
     }

     /**
     *	@return
     *	  The matrix inverted.
     *
     */
     DataMatrix Inverse() const;

    /**
    * @return
    *	  A pointer to the first element of the matrix.
    */
     float* ptr()
    {
      return m_elements[0].ptr();
    }

    /**
    * @return
    *	  A constant pointer to the first element of the matrix.
    */
     const float* ptr() const
    {
      return m_elements[0].ptr();
    }

    /**
    *	This overload performs the multiplication assignment by scalar
    *	to each row of the matrix.
    *
    *	@param scalar
    *	 Right side operand (a scalar)
    *
    *	@return
    *	  A reference to (*this).
    */
     DataMatrix& operator*=(float scalar)
    {
      for (auto& row : m_elements) {
        row *= scalar;
      }

      return *this;
    }

    /**
    *	This overload performs the division assignment by scalar
    *	to each row of the matrix.
    *
    *	@param scalar
    *	 Right side operand (a scalar)
    *
    *	@return
    *	  A reference to (*this).
    */
     DataMatrix& operator/=(float scalar)
    {
      return *this *= (1.f / scalar);
    }

    /**
    *	This overload performs a memberwise equality comparision.
    *
    * @param rhs
    *  Right operand (a matrice of the same size with which the rows
    *	 are compared).
    *
    *	@return
    *	  True if all rows of *this matrix are equal to all rows of rhs
    *	  matrix, false otherwise.
    *
    */
     bool operator==(const DataMatrix& rhs)
    {
      //Compares each element in the first range (m_elements.begin()-m_elements.end())
      //to each element in the second range(rhs.m_elements.begin()-m_elements.end()
      return std::equal(m_elements.begin(),
        m_elements.end(),
        rhs.m_elements.begin(),
        rhs.m_elements.end());
    }

    /**
    *	This overload performs a memberwise inequality comparision.
    *
    * @param rhs
    *  Right operand (a matrice of the same size with which the rows
    *	 are compared).
    *
    *	@return
    *	  True if a row of *this matrix is unequal to a row of rhs
    *	  matrix, false otherwise.
    *
    */
     bool operator!=(const DataMatrix& rhs)
    {
      return !(*this == rhs);
    }
  private:
    static DataMatrix GetCofactor(const DataMatrix& A, int p, int q, int n)
    {
      int i = 0, j = 0;
      DataMatrix ret;
      ret.Resize(n, n);
      for (int row = 0; row < n; row++)
      {
        for (int col = 0; col < n; col++)
        {
          if (row != p && col != q)
          {
            ret[i][j++] = A[row][col];
            if (j == n - 1)
            {
              j = 0;
              i++;
            }
          }
        }
      }
      return ret;
    }
    static int Determinant(const DataMatrix& A, int n)
    {
      int D = 0;
      if (n == 1)
        return A[0][0];

      DataMatrix temp;
      temp.Resize(A.Rows(), A.Cols());

      int sign = 1;

      for (int f = 0; f < n; f++)
      {
        temp = DataMatrix::GetCofactor(A, 0, f, n);
        D += sign * A[0][f] * Determinant(temp, n - 1);
        sign = -sign;
      }
      return D;
    }

    std::vector<DataVector> m_elements;
  };

  /**
  * This overload performs the vector-matrix product.
  *
  * @param lhs
  *  Left side operand (a vector with N elements).
  *
  * @param rhs
  *  Right side operand (a matrix with N rows and M columns).
  *
  * @return
  *	The transformed vector.
  */
  static  DataVector operator*(const DataVector lhs, const DataMatrix& rhs)
  {
    DataVector temp;
    temp.Resize(rhs.Cols());
    DataMatrix rhsTransposed = rhs.transpose();
    for (int iCol = 0; iCol < rhs.Cols(); ++iCol) {
      temp[iCol] = lhs.dot(rhsTransposed[iCol]);
    }
    return temp;
  }

  /**
  *	This overload performs the matrix-vector product.
  *
  * @param lhs
  *  Left side operand (a matrix)
  *
  *	@param rhs
  *	 Right side operand (a vector with _cols number of elements)
  *	 elements.
  *
  *	@return
  *	  The transformed vector.
  */
  static  DataVector operator*(const DataMatrix& lhs, const DataVector rhs)
  {
    DataVector temp;
    temp.Resize(lhs.Rows());
    for (int iRow = 0; iRow < lhs.Rows(); ++iRow) {
      temp[iRow] = rhs.dot(lhs[iRow]);
    }
    return temp;
  }

  /**
  * This overload performs the multiplication of each row of matrix
  * by scalar.
  *
  * @param matrix
  *  Left side operand (a matrix with N rows and M columns).
  *
  * @param scalar
  *  Right side operand (a scalar).
  *
  * @return
  *	The transformed matrix.
  */
  static  DataMatrix operator*(DataMatrix matrix, float scalar)
  {
    return matrix *= scalar;
  }

  /**
  * This overload performs the multiplication of each row of matrix
  * by scalar.
  *
  * @param scalar
  *  Left side operand (a scalar).
  *
  * @param matrix
  *  Right side operand (a matrix with N rows and M columns).
  *
  * @return
  *	The transformed matrix.
  */
  static  DataMatrix operator*(float scalar, const DataMatrix& matrix)
  {
    return matrix * scalar;
  }

  /**
  * This overload performs the division of each row of matrix
  * by scalar.
  *
  * @param matrix
  *  Left side operand (a matrix with N rows and M columns).
  *
  * @param scalar
  *  Right side operand (a scalar).
  *
  * @return
  *	The transformed matrix.
  */
  static DataMatrix operator/(DataMatrix matrix, float scalar)
  {
    return matrix /= scalar;
  }

  /**
  * This overload performs the matrices product.
  *
  * @param lhs
  *  Left size operand (a matrix of N rows x M columns).
  *
  * @param rhs
  *  Right side operand (a matrix of M rows x P columns).
  *
  * @return
  *   The matrices product (a matrix of N rows x P columns).
  */
  static DataMatrix operator*(const DataMatrix& lhs, const DataMatrix& rhs)
  {
    DataMatrix temp;
    temp.Resize(lhs.Rows(), rhs.Cols());
    DataMatrix rhsTransposed = rhs.transpose();

    for (int iRows = 0; iRows < lhs.Rows(); ++iRows) {
      for (int iCols = 0; iCols < rhs.Cols(); ++iCols) {
        temp[iRows][iCols] = lhs[iRows].dot(rhsTransposed[iCols]);
      }
    }

    return temp;
  }
}