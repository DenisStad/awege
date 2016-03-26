//
//  Renderer.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 21/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "Renderer.hpp"
#include "Entity.hpp"
#include "MeshComponent.hpp"
#include "MaterialComponent.hpp"
#include "RenderCommandBuffer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::onAttach()
{
//  materialBuffer.allocateBuffer(sizeof(AAPLMaterialUniforms));
  
  auto entityPtr = getEntity();
  if (auto entity = entityPtr.lock()) {
    auto meshComponentPtr = entity->getComponent<MeshComponent>();
    if (auto meshComponent = meshComponentPtr.lock()) {
      vbo = VBOManager::SharedManager().getVBO(meshComponent->getIdentifier());
    }
    
//    auto materialComponentPtr = entity->getComponent<MaterialComponent>();
//    if (auto materialComponent = materialComponentPtr.lock()) {
//      materialUniforms = (AAPLMaterialUniforms*) materialBuffer.getData();
//      (*materialUniforms).diffuseColor = materialComponent->redColor;
//    }
  }
}

void Renderer::update()
{
//  RenderCommands commands;
//  commands.setActiveUniformBuffer(&materialBuffer, 2);
//  commands.setActiveVertexBuffer(vbo.get(), 0);
//  commands.draw();
//  RenderCommandBuffer::SharedBuffer().addCommandsToWorkingBuffer(commands);
}

void Renderer::onDetach()
{
  
}
