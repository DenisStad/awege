//
//  Editor.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Editor_hpp
#define Editor_hpp

#include "Toolbar.hpp"
#include "MainArea.hpp"

class Editor {
  
public:
  
  Editor();
  
private:
  
  std::shared_ptr<Toolbar> toolbar;
  std::shared_ptr<MainArea> content;
  
};

#endif /* Editor_hpp */
