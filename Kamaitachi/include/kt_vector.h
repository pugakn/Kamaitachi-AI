#pragma once
#include <vector>
#include <algorithm>
namespace Kamaitachi {
  class DataVector
  {
  public:
    /**
    * Default constructor
    */
    DataVector()
    {}

    DataVector(std::vector<float> vector);

    /**
    * Constructor using a scalar value.
    *
    *	@param _scalar
    *	 All the elements of the vector are initialized to this value.
    *
    */
    DataVector(float _scalar,int _dimension);

    /**
    * Number of elements in the vector.
    *
    *	@return
    *   The number of elements the vector contains.
    *
    */
     size_t Features() const;

    void Resize(size_t _cols);

    void AddFeature(size_t _pos, float value);

    float GetFeature(size_t _pos) const;

    const std::vector<float>& GetStdVector()const;

    /**
    * Gets a reference to the specified element from the vector.
    *
    *	@param index
    *	 The index of the element.
    *
    * @return
    *	  A reference to the element at the [index] position.
    */
     float& operator[](size_t index);

    /**
    * Gets a const reference to the specified element from the vector.
    *
    *	@param index
    *	 The index of the element.
    *
    * @return
    *	  A const reference to the element at the [index] position.
    */
     const float& operator[](size_t index) const;

    /**
    * Computes the dot product between 2 vectors.
    *
    *	@param other
    *	 The vector against which the dot product is calculated.
    *
    * @return
    *	  A const reference to the element at the [index] position.
    */
     float dot(const DataVector& other) const;

    /**
    * Computes the length of the vector.
    *
    * @return
    *	  Length of the vector.
    */
     float length() const;

    /**
    * Computes the squared length of the vector.
    *
    * @return
    *	  Squared length of the vector.
    */
     float lengthSqr() const;

    /**
    * Normalize the plane
    *
    */
     void normalize();

    /**
    * Gets a pointer to the first element of the vector.
    *
    * @return
    *	  The pointer to the first element of the vector.
    */
     float* ptr();

    /**
    * Gets a constant pointer to the first element of the vector.
    *
    * @return
    *	  The constant pointer to the first element of the vector.
    */
     const float* ptr() const;

    /**
    *	Overload of binary operator *=
    *
    *	This operator performs a memberwise multiplication by a scalar
    * and assigns the result to *this.
    *
    *	@param scalar
    *	 Right operand (a scalar value).
    *
    * @return
    *	  A reference to the transformed vector (*this).
    *
    */
     DataVector& operator*=(float scalar);

    /**
    *	Overload of binary operator *=
    *
    *	This operator performs a memberwise division by a scalar
    * and assigns the result to *this.
    *
    *	@param scalar
    *	 Right operand (a scalar value).
    *
    * @return
    *	  A reference to the transformed vector (*this).
    *
    */
     DataVector& operator/=(float scalar);

    /**
    *	Overload of binary operator +=.
    *
    *	This operator performs a memberwise addition of both vectors
    * and assigns the result to *this.
    *
    *	@param rhs
    *	 Right operand (a vector with same number of elements).
    *
    * @return
    *	  A reference to the transformed vector (*this).
    *
    */
     DataVector& operator+=(const DataVector& rhs);

    /**
    *	Overload of binary operator +=.
    *
    *	This operator performs a memberwise subtraction of both vectors
    * and assigns the result to *this.
    *
    *	@param rhs
    *	 Right operand (a vector with same number of elements).
    *
    * @return
    *	  A reference to the transformed vector (*this).
    *
    */
     DataVector& operator-=(const DataVector& rhs);

    /**
    *	Overload of unary operator -.
    *
    *	Gets the vector with all of its elements negated.
    *
    * @return
    *	  The vector with negated elements.
    *
    */
     DataVector operator-();

    /**
    * Overload of binary operator ==.
    *
    * This operator performs a memberwise equality comparison.
    *
    * @param rhs
    *  Right operand (a vector with same number of elements).
    *
    *	@return
    *	  True if all elements of *this vector are equal to all elements of rhs
    *	  vector, false otherwise.
    *
    */
     bool operator==(const DataVector& rhs) const;

    /**
    * Overload of binary operator ==.
    *
    * This operator performs a memberwise inequality comparison.
    *
    *	@return
    *	  True if an elements of *this vector is unequal to an elements of rhs
    *	  vector, false otherwise.
    *
    */
     bool operator!=(const DataVector& rhs) const;
  protected:

  private:
    std::vector<float> m_elements;
  };



  //----------------------- Operators override -----------------------

  /**
* Overload of binary operator *.
*
* This operator performs a multiplication of each member of vector by scalar.
*
* @param vector
*  Left operand (a vector).
*
* @param scalar
*  Right operand (a scalar).
*
* @return
*	Memberwise multiplication by scalar.
*
*/
  static  DataVector
    operator*(DataVector vector, float scalar)
  {
    return vector *= scalar;
  }

  /**
  * Overload of binary operator *.
  *
  * This operator performs a multiplication of each member of vector by scalar.
  *
  * @param scalar
  *	Left operand (a scalar).
  *
  * @param vector
  *  Right operand (a vector).
  *
  * @return
  *	Memberwise multiplication by scalar.
  *
  */
  static  DataVector
    operator*(float scalar, const DataVector& vector)
  {
    return vector * scalar;
  }

  /**
  * Overload of binary operator /.
  *
  * This operator performs a division of each member of vector by scalar.
  *
  * @param vector
  *	Left operand (a vector).
  *
  * @param scalar
  *  Right operand (a scalar).
  *
  * @return
  *	Memberwise division by scalar.
  *
  */
  static  DataVector
    operator/(DataVector vector, float scalar)
  {
    //DR_ASSERT(scalar != 0.0f);
    return vector /= scalar;
  }

  /**
  * Overload of binary operator +.
  *
  * This operator performs a memberwise addition of both vectors.
  *
  * @param lhs
  *	Left operand (a vector).
  *
  * @param rhs
  *  Right operand (a scalar).
  *
  * @return
  *	Memberwise addition of both vectors.
  *
  */
  static  DataVector
    operator+(DataVector lhs, const DataVector& rhs)
  {
    return lhs += rhs;
  }

  /**
  * Overload of binary operator -.
  *
  * This operator performs a memberwise subtraction of both vectors.
  *
  * @param lhs
  *	Left operand (a vector).
  *
  * @param rhs
  *  Right operand (a scalar).
  *
  * @return
  *	Memberwise subtraction of both vectors.
  *
  */
  static  DataVector
    operator-(DataVector lhs, const DataVector& rhs)
  {
    return lhs -= rhs;
  }
}