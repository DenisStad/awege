//
//  ShaderParameters.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef ShaderParameters_hpp
#define ShaderParameters_hpp

#include "VertexAttribute.hpp"

struct ShaderParameters {
  
public:
  
  struct ShaderBuffer {
    unsigned int parameterIndex;
  };
  
  struct UniformBuffer : ShaderBuffer {
    unsigned int sizeInBytes;
  };
  
  struct VertexBuffer : ShaderBuffer {
    VertexAttributeFormat format;
    VertexBuffer(VertexAttributeFormat format);
  };
  
  VertexBuffer vertexBuffer;
  std::vector<UniformBuffer> uniformBuffers;
  
  ShaderParameters(VertexAttributeFormat format, std::vector<UniformBuffer> uniformBuffers);
};

#endif /* ShaderParameters_hpp */
