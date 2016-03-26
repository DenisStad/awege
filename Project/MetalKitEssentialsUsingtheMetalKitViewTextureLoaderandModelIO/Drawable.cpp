//
//  Drawable.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Drawable.hpp"
#include "Log.hpp"
#include "Window.hpp"
#include <math.h>

void Engine::Drawable::drawPoint(Vector2 point, Color color)
{
  int x = roundf(point.x() * Window::SharedWindow().getScaleFactor());
  int y = roundf(point.y() * Window::SharedWindow().getScaleFactor());
  if (x < 0 || x > dataSize.x()) {
    return;
  }
  if (y < 0 || y > dataSize.y()) {
    return;
  }
  
  if (cullingEnabled) {
    if (x < viewFrame.getPosition().x() || x > viewFrame.getPosition().x() + viewFrame.getSize().x()) {
      return;
    }
    if (y < viewFrame.getPosition().y() || y > viewFrame.getPosition().y() + viewFrame.getSize().y()) {
      return;
    }
  }
  data[(y * (int) dataSize.x() + x) * 4 + 0] = color.red() * 255;
  data[(y * (int) dataSize.x() + x) * 4 + 1] = color.green() * 255;
  data[(y * (int) dataSize.x() + x) * 4 + 2] = color.blue() * 255;
  data[(y * (int) dataSize.x() + x) * 4 + 3] = color.alpha() * 255;
}

void Engine::Drawable::drawLine(Vector2 start, Vector2 end, float width, Color color)
{
  
}

void Engine::Drawable::drawRect(Rectangle rect, Color color)
{
  for (float y = rect.getPosition().y(); y < rect.getPosition().y() + rect.getSize().y(); y += 1.0f/Window::SharedWindow().getScaleFactor()) {
    for (float x = rect.getPosition().x(); x < rect.getPosition().x() + rect.getSize().x(); x += 1.0f/Window::SharedWindow().getScaleFactor()) {
      drawPoint(Vector2(x, y), color);
    }
  }
}