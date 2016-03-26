//
//  AutoSizeCanvas.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "AutoSizeCanvas.hpp"
#include "Color.hpp"

void AutoSizeCanvas::clearRect(PlainFrame rect, Color color)
{
  ensureFrame(rect);
  
  Canvas::clearRect(convert(rect), color);
}

void AutoSizeCanvas::drawPixel(PlainPosition position, Color color)
{
  ensureFrame({{position.x, position.y}, {1, 1}});
  
  Canvas::drawPixel(convert(position), color);
}

void AutoSizeCanvas::drawPoint(PlainPosition position, float radius, Color color)
{
  int minX = position.x - radius - 0.5f;
  int minY = position.y - radius - 0.5f;
  int maxX = position.x + radius + 0.5f;
  int maxY = position.y + radius + 0.5f;
  ensureFrame({{minX, minY}, {maxX - minX, maxY - minY}});
  
  Canvas::drawPoint(convert(position), radius, color);
}

void AutoSizeCanvas::drawLine(PlainPosition p1, PlainPosition p2, float width, Color color)
{
  int minX = (p1.x < p2.x ? p1.x : p2.x) - width;
  int minY = (p1.y < p2.y ? p1.y : p2.y) - width;
  int maxX = (p1.x > p2.x ? p1.x : p2.x) + width;
  int maxY = (p1.y > p2.y ? p1.y : p2.y) + width;
  ensureFrame({{minX, minY}, {maxX - minX, maxY - minY}});
  
  Canvas::drawLine(convert(p1), convert(p2), width, color);
}

void AutoSizeCanvas::drawRect(PlainFrame rect, Color color)
{
  ensureFrame(rect);
  
  Canvas::drawRect(convert(rect), color);
}

void AutoSizeCanvas::ensureFrame(PlainFrame requiredFrame)
{
  auto currentCanvasFrame = PlainFrame { positionOffset, size };
  if (!requiredFrame.liesCompletelyIn(currentCanvasFrame)) {
    auto unionFrame = PlainFrame::FrameThatContainsBoth(currentCanvasFrame, requiredFrame);
    resizeDrawFrame(unionFrame);
  }
}

void AutoSizeCanvas::resizeDrawFrame(PlainFrame newFrame)
{
  auto oldFrame = PlainFrame { positionOffset, size };
  auto intersection = oldFrame.intersection(newFrame);
  
  unsigned char* oldData = data;
  data = nullptr;
  setSize(newFrame.size);
  
  for (int y = intersection.position.y; y < intersection.position.y + intersection.size.h; y++) {
    for (int x = intersection.position.x; x < intersection.position.x + intersection.size.w; x++) {
      data[4 * (newFrame.size.w * (y - newFrame.position.y) + (x - newFrame.position.x)) + 0] = oldData[4 * (oldFrame.size.w * (y - oldFrame.position.y) + (x - oldFrame.position.x)) + 0];
      data[4 * (newFrame.size.w * (y - newFrame.position.y) + (x - newFrame.position.x)) + 1] = oldData[4 * (oldFrame.size.w * (y - oldFrame.position.y) + (x - oldFrame.position.x)) + 1];
      data[4 * (newFrame.size.w * (y - newFrame.position.y) + (x - newFrame.position.x)) + 2] = oldData[4 * (oldFrame.size.w * (y - oldFrame.position.y) + (x - oldFrame.position.x)) + 2];
      data[4 * (newFrame.size.w * (y - newFrame.position.y) + (x - newFrame.position.x)) + 3] = oldData[4 * (oldFrame.size.w * (y - oldFrame.position.y) + (x - oldFrame.position.x)) + 3];
    }
  }
  
  delete[] oldData;
  
  positionOffset = newFrame.position;
}

PlainFrame AutoSizeCanvas::currentlyAllocatedFrame()
{
  return { positionOffset, size };
}

PlainFrame AutoSizeCanvas::convert(PlainFrame frame)
{
  frame.position = convert(frame.position);
  return frame;
}

PlainPosition AutoSizeCanvas::convert(PlainPosition position)
{
  position.x -= positionOffset.x;
  position.y -= positionOffset.y;
  return position;
}