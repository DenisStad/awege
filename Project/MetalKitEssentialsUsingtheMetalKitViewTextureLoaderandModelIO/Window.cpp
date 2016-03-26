//
//  Window.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Window.hpp"
#include "Log.hpp"

Engine::Window& Engine::Window::SharedWindow()
{
  static Window window;
  return window;
}

void Engine::Window::updateScaleFactor(float newScaleFactor)
{
  scaleFactor = newScaleFactor;
  DevLogTag("Platform", "New screen scale factor", newScaleFactor);
}

void Engine::Window::updateSize(Vector2 newSize)
{
  size = newSize;
  DevLogTag("Platform", "New screen size", newSize);
  for (auto updater : updaters) {
    updater(newSize);
  }
}

Engine::Vector2 Engine::Window::getSize()
{
  return size;
}

float Engine::Window::getScaleFactor()
{
  return scaleFactor;
}

void Engine::Window::onSizeUpdate(std::function<void(const Vector2 newSize)> updater)
{
  updaters.push_back(updater);
}