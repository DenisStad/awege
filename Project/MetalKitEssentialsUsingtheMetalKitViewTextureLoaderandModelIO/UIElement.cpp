//
//  UIElement.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "UIElement.hpp"
#include "UserInterface.hpp"

Engine::UI::UIElement::UIElement(View* view)
:
view(view)
{
}

void Engine::UI::UIElement::setView(View* view)
{
  this->view = view;
}


void Engine::UI::UIElement::onAttach()
{
  if (view != nullptr) {
    view->setNeedsRendering();
  }
}

void Engine::UI::UIElement::onDetach()
{
  if (view != nullptr) {
    delete view;
  }
}

void Engine::UI::UIElement::update()
{
  if (view != nullptr) {
    if (view->needsRendering()) {
      view->setNeedsRendering(false);
      auto UI = getSystem();
      view->data = UI->textureData;
      view->dataSize = UI->textureSize;
      view->viewFrame = view->getFrame();
      view->render();
      
      UI->texture->setDataInRegion(Rectangle(Vector2(), UI->textureSize), UI->textureData);
    }
  }
}