//
//  ShaderParameters.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "ShaderParameters.hpp"

ShaderParameters::VertexBuffer::VertexBuffer(VertexAttributeFormat format)
:
format(format)
{
  
}

ShaderParameters::ShaderParameters(VertexAttributeFormat format, std::vector<UniformBuffer> uniformBuffers)
:
vertexBuffer(VertexBuffer(format)),
uniformBuffers(uniformBuffers)
{
}