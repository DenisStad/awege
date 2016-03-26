//
//  Label.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 26/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Label.hpp"
#include "Log.hpp"

Engine::UI::Label::Label(String text)
:
text(text)
{
}

Engine::UI::Label::String Engine::UI::Label::getText()
{
  return text;
}

void Engine::UI::Label::setText(String text)
{
  this->text = text;
}

void Engine::UI::Label::render()
{
  DevLog("Render label", text);
  drawRect(Rectangle(Vector2(10, 10), Vector2(100, 100)), Engine::Color::RGB(1, 0, 0, 0.5f));
}