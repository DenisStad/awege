//
//  Toolbar.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Toolbar_hpp
#define Toolbar_hpp

#include "View.hpp"

class Toolbar : public View {
  
public:
  
  Toolbar();

  void parentFrameDidUpdate(awege::Frame parentFrame);
  
};

#endif /* Toolbar_hpp */
