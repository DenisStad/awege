//
//  Color.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Color.hpp"

Color Color::RGBA(float r, float g, float b, float a)
{
  Color color;
  if (r < 0) {
    r = 0;
  }
  if (r > 1) {
    r = 1;
  }
  color.m[0] = r * 255.0f;
  
  if (g < 0) {
    g = 0;
  }
  if (g > 1) {
    g = 1;
  }
  color.m[1] = g * 255.0f;
  
  if (b < 0) {
    b = 0;
  }
  if (b > 1) {
    b = 1;
  }
  color.m[2] = b * 255.0f;
  
  if (a < 0) {
    a = 0;
  }
  if (a > 1) {
    a = 1;
  }
  color.m[3] = a * 255.0f;
  
  return color;
}

Color::Color()
{
  m[0] = 0;
  m[1] = 0;
  m[2] = 0;
  m[3] = 0;
}

unsigned char Color::r()
{
  return m[0];
}

unsigned char Color::g()
{
  return m[1];
}

unsigned char Color::b()
{
  return m[2];
}

unsigned char Color::a()
{
  return m[3];
}