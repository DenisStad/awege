//
//  UserInterface.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "UserInterface.hpp"
#include "Window.hpp"
#include "RenderCommandBuffer.hpp"

void Engine::UI::UserInterface::onCreate()
{
  textureSize = Window::SharedWindow().getSize() * Window::SharedWindow().getScaleFactor();
  textureData = (unsigned char*) malloc((int) textureSize.x() * (int) textureSize.y() * 4 * sizeof(unsigned char));
  
  auto windowSize = Window::SharedWindow().getSize() * Window::SharedWindow().getScaleFactor();
  Vector2i size;
  size.x(windowSize.x());
  size.y(windowSize.y());
  
  texture = new Texture(size);
  
  uiEntity = getWorld()->createEntity();
}

void Engine::UI::UserInterface::addView(View *view)
{
  if (auto ui = uiEntity.lock()) {
    ui->addChild(std::shared_ptr<Entity>(view->getUIElement()->getEntity()));
  }
}

void Engine::UI::UserInterface::onUpdate()
{
//  RenderCommands commands;
//  commands.setActiveShader();
//  commands.setUniforms();
//  commands.drawObject();
//  RenderCommandBuffer::SharedBuffer().addCommandsToWorkingBuffer(commands);
}