//
//  RenderCommandBuffer.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 02/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "RenderCommandBuffer.hpp"
#import "AAPLMetalKitEssentialsViewController.h"
#include "Log.hpp"
#include "Shader.hpp"
#include "VertexBufferObject.hpp"
#include "UniformBufferObject.hpp"
#include "Texture.hpp"

void RenderCommands::setActiveShader(Shader *shader)
{
  DevLogTag("Graphics", "Shader", shader, "activated");
  
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  
//  [renderEncoder setViewport:{0, 0, _view.drawableSize.width, _view.drawableSize.height, 0, 1}];
  id <MTLDepthStencilState> depthState = (__bridge id <MTLDepthStencilState>) shader->getDepthState();
  [renderEncoder setDepthStencilState:depthState];
  id <MTLRenderPipelineState> pipelineState = (__bridge id <MTLRenderPipelineState>) shader->getPipelineState();
  [renderEncoder setRenderPipelineState:pipelineState];
}

void RenderCommands::setActiveUniformBuffer(UniformBufferObject object, unsigned int parameterIndex)
{
  DevLogTag("Graphics", "Uniform buffer at index", parameterIndex, "set");
  
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder setVertexBuffer:(__bridge id <MTLBuffer>)object.getRawBuffer() offset:0 atIndex:parameterIndex];
}

void RenderCommands::setActiveUniformBufferOnFragmentShader(UniformBufferObject object, unsigned int parameterIndex)
{
  DevLogTag("Graphics", "Uniform buffer at index", parameterIndex, "set");
  
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder setFragmentBuffer:(__bridge id <MTLBuffer>)object.getRawBuffer() offset:0 atIndex:parameterIndex];
}

void RenderCommands::setActiveUniformBuffer(InflightUniformBufferObject object, unsigned int parameterIndex, std::size_t bufferByteOffset)
{
  DevLogTag("Graphics", "Uniform buffer at index", parameterIndex, "set");
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder setVertexBuffer:(__bridge id <MTLBuffer>)object.getCurrentBuffer().getRawBuffer() offset:bufferByteOffset atIndex:parameterIndex];
}

void RenderCommands::setActiveUniformBufferOnFragmentShader(InflightUniformBufferObject object, unsigned int parameterIndex)
{
  DevLogTag("Graphics", "Uniform buffer at index", parameterIndex, "set");
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder setFragmentBuffer:(__bridge id <MTLBuffer>)object.getCurrentBuffer().getRawBuffer() offset:0 atIndex:parameterIndex];
}

void RenderCommands::setActiveVertexBuffer(VertexBufferObject object, unsigned int parameterIndex)
{
  DevLogTag("Graphics", "Vertex buffer at index", parameterIndex, "set");
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder setVertexBuffer:(__bridge id <MTLBuffer>)object.getRawBuffer() offset:0 atIndex:parameterIndex];
  
  /*
  for (MTKMeshBuffer *vertexBuffer in _mesh.vertexBuffers) {
    // Set mesh's vertex buffers.
    if(vertexBuffer.buffer != nil) {
      [encoder setVertexBuffer:vertexBuffer.buffer offset:vertexBuffer.offset atIndex:bufferIndex];
    }
    
    bufferIndex++;
  }
  
  if(_diffuseTexture) {
    [encoder setFragmentTexture:_diffuseTexture atIndex:AAPLDiffuseTextureIndex];
  }
   */
  
//  [encoder setFragmentBuffer:_materialUniforms offset:0 atIndex:AAPLMaterialUniformBuffer];
//  [encoder setVertexBuffer:_materialUniforms offset:0 atIndex:AAPLMaterialUniformBuffer];
  
  // Draw the submesh.
//  [encoder drawIndexedPrimitives:_submesh.primitiveType indexCount:_submesh.indexCount indexType:_submesh.indexType indexBuffer:_submesh.indexBuffer.buffer indexBufferOffset:_submesh.indexBuffer.offset];
}

void RenderCommands::setActiveFragmentTexture(Engine::Texture texture, unsigned int parameterIndex)
{
  /*
  MTLSamplerDescriptor *desc = [[MTLSamplerDescriptor alloc] init];
  desc.minFilter = MTLSamplerMinMagFilterLinear;
  desc.magFilter = MTLSamplerMinMagFilterLinear;
  desc.sAddressMode = MTLSamplerAddressModeRepeat;
  desc.tAddressMode = MTLSamplerAddressModeRepeat;
  //  all properties below have default values
  desc.mipFilter        = MTLSamplerMipFilterNotMipmapped;
  desc.maxAnisotropy    = 1U;
  desc.normalizedCoordinates = YES;
  desc.lodMinClamp      = 0.0f;
  desc.lodMaxClamp      = FLT_MAX;
  // create MTLSamplerState
  id <MTLSamplerState> _sampler = [[AAPLMetalKitEssentialsViewController SharedInstance].device newSamplerStateWithDescriptor:desc];

   */
  
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  id<MTLTexture> tex = (__bridge id<MTLTexture>) texture.getRawTexture();
//  [renderEncoder setFragmentSamplerState:_sampler atIndex:parameterIndex];
  [renderEncoder setFragmentTexture:tex atIndex:parameterIndex];
}

void RenderCommands::draw()
{
  DevLogTag("Graphics", "Draw");
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:507];
//  [renderEncoder drawIndexedPrimitives:_submesh.primitiveType indexCount:_submesh.indexCount indexType:_submesh.indexType indexBuffer:_submesh.indexBuffer.buffer indexBufferOffset:_submesh.indexBuffer.offset];
}

void RenderCommands::drawIndexed(VertexBufferObject object)
{
  DevLogTag("Graphics", "Draw");
  auto renderEncoder = [[AAPLMetalKitEssentialsViewController SharedInstance] currentRenderEncoder];
  [renderEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:/*968*/732 * 3 indexType:MTLIndexTypeUInt32 indexBuffer:(__bridge id <MTLBuffer>)object.getRawBuffer() indexBufferOffset:0];
}

/*
void RenderCommands::addLoadTexture()
{
  nonTransientCommands.push_back(LOAD_TEXTURE);
}

void RenderCommands::addDeleteTexture()
{
  nonTransientCommands.push_back(DELETE_TEXTURE);
}

void RenderCommands::addDrawObject()
{
  transientCommands.push_back(DRAW_OBJECT);
}
 */


void RenderCommandBuffer::addCommandsToWorkingBuffer(RenderCommands& commands)
{
}

/*
void RenderCommandBuffer::addCommandsToWorkingBuffer(RenderCommands& commands)
{
  workingCommandsMutex.lock();
  workingTransientCommands.insert(workingTransientCommands.end(), commands.transientCommands.begin(), commands.transientCommands.end());
  workingCommandsMutex.unlock();
  
  if (commands.nonTransientCommands.size() == 0) {
    return;
  }
  
  
  nonTransientCommandsMutex.lock();
  
  for (auto command : commands.nonTransientCommands) {
    if (command.type == RenderCommands::DELETE_TEXTURE) {
      for (CommandsList::const_reverse_iterator it = nonTransientCommands.rbegin(); it != nonTransientCommands.rend(); ++it) {
        if ((*it).type == RenderCommands::LOAD_TEXTURE) {
//          it = nonTransientCommands.erase(it);
        }
      }
    }
    nonTransientCommands.push_back(command);
  }
  
  nonTransientCommandsMutex.unlock();
}
*/

//void RenderCommandBuffer::clearTransientCommands()
//{
//  workingCommandBufferMutex.lock();
//  workingTransientCommands.clear();
//  workingCommandBufferMutex.unlock();
//}

/*
void RenderCommandBuffer::finalizeCommands()
{
  workingCommandsMutex.lock();
  finalizedCommandsMutex.lock();
  
  finalizedTransientCommands = workingTransientCommands;
  workingTransientCommands.clear();
  
  finalizedCommandsMutex.unlock();
  workingCommandsMutex.unlock();
}

RenderCommandBuffer::CommandsList RenderCommandBuffer::popNonTransientCommands()
{
  nonTransientCommandsMutex.lock();
  auto copy = nonTransientCommands;
  nonTransientCommands.clear();
  nonTransientCommandsMutex.unlock();
  return copy;
}

RenderCommandBuffer::CommandsList RenderCommandBuffer::getTransientCommands()
{
  finalizedCommandsMutex.lock();
  auto copy = finalizedTransientCommands;
  finalizedCommandsMutex.unlock();
  return copy;
}
 */

RenderCommandBuffer& RenderCommandBuffer::SharedBuffer()
{
  static RenderCommandBuffer buffer;
  return buffer;
}