//
//  RenderSystem.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 22/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "RenderSystem.hpp"
#include "RenderCommandBuffer.hpp"
#include "AAPLShaderTypes.h"
#include "Window.hpp"

#define BUFFER_SIZE 512

RenderSystem::RenderSystem()
:
texture(Engine::Texture::FromFile("/Users/denis/Projects/Awege/BlenderImporter/export_script/gizmo_color_LO.png")),
normalTexture(Engine::Texture::FromFile("/Users/denis/Projects/Awege/BlenderImporter/export_script/gizmo_normal2_LO.png"))
{
  
  ShaderParameters::UniformBuffer frameUniformBuffer;
  frameUniformBuffer.sizeInBytes = sizeof(AAPLFrameUniforms);
  frameUniformBuffer.parameterIndex = 1;
  
  ShaderParameters::UniformBuffer materialUniformBuffer;
  materialUniformBuffer.sizeInBytes = sizeof(AAPLMaterialUniforms);
  materialUniformBuffer.parameterIndex = 2;
  
  std::vector<ShaderParameters::UniformBuffer> uniformBuffers;
  uniformBuffers.push_back(frameUniformBuffer);
  uniformBuffers.push_back(materialUniformBuffer);
  
  
  std::vector<VertexAttribute> attributes;
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributePositionName, VertexAttribute::DataType_Float3, 0));
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeNormalName, VertexAttribute::DataType_Float3, 12));
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeTangentName, VertexAttribute::DataType_Float3, 24));
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributeTexCoordsName, VertexAttribute::DataType_Half2, 36));
  VertexAttributeFormat attributeFormat(attributes, 40);
  
  
  ShaderParameters shaderParameters(attributeFormat, uniformBuffers);
  shaderParameters.vertexBuffer.parameterIndex = 0;
  
  shader = new Shader("vertexLight", "fragmentLight", shaderParameters, Shader::DepthCompareFunction::CompareFunction_Less);
  
  materialBuffer.allocateBuffer(sizeof(AAPLMaterialUniforms));
  AAPLMaterialUniforms* material = (AAPLMaterialUniforms*) materialBuffer.getData();
  material->emissiveColor[1] = 2;
  material->emissiveColor[2] = 2;
  material->emissiveColor[3] = 2;
  material->emissiveColor[4] = 2;
  
  frameBuffer.allocateBuffers(BUFFER_SIZE, 500);
  
  Engine::Window::SharedWindow().onSizeUpdate([this](Engine::Vector2 newSize) {
    updateViewProjectionMatrix(newSize);
  });
  
  updateViewProjectionMatrix(Engine::Window::SharedWindow().getSize());
}

RenderSystem::~RenderSystem()
{
  delete shader;
}

void RenderSystem::updateViewProjectionMatrix(Engine::Vector2 size)
{
  float aspectRatio = fabsf(size.x() / size.y());
  projectionMatrix = Engine::Matrix4x4::PerspectiveLH(Engine::Angle::Degrees(65), aspectRatio, 0.1f, 100.0f);
  viewMatrix = Engine::Matrix4x4::Identity();
}

void RenderSystem::update()
{
  
  static float _rotation = 0.f;
  _rotation += 0.005f;
  
  RenderCommands commands;
  commands.setActiveShader(shader);
  commands.setActiveFragmentTexture(texture, 0);
  commands.setActiveFragmentTexture(normalTexture, 1);
//  Weirdo::updateFB();
  int i = 0;
  for (auto component : components) {
    auto frameData = (EngineFrameUniforms*) frameBuffer.getData(i, BUFFER_SIZE);
    frameData->model = Engine::Matrix4x4::Translation(Engine::Vector3(-0.9f+(float)i*0.85f, (float)i*0.1f, 3)) * Engine::Matrix4x4::Rotation(Engine::Quaternion::AxisAngle(Engine::Vector3(1, 1, 0), Engine::Angle::Radians(_rotation)));
    frameData->view = viewMatrix;  //this is the camera look at matrix ;)
    auto modelViewMatrix = frameData->view * frameData->model;
    frameData->projectionView = projectionMatrix * modelViewMatrix;
    frameData->normal = modelViewMatrix.transposed().inverted();
    
    commands.setActiveUniformBuffer(frameBuffer, 1, i * BUFFER_SIZE);
    commands.setActiveUniformBufferOnFragmentShader(frameBuffer, 1);
    
    
    commands.setActiveUniformBuffer(materialBuffer, 2);
    commands.setActiveVertexBuffer(component->vbo.get().vertexBuffer, 0);
    commands.drawIndexed(component->vbo.get().indexBuffer);
//    commands.draw();

    i++;
  }
  
  RenderCommandBuffer::SharedBuffer().addCommandsToWorkingBuffer(commands);
  
//  updateComponents();
}

void RenderSystem::onCreate()
{
  
}
