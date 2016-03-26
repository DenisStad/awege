//
//  TextureAtlas.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 29/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef TextureAtlas_hpp
#define TextureAtlas_hpp

#include "Rectangle.h"
#include "Image.hpp"

namespace Engine {
  struct TextureNode {
    TextureNode* child[2];
    Engine::Rectangle rect;
  };
  
  
  class TextureAtlas {
    
  public:
    
    void insert(Image image);
    
  };
}

#endif /* TextureAtlas_hpp */
