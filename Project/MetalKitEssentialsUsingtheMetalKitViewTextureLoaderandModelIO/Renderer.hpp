//
//  Renderer.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Component.hpp"
#include "VBOManager.hpp"
#include "UniformBufferObject.hpp"
#include "AAPLShaderTypes.h"

class RenderSystem;

class Renderer : public Engine::Component<RenderSystem> {
  
  friend class RenderSystem;

  VBOManager::SharedVBOPointer vbo;
  unsigned int perObjectBufferIndex;
//  UniformBufferObject materialBuffer;
//  AAPLMaterialUniforms* materialUniforms;
  
public:
  
  Renderer();
  ~Renderer();
  
  void onAttach();
  void update();
  void onDetach();
};

#endif /* Renderer_hpp */
