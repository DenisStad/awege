//
//  Frame.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Frame.hpp"

awege::Frame::Frame()
:
position(0, 0),
size(0, 0)
{
}

awege::Frame::Frame(Position position, Size size)
:
position(position),
size(size)
{
  
}

awege::Size::Size()
:
width(0),
height(0)
{
}

awege::Size::Size(Length width, Length height)
:
width(width),
height(height)
{
}

awege::Position::Position()
:
x(0),
y(0)
{
}

awege::Position::Position(Length x, Length y)
:
x(x),
y(y)
{
}

bool awege::Frame::operator==(const Frame & other)
{
  return position == other.position && size == other.size;
}

bool awege::Position::operator==(const Position & other)
{
  return x == other.x && y == other.y;
}

bool awege::Size::operator==(const Size & other)
{
  return width == other.width && height == other.height;
}


bool awege::Frame::operator!=(const Frame & other)
{
  return position != other.position || size != other.size;
}

bool awege::Position::operator!=(const Position & other)
{
  return x != other.x || y != other.y;
}

bool awege::Size::operator!=(const Size & other)
{
  return width != other.width || height != other.height;
}
