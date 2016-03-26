//
//  MainArea.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 23/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef MainArea_hpp
#define MainArea_hpp

#include "View.hpp"

class MainArea : public View {
  
public:
  
  MainArea();
  
  void parentFrameDidUpdate(awege::Frame parentFrame);
  
};

#endif /* MainArea_hpp */
