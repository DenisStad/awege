//
//  Toolbar.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Toolbar.hpp"

Toolbar::Toolbar()
{
  setBackgroundColor(Color::RGBA(0.4, 0.1, 0.1, 0.1));
}

void Toolbar::parentFrameDidUpdate(awege::Frame parentFrame)
{
  setFrame({ { 0, 0 }, { parentFrame.size.width, 30 } });
}