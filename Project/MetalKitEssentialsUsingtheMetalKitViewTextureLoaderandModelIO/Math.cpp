//
//  Math.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 09/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include <stdio.h>

float fastSQRT(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;
  
  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
  
  return 1.0f/y;
}