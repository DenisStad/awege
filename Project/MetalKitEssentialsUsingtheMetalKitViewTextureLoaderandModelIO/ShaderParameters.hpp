//
//  ShaderParameters.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 07/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef ShaderParameters_hpp
#define ShaderParameters_hpp

#include "VertexAttributes.hpp"
#include <vector>

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
