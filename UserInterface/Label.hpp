//
//  Label.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include "View.hpp"
#include <string>

class Label : public View {
  
public:
  
  Label(std::string text);
  
  void setText(std::string text);
  std::string getText();
  
  void draw(Canvas* canvas);
  
  awege::Size getNaturalSize();
  
private:
  
  std::string text;
  awege::Size naturalSize;
  
};

#endif /* Label_hpp */
