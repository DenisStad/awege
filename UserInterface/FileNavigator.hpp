//
//  FileNavigator.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef FileNavigator_hpp
#define FileNavigator_hpp

#include "File.hpp"
#include "View.hpp"

class FileNavigator {
  
public:
  
  FileNavigator();
  
  std::shared_ptr<View> getView();
  
private:
  
  std::shared_ptr<View> view;
  File root;
  
  void setupView();
  void addFilesViews();
};

#endif /* FileNavigator_hpp */
