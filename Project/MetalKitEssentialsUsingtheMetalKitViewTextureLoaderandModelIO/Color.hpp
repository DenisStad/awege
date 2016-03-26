//
//  Color.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

namespace Engine {
 
  class Color {
    float r;
    float g;
    float b;
    float a;
    
  public:
    static Color RGB(float r, float g, float b, float a);
    static Color HSV(float h, float s, float v, float a);
    
    void setRGB(float r, float g, float b);
    void setAlpha(float a);
    
    float red();
    float green();
    float blue();
    float alpha();
  };
  
}

#endif /* Color_hpp */
