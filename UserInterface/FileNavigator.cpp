//
//  FileNavigator.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "FileNavigator.hpp"
#include "File.hpp"
#include "Label.hpp"
#include <iostream>

FileNavigator::FileNavigator()
:
root(".")
{
  setupView();
  addFilesViews();
}

std::shared_ptr<View> FileNavigator::getView()
{
  return view;
}

void FileNavigator::setupView()
{
  view = std::shared_ptr<View>(new View());
  view->setFrame({ { 0, 0 }, { 100, 100 } });
}

void FileNavigator::addFilesViews()
{
  auto items = root.listItems();
  
  static int i = 0;
  for (auto item : items) {
    std::cout << (std::string)item << std::endl;
    
    auto itemLabel = std::shared_ptr<Label>(new Label(item));
    view->addSubView(itemLabel);
    itemLabel->setFrame({ {5, 5 + i++ * 30}, itemLabel->getNaturalSize() });
  }
}