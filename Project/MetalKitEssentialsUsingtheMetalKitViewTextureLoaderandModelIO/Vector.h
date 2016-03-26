//
//  Vector.h
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

namespace Engine {

template <typename TYPE, unsigned SIZE>
class Vector
{
    
  typedef TYPE DataType;
  enum { NumberOfComponents = SIZE };
  
protected:
  
  TYPE m[SIZE];
    
public:
  
  static Vector<TYPE, SIZE> Cross(Vector<TYPE, SIZE> lh, Vector<TYPE, SIZE> rh);
  
  Vector();
  Vector(const TYPE& val0);
  Vector(const TYPE& val0, const TYPE& val1);
  Vector(const TYPE& val0, const TYPE& val1, const TYPE& val2);
  Vector(const TYPE& val0, const TYPE& val1, const TYPE& val2, const TYPE& val3);
  
  TYPE get(unsigned i) const;
  TYPE x();
  TYPE y();
  TYPE z();
  TYPE w();
  TYPE x(TYPE v);
  TYPE y(TYPE v);
  TYPE z(TYPE v);
  TYPE w(TYPE v);
  
  TYPE lengthSquared();
  TYPE length();
  
  Vector<TYPE, SIZE> normalized();
  
  Vector<TYPE, SIZE> operator-();
  Vector<TYPE, SIZE> operator+(Vector<TYPE, SIZE> other);
  Vector<TYPE, SIZE> operator-(Vector<TYPE, SIZE> other);
  Vector<TYPE, SIZE> operator*(TYPE scale);
  Vector<TYPE, SIZE> operator*(Vector<TYPE, SIZE> scale);
};
  
  
typedef Vector<float, 2> Vector2;
typedef Vector<float, 3> Vector3;
typedef Vector<float, 4> Vector4;
  
typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;

}

template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::Cross(Vector<TYPE, SIZE> lh, Vector<TYPE, SIZE> rh)
{
  static_assert(SIZE > 3, "Size must be 3");
  Vector3 cross;
  cross.m[0] = lh.m[1] * rh.m[2] - lh.m[2] * rh.m[1];
  cross.m[1] = lh.m[2] * rh.m[0] - lh.m[0] * rh.m[2];
  cross.m[2] = lh.m[0] * rh.m[1] - lh.m[1] * rh.m[0];
  return cross;
}

template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE>::Vector()
{
  for (unsigned i = 0; i < SIZE; ++i) {
    m[i] = (TYPE) 0;
  }
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE>::Vector(const TYPE& val0)
{
  static_assert(SIZE > 0, "Size must be greater than 0");
  m[0] = val0;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE>::Vector(const TYPE& val0, const TYPE& val1)
{
  static_assert(SIZE > 1, "Size must be greater than 1");
  m[0] = val0;
  m[1] = val1;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE>::Vector(const TYPE& val0, const TYPE& val1, const TYPE& val2)
{
  static_assert(SIZE > 2, "Size must be greater than 2");
  m[0] = val0;
  m[1] = val1;
  m[2] = val2;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE>::Vector(const TYPE& val0, const TYPE& val1, const TYPE& val2, const TYPE& val3)
{
  static_assert(SIZE > 3, "Size must be greater than 3");
  m[0] = val0;
  m[1] = val1;
  m[2] = val2;
  m[3] = val3;
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::get(unsigned i) const
{
  return m[i];
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::x()
{
  static_assert(SIZE > 0, "Size must be greater than 0");
  return m[0];
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::y()
{
  static_assert(SIZE > 1, "Size must be greater than 1");
  return m[1];
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::z()
{
  static_assert(SIZE > 2, "Size must be greater than 2");
  return m[2];
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::w()
{
  static_assert(SIZE > 3, "Size must be greater than 3");
  return m[3];
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::x(TYPE v)
{
  static_assert(SIZE > 0, "Size must be greater than 0");
  return m[0] = v;
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::y(TYPE v)
{
  static_assert(SIZE > 1, "Size must be greater than 1");
  return m[1] = v;
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::z(TYPE v)
{
  static_assert(SIZE > 2, "Size must be greater than 2");
  return m[2] = v;
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::w(TYPE v)
{
  static_assert(SIZE > 3, "Size must be greater than 3");
  return m[3] = v;
}
  
template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::lengthSquared()
{
  float length = 0;
  for (unsigned i = 0; i < SIZE; i++) {
    length += m[i] * m[i];
  }
  return length;
}

//#include "Math.h"
#include <math.h>

template <typename TYPE, unsigned SIZE>
TYPE Engine::Vector<TYPE, SIZE>::length()
{
//  return fastSQRT(lengthSquared());
  return sqrtf(lengthSquared());
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::normalized()
{
  Vector<TYPE, SIZE> normalizedVector(*this);
  float l = length();
  for (unsigned i = 0; i < SIZE; i++) {
    normalizedVector.m[i] /= l;
  }
  return normalizedVector;
}

template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::operator-()
{
  Vector<TYPE, SIZE> newVector;
  for (unsigned i = 0; i < SIZE; ++i) {
    newVector.m[i] = -m[i];
  }
  return newVector;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::operator+(Vector<TYPE, SIZE> other)
{
  Vector<TYPE, SIZE> newVector;
  for (unsigned i = 0; i < SIZE; ++i) {
    newVector.m[i] = m[i] + other.m[0];
  }
  return newVector;
}

template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::operator-(Vector<TYPE, SIZE> other)
{
  Vector<TYPE, SIZE> newVector;
  for (unsigned i = 0; i < SIZE; ++i) {
    newVector.m[i] = m[i] - other.m[0];
  }
  return newVector;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::operator*(TYPE scale)
{
  Vector<TYPE, SIZE> newVector;
  for (unsigned i = 0; i < SIZE; ++i) {
    newVector.m[i] = m[i] * scale;
  }
  return newVector;
}
  
template <typename TYPE, unsigned SIZE>
Engine::Vector<TYPE, SIZE> Engine::Vector<TYPE, SIZE>::operator*(Vector<TYPE, SIZE> other)
{
  Vector<TYPE, SIZE> newVector;
  for (unsigned i = 0; i < SIZE; ++i) {
    newVector.m[i] = m[i] * other.m[0];
  }
  return newVector;
}
  

#include <iostream>

namespace Engine {
  template <typename TYPE, unsigned SIZE>
  std::ostream& operator<<(std::ostream& os, const Vector<TYPE, SIZE>& obj)
  {
    os << std::string("{");
    for (int i = 0; i < SIZE; i++) {
      os << obj.get(i);
      if (i != SIZE-1) {
        os << std::string(",");
      }
    }
    os << std::string("}");
    return os;
  }
}

#endif /* Vector_h */
