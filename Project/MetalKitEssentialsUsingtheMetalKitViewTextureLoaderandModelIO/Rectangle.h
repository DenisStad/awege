//
//  Rectangle.h
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 29/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Rectangle_h
#define Rectangle_h

#include "Vector.h"

namespace Engine {

class Rectangle {
  
  Vector2 position;
  Vector2 size;
  
public:
  
  Rectangle()
  {
  }
  
  Rectangle(Vector2 position, Vector2 size)
  :
  position(position),
  size(size)
  {
  }
  
  void setPosition(Vector2 newPosition)
  {
    position.x(newPosition.x());
    position.y(newPosition.y());
  }
  
  Vector2& getPosition()
  {
    return position;
  }
  
  void setSize(Vector2 newSize)
  {
    size.x(newSize.x());
    size.y(newSize.y());
  }
  
  Vector2& getSize()
  {
    return size;
  }
  
};
  
}

#endif /* Rectangle_h */
