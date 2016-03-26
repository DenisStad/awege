//
//  Frame.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Frame_hpp
#define Frame_hpp

#include "Length.hpp"

namespace awege {
  
  class Position {
    
  public:
    
    Position();
    Position(Length x, Length y);
    
    Length x;
    Length y;
    
    bool operator==(const Position & other);
    bool operator!=(const Position & other);
    
  };
  
  class Size {
    
  public:
    
    Size();
    Size(Length width, Length height);
    
    Length width;
    Length height;
    
    bool operator==(const Size & other);
    bool operator!=(const Size & other);
    
  };
  
  class Frame {
    
  public:
    
    Frame();
    Frame(Position position, Size size);
    
    Position position;
    Size size;
    
    bool operator==(const Frame & other);
    bool operator!=(const Frame & other);
    
  };

}

#endif /* Frame_hpp */
