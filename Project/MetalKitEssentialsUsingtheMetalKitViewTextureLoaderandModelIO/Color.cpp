//
//  Color.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Color.hpp"

Engine::Color Engine::Color::RGB(float r, float g, float b, float a)
{
  Color color;
  color.setRGB(r, g, b);
  color.setAlpha(a);
  return color;
}

void Engine::Color::setRGB(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
}

void Engine::Color::setAlpha(float a)
{
  this->a = a;
}

//Engine::Color Engine::Color::HSV(float h, float s, float v, float a)
//{
//  
//}

float Engine::Color::red()
{
  return r;
}

float Engine::Color::green()
{
  return g;
}

float Engine::Color::blue()
{
  return b;
}

float Engine::Color::alpha()
{
  return a;
}