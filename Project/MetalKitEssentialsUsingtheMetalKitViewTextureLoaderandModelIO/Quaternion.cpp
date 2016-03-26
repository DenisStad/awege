//
//  Quaternion.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Quaternion.hpp"
#include "Vector.h"
#include "Angle.hpp"
#include <math.h>

Engine::Quaternion Engine::Quaternion::AxisAngle(Engine::Vector3 axis, Engine::Angle angle)
{
  auto normalized = axis.normalized();
  float s = sinf(angle.radians()/2.0f);
  Quaternion q;
  
  q.m[0] = normalized.x() * s;
  q.m[1] = normalized.y() * s;
  q.m[2] = normalized.z() * s;
  q.m[3] = cosf(angle.radians()/2.0f);
  
  return q;
}

Engine::Quaternion Engine::Quaternion::operator*(Quaternion other)
{
  Quaternion newQuaternion;
  newQuaternion.m[0] = m[3] * other.m[3] - m[0] * other.m[0] - m[1] * other.m[1] - m[2] * other.m[2];
  newQuaternion.m[1] = m[3] * other.m[0] + m[0] * other.m[3] + m[1] * other.m[2] - m[2] * other.m[1];
  newQuaternion.m[2] = m[3] * other.m[1] + m[1] * other.m[3] + m[2] * other.m[0] - m[0] * other.m[2];
  newQuaternion.m[3] = m[3] * other.m[2] + m[2] * other.m[3] + m[0] * other.m[1] - m[1] * other.m[0];
  return newQuaternion;
}

float Engine::Quaternion::x()
{
  return m[0];
}

float Engine::Quaternion::y()
{
  return m[1];
}

float Engine::Quaternion::z()
{
  return m[2];
}

float Engine::Quaternion::w()
{
  return m[3];
}
