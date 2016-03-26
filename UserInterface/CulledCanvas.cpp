//
//  CulledCanvas.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 21/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "CulledCanvas.hpp"

void CulledCanvas::clearRect(PlainFrame rect, Color color)
{
  Canvas::clearRect(rect.intersection({ { 0, 0 }, size }), color);
}

void CulledCanvas::drawPixel(PlainPosition position, Color color)
{
  if (position.x >= 0 && position.y >= 0 && position.x < size.w && position.y < size.h) {
    Canvas::drawPixel(position, color);
  }
}

//void CulledCanvas::drawLine(PlainPosition p1, PlainPosition p2, float width, Color color)
//{
//  int minX = (p1.x < p2.x ? p1.x : p2.x) - width;
//  int minY = (p1.y < p2.y ? p1.y : p2.y) - width;
//  int maxX = (p1.x > p2.x ? p1.x : p2.x) + width;
//  int maxY = (p1.y > p2.y ? p1.y : p2.y) + width;
//  ensureFrame({{minX, minY}, {maxX - minX, maxY - minY}});
//  
//  Canvas::drawLine(convert(p1), convert(p2), width, color);
//}

void CulledCanvas::drawRect(PlainFrame rect, Color color)
{
  Canvas::drawRect(rect.intersection({ { 0, 0 }, size }), color);
}
