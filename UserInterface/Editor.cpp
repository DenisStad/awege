//
//  Editor.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Editor.hpp"
#include "UserInterface.hpp"
#include "FileNavigator.hpp"

Editor::Editor()
{
  
  toolbar = std::shared_ptr<Toolbar>(new Toolbar());
  UserInterface::SharedUserInterface().addView(toolbar);
  
  content = std::shared_ptr<MainArea>(new MainArea());
  UserInterface::SharedUserInterface().addView(content);
  
  auto nav = new FileNavigator();
  content->addSubView(nav->getView());
}