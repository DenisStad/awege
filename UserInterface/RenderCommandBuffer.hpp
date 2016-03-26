//
//  RenderCommandBuffer.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef RenderCommandBuffer_hpp
#define RenderCommandBuffer_hpp

#include <vector>

class Shader;
class UniformBufferObject;
class InflightUniformBufferObject;
class VertexBufferObject;
namespace Engine {
  class Texture;
}

class RenderCommands {
  
  friend class RenderCommandBuffer;
  
public:
  
  void setActiveShader(Shader *shader);
  void setActiveUniformBuffer(UniformBufferObject object, unsigned int parameterIndex, std::size_t bufferByteOffset = 0);
  void setActiveUniformBuffer(InflightUniformBufferObject object, unsigned int parameterIndex, std::size_t bufferByteOffset = 0);
  void setActiveUniformBufferOnFragmentShader(UniformBufferObject object, unsigned int parameterIndex);
  void setActiveUniformBufferOnFragmentShader(InflightUniformBufferObject object, unsigned int parameterIndex);
  
  void setActiveVertexBuffer(VertexBufferObject object, unsigned int parameterIndex);
  void setActiveFragmentTexture(Engine::Texture texture, unsigned int parameterIndex);
  
  void draw();
  void drawIndexed(VertexBufferObject object);
  
};


class RenderCommandBuffer {
  /*
   typedef std::vector<RenderCommands::Command> CommandsList;
   
   std::mutex workingCommandsMutex;
   std::mutex finalizedCommandsMutex;
   std::mutex nonTransientCommandsMutex;
   CommandsList workingTransientCommands;
   CommandsList finalizedTransientCommands;
   CommandsList nonTransientCommands;
   */
  
public:
  
  void addCommandsToWorkingBuffer(RenderCommands& commands);
  
  /*
   void finalizeCommands();
   //  void clearTransientCommands();
   
   CommandsList popNonTransientCommands();
   CommandsList getTransientCommands();
   */
  
  
  static RenderCommandBuffer& SharedBuffer();
};


#endif /* RenderCommandBuffer_hpp */
