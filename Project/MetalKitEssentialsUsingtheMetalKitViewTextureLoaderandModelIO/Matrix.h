//
//  Matrix.h
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

namespace Engine {

template <typename TYPE, unsigned SIZE> class Vector;
typedef Vector<float, 3> Vector3;
class Quaternion;
class Angle;

template <typename TYPE, unsigned ROWS, unsigned COLUMNS>
class Matrix {
  
  TYPE m[COLUMNS][ROWS];
  
public:
  
  static Matrix<TYPE, ROWS, COLUMNS> Identity();
  
};

  
  /*
template <typename TYPE>
class Matrix<TYPE, 3, 4> {
  
  TYPE m[4][3];
  
public:
  
  static Matrix<TYPE, 3, 4> Identity();
  static Matrix<TYPE, 3, 4> Translation(Engine::Vector3 translation);
  static Matrix<TYPE, 3, 4> Rotation(Engine::Quaternion rotation);
  static Matrix<TYPE, 3, 4> PerspectiveLH(const Angle fov, const float aspectRatio, const float nearZ, const float farZ);
  
  
  Matrix<TYPE, 3, 4>();
  TYPE get(unsigned row, unsigned column) const;
  TYPE* getRawData();
  
};
  
   */
  
template <typename TYPE>
class Matrix<TYPE, 4, 4> {
    
  TYPE m[4][4];
    
public:
    
  static Matrix<TYPE, 4, 4> Identity();
  static Matrix<TYPE, 4, 4> Translation(Engine::Vector3 translation);
  static Matrix<TYPE, 4, 4> Rotation(Engine::Quaternion rotation);
  static Matrix<TYPE, 4, 4> Scale(Engine::Vector3 scale);
  static Matrix<TYPE, 4, 4> PerspectiveLH(const Angle fov, const float aspectRatio, const float nearZ, const float farZ);
  static Matrix<TYPE, 4, 4> LookAtLH(Engine::Vector3 position, Engine::Vector3 target, Engine::Vector3 up);
    
    
  Matrix<TYPE, 4, 4>();
  TYPE get(unsigned row, unsigned column) const;
  TYPE* getRawData();
  
  Matrix<TYPE, 4, 4> transposed();
  Matrix<TYPE, 4, 4> inverted();
  
  Matrix<TYPE, 4, 4> operator*(Matrix<TYPE, 4, 4> other);
    
};



typedef Matrix<float, 3, 4> Matrix3x4;
typedef Matrix<float, 4, 4> Matrix4x4;
  
}

#include "Vector.h"
#include "Quaternion.hpp"
#include "Angle.hpp"
#include <math.h>

template <typename TYPE, unsigned ROWS, unsigned COLUMNS>
Engine::Matrix<TYPE, ROWS, COLUMNS> Engine::Matrix<TYPE, ROWS, COLUMNS>::Identity()
{
  Matrix<TYPE, ROWS, COLUMNS> matrix;
  for (unsigned c = 0; c < COLUMNS; c++) {
    for (unsigned r = 0; r < ROWS; r++) {
      if (c == r) {
        matrix.m[c][r] = (TYPE) 1;
      } else {
        matrix.m[c][r] = (TYPE) 0;
      }
    }
  }
  return matrix;
}
/*
template <typename TYPE>
Engine::Matrix<TYPE, 3, 4>::Matrix()
{
  m[0][0] = 0;
  m[0][1] = 0;
  m[0][2] = 0;
  
  m[1][0] = 0;
  m[1][1] = 0;
  m[1][2] = 0;
  
  m[2][0] = 0;
  m[2][1] = 0;
  m[2][2] = 0;
  
  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
}

template <typename TYPE>
Engine::Matrix<TYPE, 3, 4> Engine::Matrix<TYPE, 3, 4>::Identity()
{
  Matrix<TYPE, 3, 4> matrix;
  matrix.m[0][0] = (TYPE) 1;
  matrix.m[1][1] = (TYPE) 1;
  matrix.m[2][2] = (TYPE) 1;
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 3, 4> Engine::Matrix<TYPE, 3, 4>::Translation(Engine::Vector3 translation)
{
  auto matrix = Identity();
  matrix.m[3][0] = (TYPE) translation.x();
  matrix.m[3][1] = (TYPE) translation.y();
  matrix.m[3][2] = (TYPE) translation.z();
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 3, 4> Engine::Matrix<TYPE, 3, 4>::Rotation(Engine::Quaternion rotation)
{
  TYPE _2xx = 2.0f * rotation.x() * rotation.x();
  TYPE _2yy = 2.0f * rotation.y() * rotation.y();
  TYPE _2zz = 2.0f * rotation.z() * rotation.z();
  
  TYPE _2xy = 2.0f * rotation.x() * rotation.y();
  TYPE _2xz = 2.0f * rotation.x() * rotation.z();
  TYPE _2xw = 2.0f * rotation.x() * rotation.w();
  
  TYPE _2yw = 2.0f * rotation.y() * rotation.w();
  TYPE _2yz = 2.0f * rotation.y() * rotation.z();
  TYPE _2zw = 2.0f * rotation.z() * rotation.w();
  
  
  Matrix<TYPE, 3, 4> matrix;
  
  matrix.m[0][0] = 1.0f - _2yy - _2zz;
  matrix.m[0][1] = _2xy + _2zw;
  matrix.m[0][2] = _2xz - _2yw;
  
  matrix.m[1][0] = _2xy - _2zw;
  matrix.m[1][1] = 1.0f - _2xx - _2zz;
  matrix.m[1][2] = _2yz + _2xw;
  
  matrix.m[2][0] = _2xz + _2yw;
  matrix.m[2][1] = _2yz - _2xw;
  matrix.m[2][2] = 1.0f - _2xx - _2yy;
  
//  matrix.m[3][3] = 1.0f;
  
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 3, 4> Engine::Matrix<TYPE, 3, 4>::PerspectiveLH(const Angle fov, const float aspectRatio, const float nearZ, const float farZ)
{
  Matrix<TYPE, 3, 4> matrix;
  
  float yScale = 1.0f / tanf(fov.radians() * 0.5f);
  float xScale = yScale / aspectRatio;
  float q = farZ / (farZ - nearZ);
  
  matrix.m[0][0] = xScale;
  matrix.m[1][1] = yScale;
  matrix.m[2][2] = q;
//  matrix.m[2][3] = 1.0f;
  matrix.m[3][2] = q * -nearZ;
  
  return matrix;
}

template <typename TYPE>
TYPE Engine::Matrix<TYPE, 3, 4>::get(unsigned row, unsigned column) const
{
  return m[column][row];
}

template <typename TYPE>
TYPE* Engine::Matrix<TYPE, 3, 4>::getRawData()
{
  return &m[0][0];
}
*/


template <typename TYPE>
Engine::Matrix<TYPE, 4, 4>::Matrix()
{
  m[0][0] = 0;
  m[0][1] = 0;
  m[0][2] = 0;
  m[0][3] = 0;
  
  m[1][0] = 0;
  m[1][1] = 0;
  m[1][2] = 0;
  m[1][3] = 0;
  
  m[2][0] = 0;
  m[2][1] = 0;
  m[2][2] = 0;
  m[2][3] = 0;
  
  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
  m[3][3] = 0;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::Identity()
{
  Matrix<TYPE, 4, 4> matrix;
  matrix.m[0][0] = (TYPE) 1;
  matrix.m[1][1] = (TYPE) 1;
  matrix.m[2][2] = (TYPE) 1;
  matrix.m[3][3] = (TYPE) 1;
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::Translation(Engine::Vector3 translation)
{
  auto matrix = Identity();
  matrix.m[3][0] = (TYPE) translation.x();
  matrix.m[3][1] = (TYPE) translation.y();
  matrix.m[3][2] = (TYPE) translation.z();
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::Rotation(Engine::Quaternion rotation)
{
  TYPE _2xx = 2.0f * rotation.x() * rotation.x();
  TYPE _2yy = 2.0f * rotation.y() * rotation.y();
  TYPE _2zz = 2.0f * rotation.z() * rotation.z();
  
  TYPE _2xy = 2.0f * rotation.x() * rotation.y();
  TYPE _2xz = 2.0f * rotation.x() * rotation.z();
  TYPE _2xw = 2.0f * rotation.x() * rotation.w();
  
  TYPE _2yw = 2.0f * rotation.y() * rotation.w();
  TYPE _2yz = 2.0f * rotation.y() * rotation.z();
  TYPE _2zw = 2.0f * rotation.z() * rotation.w();
  
  
  Matrix<TYPE, 4, 4> matrix;
  
  matrix.m[0][0] = 1.0f - _2yy - _2zz;
  matrix.m[0][1] = _2xy + _2zw;
  matrix.m[0][2] = _2xz - _2yw;
  
  matrix.m[1][0] = _2xy - _2zw;
  matrix.m[1][1] = 1.0f - _2xx - _2zz;
  matrix.m[1][2] = _2yz + _2xw;
  
  matrix.m[2][0] = _2xz + _2yw;
  matrix.m[2][1] = _2yz - _2xw;
  matrix.m[2][2] = 1.0f - _2xx - _2yy;
  
    matrix.m[3][3] = 1.0f;
  
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::Scale(Engine::Vector3 scale)
{
  Matrix<TYPE, 4, 4> matrix;
  matrix.m[0][0] = (TYPE) scale.x();
  matrix.m[1][1] = (TYPE) scale.y();
  matrix.m[2][2] = (TYPE) scale.z();
  matrix.m[3][3] = (TYPE) 1;
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::PerspectiveLH(const Angle fov, const float aspectRatio, const float nearZ, const float farZ)
{
  Matrix<TYPE, 4, 4> matrix;
  
  float yScale = 1.0f / tanf(fov.radians() * 0.5f);
  float xScale = yScale / aspectRatio;
  float q = farZ / (farZ - nearZ);
  
  matrix.m[0][0] = xScale;
  matrix.m[1][1] = yScale;
  matrix.m[2][2] = q;
  matrix.m[2][3] = 1.0f;
  matrix.m[3][2] = q * -nearZ;
  
  return matrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::LookAtLH(Engine::Vector3 position, Engine::Vector3 target, Engine::Vector3 up)
{
  auto f = (target - position).normalized();
  up = up.normalized();
  
  auto s = Vector3::Cross(f, up);
  auto u = Vector3::Cross(s, f);
  
  Matrix<TYPE, 4, 4> m;
  
  m.m[0][0] = s.x();
  m.m[1][0] = s.y();
  m.m[2][0] = s.z();
  
  m.m[0][1] = u.x();
  m.m[1][1] = u.y();
  m.m[2][1] = u.z();
  
  m.m[0][2] = -f.x();
  m.m[1][2] = -f.y();
  m.m[2][2] = -f.z();
  
  m.m[3][3] = 1;
  
  Matrix<TYPE, 4, 4> t = Matrix<TYPE, 4, 4>::Translation(-position);
  
  return m * t;
}

template <typename TYPE>
TYPE Engine::Matrix<TYPE, 4, 4>::get(unsigned row, unsigned column) const
{
  return m[column][row];
}

template <typename TYPE>
TYPE* Engine::Matrix<TYPE, 4, 4>::getRawData()
{
  return &m[0][0];
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::transposed()
{
  Matrix<TYPE, 4, 4> newMatrix;
  
  newMatrix.m[0][0] = m[0][0];
  newMatrix.m[0][1] = m[1][0];
  newMatrix.m[0][2] = m[2][0];
  newMatrix.m[0][3] = m[3][0];
  
  newMatrix.m[1][0] = m[0][1];
  newMatrix.m[1][1] = m[1][1];
  newMatrix.m[1][2] = m[2][1];
  newMatrix.m[1][3] = m[3][1];
  
  newMatrix.m[2][0] = m[0][2];
  newMatrix.m[2][1] = m[1][2];
  newMatrix.m[2][2] = m[2][2];
  newMatrix.m[2][3] = m[3][2];
  
  newMatrix.m[3][0] = m[0][3];
  newMatrix.m[3][1] = m[1][3];
  newMatrix.m[3][2] = m[2][3];
  newMatrix.m[3][3] = m[3][3];
  
  return newMatrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::inverted()
{
//  float det = m[0][0] * m[1][1] * m[2][2] * m[3][3]  +  m[0][0] * m[1][2] * m[2][3] * m[3][1]  +  m[0][0] * m[1][3] * m[2][1] * m[3][2]
//            + m[0][1] * m[1][0] * m[2][3] * m[3][2]  +  m[0][1] * m[1][2] * m[2][0] * m[3][3]  +  m[0][1] * m[1][3] * m[2][2] * m[3][0]
//            + m[0][2] * m[1][0] * m[2][1] * m[3][3]  +  m[0][2] * m[1][1] * m[2][3] * m[3][0]  +  m[0][2] * m[1][3] * m[2][0] * m[3][1]
  
  auto copy = Matrix<TYPE, 4, 4>(*this);
  Matrix<TYPE, 4, 4> newMatrix = Matrix<TYPE, 4, 4>::Identity();
  for (int i = 0; i < 4; i++) {
    float f = copy.m[i][i];
    copy.m[0][i] /= f;
    copy.m[1][i] /= f;
    copy.m[2][i] /= f;
    copy.m[3][i] /= f;
    
    newMatrix.m[0][i] /= f;
    newMatrix.m[1][i] /= f;
    newMatrix.m[2][i] /= f;
    newMatrix.m[3][i] /= f;
    
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        continue;
      }
      float c = copy.m[i][j];
      
      copy.m[0][j] -= c * copy.m[0][i];
      copy.m[1][j] -= c * copy.m[1][i];
      copy.m[2][j] -= c * copy.m[2][i];
      copy.m[3][j] -= c * copy.m[3][i];
      
      newMatrix.m[0][j] -= c * newMatrix.m[0][i];
      newMatrix.m[1][j] -= c * newMatrix.m[1][i];
      newMatrix.m[2][j] -= c * newMatrix.m[2][i];
      newMatrix.m[3][j] -= c * newMatrix.m[3][i];
    }
  }
  return newMatrix;
}

template <typename TYPE>
Engine::Matrix<TYPE, 4, 4> Engine::Matrix<TYPE, 4, 4>::operator*(Matrix<TYPE, 4, 4> other)
{
  Matrix<TYPE, 4, 4> newMatrix;
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      for(int k = 0; k < 4; ++k) {
        newMatrix.m[j][i] += m[k][i] * other.m[j][k];
      }
    }
  }
  return newMatrix;
}




namespace Engine {
  template <typename TYPE, unsigned ROWS, unsigned COLUMNS>
  std::ostream& operator<<(std::ostream& os, const Matrix<TYPE, ROWS, COLUMNS>& obj);
  std::ostream& operator<<(std::ostream& os, const Matrix3x4& obj);
  std::ostream& operator<<(std::ostream& os, const Matrix4x4& obj);
}

#endif /* Matrix_h */
