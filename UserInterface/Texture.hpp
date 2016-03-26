//
//  Texture.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Canvas.hpp"
#include <string>

namespace Engine {
  
  class Texture {
    
    PlainSize size;
    void* textureId;
    
    Texture(void* textureId);
    
  public:
    
    static Texture FromFile(std::string filename);
    
    Texture(PlainSize size);
    ~Texture();
    
    PlainSize getSize();
    void setDataInRegion(PlainFrame region, unsigned char *data);
    
    void* getRawTexture();
    
  };
  
}

#endif /* Texture_hpp */
