//
//  Canvas.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Canvas.hpp"
#include "Color.hpp"
#include <math.h>

PlainPosition::PlainPosition()
:
x(0),
y(0)
{
}

PlainPosition::PlainPosition(int x, int y)
:
x(x),
y(y)
{
}


PlainSize::PlainSize()
:
w(0),
h(0)
{
}

PlainSize::PlainSize(int w, int h)
:
w(w),
h(h)
{
}

PlainFrame::PlainFrame()
:
position({ 0, 0 }),
size({ 0, 0 })
{
}

PlainFrame::PlainFrame(PlainPosition position, PlainSize size)
:
position(position),
size(size)
{
}

bool PlainFrame::intersects(PlainFrame other)
{
  return position.x + size.w > other.position.x && position.x < other.position.x + other.size.w && position.y + size.h > other.position.y && position.y < other.position.y + other.size.h;
}

PlainFrame PlainFrame::intersection(PlainFrame other)
{
  PlainFrame intersection;
  if (position.x > other.position.x) {
    intersection.position.x = position.x;
  } else {
    intersection.position.x = other.position.x;
  }
  if (position.y > other.position.y) {
    intersection.position.y = position.y;
  } else {
    intersection.position.y = other.position.y;
  }
   int max;
  if (position.x + size.w < other.position.x + other.size.w) {
    max = position.x + size.w;
  } else {
    max = other.position.x + other.size.w;
  }
  if (max < intersection.position.x) {
    intersection.size.w = 0;
  } else {
    intersection.size.w = max - intersection.position.x;
  }
  if (position.y + size.h < other.position.y + other.size.h) {
    max = position.y + size.h;
  } else {
    max = other.position.y + other.size.h;
  }
  if (max < intersection.position.y) {
    intersection.size.h = 0;
  } else {
    intersection.size.h = max - intersection.position.y;
  }
  return intersection;
}

int PlainFrame::leftSide()
{
  return position.x;
}
int PlainFrame::rightSide()
{
  return position.x + size.w;
}
int PlainFrame::topSide()
{
  return position.y;
}
int PlainFrame::bottomSide()
{
  return position.y + size.h;
}

bool PlainFrame::liesCompletelyIn(PlainFrame other)
{
  return position.x >= other.position.x && position.y >= other.position.y && rightSide() <= other.rightSide() && bottomSide() <= other.bottomSide();
}

PlainFrame PlainFrame::FrameThatContainsBoth(PlainFrame one, PlainFrame other)
{
  PlainFrame container;
  
  if (one.size.w == 0 && one.size.h == 0) {
    return other;
  }
  
  if (other.size.w == 0 && other.size.h == 0) {
    return one;
  }
  
  container.position.x = one.position.x < other.position.x ? one.position.x : other.position.x;
  container.position.y = one.position.y < other.position.y ? one.position.y : other.position.y;
  
  int max = one.rightSide() > other.rightSide() ? one.rightSide() : other.rightSide();
  container.size.w = max - container.position.x;
  max = one.bottomSide() > other.bottomSide() ? one.bottomSide() : other.bottomSide();
  container.size.h = max - container.position.y;
  
  return container;
}

Canvas::Canvas()
:
data(nullptr),
size({0, 0})
{
}

Canvas::~Canvas()
{
  freeData();
}

void Canvas::freeData()
{
  if (data != nullptr) {
    delete[] data;
  }
}

unsigned char* Canvas::getData()
{
  return data;
}

PlainSize Canvas::getSize()
{
  return size;
}

void Canvas::setSize(PlainSize newSize)
{
//  float* newData = new float[newSize.w * newSize.h * 3]();
//  unsigned int maxY = size.h;
//  if (newSize.y < maxY) {
//    maxY = newSize.y;
//  }
//  unsigned int maxX = size.w;
//  if (newSize.x < maxX) {
//    maxX = newSize.x;
//  }
//  for (int y = 0; y < maxY; y++) {
//    for (int x = 0; x < maxX; x++) {
//      newData[(y * newSize.w + x) * 3 + 0] = data[(y * size.w + x) * 3 + 0];
//      newData[(y * newSize.w + x) * 3 + 1] = data[(y * size.w + x) * 3 + 1];
//      newData[(y * newSize.w + x) * 3 + 2] = data[(y * size.w + x) * 3 + 2];
//    }
//  }
  
  freeData();
  unsigned char* newData = new unsigned char[newSize.w * newSize.h * 4]();
  data = newData;
  size = newSize;
}

void Canvas::copyDataFromCanvas(Canvas canvas, PlainFrame sourceFrame, PlainFrame targetFrame)
{
  
}

void Canvas::clearRect(PlainFrame rect, Color color)
{
//  rect = rect.intersect(PlainFrame({0, 0}, size));
  for (unsigned int y = rect.position.y; y < rect.position.y + rect.size.h; y++) {
    for (unsigned int x = rect.position.x; x < rect.position.x + rect.size.w; x++) {
      data[4 * (size.w * y + x) + 0] = color.r();
      data[4 * (size.w * y + x) + 1] = color.g();
      data[4 * (size.w * y + x) + 2] = color.b();
      data[4 * (size.w * y + x) + 3] = color.a();
    }
  }
}

void Canvas::drawPixel(PlainPosition position, Color color)
{
  float a = color.a() / 255.0f;
  auto ai = 1.0f - a;
  data[4 * (size.w * position.y + position.x) + 0] = ai * data[4 * (size.w * position.y + position.x) + 0] + a * color.r();
  data[4 * (size.w * position.y + position.x) + 1] = ai * data[4 * (size.w * position.y + position.x) + 1] + a * color.g();
  data[4 * (size.w * position.y + position.x) + 2] = ai * data[4 * (size.w * position.y + position.x) + 2] + a * color.b();
//  data[4 * (size.w * position.y + position.x) + 3] = ai * data[4 * (size.w * position.y + position.x) + 3] + a * color.a();//data[4 * (size.w * position.y + position.x) + 3] * color.a();
}

void Canvas::drawPoint(PlainPosition position, float radius, Color color)
{
  for (float y = position.y - radius - 0.5f; y < position.y + radius; y += 1.0f) {
    if (y < 0) {
      continue;
    }
    if (y >= size.h) {
      continue;
    }
    for (float x = position.x - radius - 0.5f; x < position.x + radius; x += 1.0f) {
      if (x < 0) {
        continue;
      }
      if (x >= size.w) {
        continue;
      }
      
      float rx = x - (float)position.x;
      float ry = y - (float)position.y;
      float alpha = radius - sqrtf(rx * rx + ry * ry);
      if (alpha > 0) {
//        alpha *= alpha;
        drawPixel(PlainPosition({static_cast<int>(x), static_cast<int>(y)}), Color::RGBA(color.r(), color.g(), color.b(), (float)color.a()/255.0f * alpha));
      }
    }
  }
}

void Canvas::drawLine(PlainPosition p1, PlainPosition p2, float width, Color color)
{
//  for (int y = p1.y - width; y < position.y + width; y++) {
//    if (y < 0) {
//      continue;
//    }
//    if (y >= size.h) {
//      continue;
//    }
//    for (int x = position.x - width; x < position.x + width; x++) {
//      if (x < 0) {
//        continue;
//      }
//      if (x >= size.w) {
//        continue;
//      }
//      
//      float rx = (float)x - (float)position.x;
//      float ry = (float)y - (float)position.y;
//      float alpha = radius - sqrtf(rx * rx + ry * ry);
//      if (alpha > 0) {
//        alpha *= alpha;
//        drawPixel(PlainPosition({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}), Color::RGBA(color.r(), color.g(), color.b(), (float)color.a()/255.0f * alpha));
//      }
//    }
//  }
}

void Canvas::drawRect(PlainFrame rect, Color color)
{
  for (int y = rect.position.y; y < rect.position.y + rect.size.h; y++) {
    for (int x = rect.position.x; x < rect.position.x + rect.size.w; x++) {
      drawPixel(PlainPosition({x, y}), color);
    }
  }
}

void Canvas::clear(Color color)
{
  clearRect({ { 0, 0 }, size }, color);
}