//
//  RenderSystem.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 22/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include "ComponentSystem.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "UniformBufferObject.hpp"
#include "Matrix.h"
#include "RenderComponentAllocator.hpp"
#include "Texture.hpp"

/// Per frame uniforms.
struct EngineFrameUniforms {
  Engine::Matrix4x4 model;
  Engine::Matrix4x4 view;
  Engine::Matrix4x4 projection;
  Engine::Matrix4x4 projectionView;
  Engine::Matrix4x4 normal;
};


class RenderSystem : public Engine::ComponentSystem<Renderer/*, RenderSystemComponentAllocator*/> {
  
  Shader* shader;
  InflightUniformBufferObject frameBuffer;
  UniformBufferObject materialBuffer;
  Engine::Texture texture;
  Engine::Texture normalTexture;
  
  Engine::Matrix4x4 projectionMatrix;
  Engine::Matrix4x4 viewMatrix;
  
  void updateViewProjectionMatrix(Engine::Vector2 size);
  
public:
  RenderSystem();
  ~RenderSystem();
  void onCreate();
  void update();
  
  
  
  /*
   
   C
   C
   C
   C
   Cfi
   
   UUUUUUUUUUUUUUUUUUUUUU
   
   VV
   41
   
   UUUUUUUUUUUUUUUUUUUUUU
   EEEEE
   4   1
   
   Shader
    VBO1
      UB1
      UB2
      UB3
      UB4
    VBO2
      UB1
   
   Shader
    VBO1
      UB1
    VBO2
      UB1
      UB2
      UB3
    VBO3
      UB1
      UB2
    VBO4
      UB1
   
   Transparent stuff
   
   ##############################
   
   Suppose positions are updated already
   
   
   
   */
};

#endif /* RenderSystem_hpp */
