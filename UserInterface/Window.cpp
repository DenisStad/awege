//
//  Window.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Window.hpp"

Window& Window::SharedWindow()
{
  static Window window;
  return window;
}

void Window::updateScaleFactor(float newScaleFactor)
{
  scaleFactor = newScaleFactor;
}

void Window::updateSize(awege::Size newSize)
{
  size = newSize;
  for (auto updater : updaters) {
    updater(newSize);
  }
}

awege::Size Window::getSize()
{
  return size;
}

float Window::getScaleFactor()
{
  return scaleFactor;
}

void Window::onSizeUpdate(std::function<void(const awege::Size newSize)> updater)
{
  updaters.push_back(updater);
}