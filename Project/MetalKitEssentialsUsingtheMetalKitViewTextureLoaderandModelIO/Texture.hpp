//
//  Texture.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Vector.h"
#include "Rectangle.h"

namespace Engine {
  
  class Texture {
    
    Vector2i size;
    void* textureId;
    
    Texture(void* textureId);
    
  public:
    
    static Texture FromFile(std::string filename);
    
    Texture(Vector2i size);
    ~Texture();
    
    Vector2i getSize();
    void setDataInRegion(Rectangle region, unsigned char *data);
    
    void* getRawTexture();
    
  };
  
}

#endif /* Texture_hpp */
