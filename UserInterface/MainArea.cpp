//
//  MainArea.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "MainArea.hpp"

MainArea::MainArea()
{
  setBackgroundColor(Color::RGBA(0.1, 0.15, 0.2, 0.3));
}

void MainArea::parentFrameDidUpdate(awege::Frame parentFrame)
{
  setFrame({ { 0, 30 }, { parentFrame.size.width, parentFrame.size.height - 30 } });
}