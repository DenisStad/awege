//
//  Angle.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Angle.hpp"
#include <math.h>

Engine::Angle Engine::Angle::Degrees(float degrees)
{
  Angle angle;
  angle.degreesValue = degrees;
  return angle;
}

Engine::Angle Engine::Angle::Radians(float radians)
{
  Angle angle;
  angle.degreesValue = radians / M_PI * 180.0f;
  return angle;
}

float Engine::Angle::degrees() const
{
  return degreesValue;
}

float Engine::Angle::radians() const
{
  return degreesValue / 180.0f * M_PI;
}