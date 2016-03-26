//
//  Length.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Length.hpp"

Length::Length()
:
value(0)
{
}

Length::Length(const float &value)
:
value(value)
{
  
}

Length::operator float() const
{
  return value;
}

/*
#include "Length.hpp"
#include "Window.hpp"

Length* Length::Pixels(float numPixels)
{
  auto length = new Length();
  length->type = LengthTypePixels;
  length->value = numPixels;
  return length;
}

Length* Length::Points(float points, Window* window)
{
  auto length = new Length();
  length->type = LengthTypePoints;
  length->window = window;
  length->value = points;
  return length;
}

Length* Length::Fraction(float fraction, Length* otherLength)
{
  auto length = new Length();
  length->type = LengthTypeFraction;
  length->value = fraction;
  length->parentLength = otherLength;
  if (otherLength != nullptr) {
    otherLength->childLengths.push_back(length);
  }
  return length;
}

Length::Length()
:
parentLength(nullptr),
window(nullptr),
type(LengthTypePixels),
value(0)
{
}

Length::~Length()
{
  
}

float Length::fraction(Length* otherLength)
{
  switch (type) {
    case LengthTypeFraction:
      if (parentLength == otherLength) {
        return value;
      }
      if (otherLength == nullptr) {
        return value;
      }
      if (isPixelsDeterminable() && otherLength->isPixelsDeterminable()) {
        return pixels() / otherLength->pixels();
      } if (isAncestor(otherLength)) {
        auto iterator = this;
        float fraction = 1;
        while (iterator != otherLength) {
          if (iterator->type != LengthTypeFraction) {
            return 0;
          }
          fraction *= iterator->value;
          iterator = iterator->parentLength;
        }
        return fraction;
      } else if (isDescendant(otherLength)) {
        auto iterator = otherLength;
        float fraction;
        while (iterator != this) {
          if (iterator->type != LengthTypeFraction) {
            return 0;
          }
          fraction *= 1.0f / iterator->value;
          iterator = iterator->parentLength;
        }
        return fraction;
      }
      return 0;
    case LengthTypePoints:
      if (isPixelsDeterminable() && otherLength->isPixelsDeterminable()) {
        return pixels() / otherLength->pixels();
      }
      return 0;
      
    case LengthTypePixels:
      if (otherLength == nullptr) {
        return 0;
      }
      auto otherPixels = otherLength->pixels();
      if (otherPixels == 0) {
        return 0;
      }
      return value / otherPixels;
  }
}

float Length::fractionOfParent()
{
  return fraction(parentLength);
}

Length* Length::getParentLength()
{
  return parentLength;
}

//float Length::points()
//{
//  
//}

float Length::pixels()
{
  switch (type) {
    case LengthTypePixels:
      return value;
    
    case LengthTypePoints:
      if (window != nullptr) {
        return window->getScaleFactor() * value;
      }
      {
        auto parent = parentLength;
        while (parent != nullptr) {
          if (parent->window != nullptr) {
            return window->getScaleFactor() * value;
          }
          parent = parent->parentLength;
        }
      }
      return 0;
      
    case LengthTypeFraction:
      if (parentLength == nullptr) {
        return 0;
      }
      return value * parentLength->pixels();
  }
}

bool Length::isAncestor(Length *possibleAncestor)
{
  if (parentLength == possibleAncestor) {
    return true;
  }
  if (parentLength == nullptr) {
    return false;
  }
  return parentLength->isAncestor(possibleAncestor);
}

bool Length::isDescendant(Length *possibleDescendant)
{
  if (possibleDescendant == nullptr) {
    return false;
  }
  return possibleDescendant->isAncestor(this);
}

bool Length::isPixelsDeterminable()
{
  switch (type) {
    case LengthTypePixels:
      return true;
    
    case LengthTypePoints:
      if (window != nullptr) {
        return true;
      }
      
    case LengthTypeFraction:
      if (parentLength == nullptr) {
        return false;
      }
      return parentLength->isPixelsDeterminable();
  }
}
*/