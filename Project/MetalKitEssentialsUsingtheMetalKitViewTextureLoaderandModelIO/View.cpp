//
//  View.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 26/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "View.hpp"
#include "World.hpp"
#include "UIElement.hpp"
#include "Entity.hpp"
#include "UserInterface.hpp"

Engine::UI::View::View()
{
  auto entityPtr = Entity::Create();
  if (auto entity = entityPtr.lock()) {
    uiElement = entity->addComponent<UIElement>(this).lock().get();
  }
}

Engine::UI::UIElement* Engine::UI::View::getUIElement()
{
  return uiElement;
}

void Engine::UI::View::render()
{
  DevLog("Render view");
}

void Engine::UI::View::setNeedsRendering()
{
  needsRenderUpdate = true;
}

void Engine::UI::View::setNeedsRendering(bool needsRendering)
{
  needsRenderUpdate = needsRendering;
}

bool Engine::UI::View::needsRendering()
{
  return needsRenderUpdate;
}

void Engine::UI::View::addSubView(View* view)
{
  if (auto entity = getUIElement()->getEntity().lock()) {
    if (auto otherEntity = view->getUIElement()->getEntity().lock()) {
      entity->addChild(otherEntity);
    }
  }
}

void Engine::UI::View::setFrame(Rectangle newFrame)
{
  setPosition(newFrame.getPosition());
  setSize(newFrame.getSize());
}

void Engine::UI::View::setPosition(Vector2 position)
{
  frame.setPosition(position);
}

void Engine::UI::View::setSize(Vector2 size)
{
  setNeedsRendering();
  frame.setSize(size);
}

Engine::Rectangle Engine::UI::View::getFrame()
{
  return frame;
}

Engine::Vector2 Engine::UI::View::getPosition()
{
  return frame.getPosition();
}

Engine::Vector2 Engine::UI::View::getSize()
{
  return frame.getSize();
}


void Engine::UI::View::removeFromParentView()
{
}