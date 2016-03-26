//
//  Drawable.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#include "Rectangle.h"
#include "Color.hpp"

namespace Engine {
  
  class Drawable {
    
    friend class UIElement;
    
  protected:
    
    unsigned char *data;
    Vector2 dataSize;
    Rectangle viewFrame;
    bool cullingEnabled;
    
  public:
    
    void drawPoint(Vector2 point, Color color);
    void drawLine(Vector2 start, Vector2 end, float width, Color color);
    void drawRect(Rectangle rect, Color color);
    
  };
  
}

#endif /* Drawable_hpp */
