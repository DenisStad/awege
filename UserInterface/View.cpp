//
//  View.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "View.hpp"
#include "Color.hpp"
#include "UserInterface.hpp"

View::View()
:
needsDrawUpdate(true)
{
//  UserInterface::SharedUserInterface()
}

View::~View()
{
}

void View::draw(Canvas* canvas)
{
  canvas->clear();
  canvas->clearRect({ { 0, 0 }, { 1, 1 } }, backgroundColor);
}


void View::addSubView(std::shared_ptr<View> view)
{
  view->removeFromSuperView();
  subViews.insert(view);
  view->parentView = shared_from_this();
  UserInterface::SharedUserInterface().viewTreeWasAdded(view);
}

void View::removeSubView(std::shared_ptr<View> view)
{
  UserInterface::SharedUserInterface().viewTreeWillBeRemoved(view);
  subViews.erase(view);
  view->parentView = std::weak_ptr<View>();
}

void View::removeFromSuperView()
{
  if (auto parent = parentView.lock()) {
    parent->removeSubView(shared_from_this());
  }
}

std::shared_ptr<View> View::getRootView()
{
  if (auto parent = parentView.lock()) {
    return parent->getRootView();
  }
  return shared_from_this();
}

void View::setFrame(awege::Frame newFrame)
{
  if (frame != newFrame) {
    frame = newFrame;
    needsFrameUpdate = true;
    for (auto view : subViews) {
      view->parentFrameDidUpdate(newFrame);
    }
  }
}

void View::parentFrameDidUpdate(awege::Frame parentFrame)
{
}


void View::setBackgroundColor(Color color)
{
  backgroundColor = color;
  setNeedsUpdate();
}

void View::setNeedsUpdate()
{
  needsDrawUpdate = true;
}

void View::setNeedsUpdate(bool newValue)
{
  needsDrawUpdate = newValue;
}

bool View::isCullingEnabled()
{
  return cullingEnabled;
}

void View::setCullingEnabled(bool enabled)
{
  cullingEnabled = enabled;
}