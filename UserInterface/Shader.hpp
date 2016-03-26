//
//  Shader.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include "ShaderParameters.hpp"

class Shader {
  
public:
  
  enum DepthCompareFunction {
    CompareFunction_Never = 0,
    CompareFunction_Less = 1,
    CompareFunction_Equal = 2,
    CompareFunction_LessEqual = 3,
    CompareFunction_Greater = 4,
    CompareFunction_NotEqual = 5,
    CompareFunction_GreaterEqual = 6,
    CompareFunction_Always = 7,
  };
  
private:
  
  void* pipelineState;
  void* depthState;
  
public:
  Shader(std::string vertexShaderName, std::string fragmentShaderName, ShaderParameters parameters, DepthCompareFunction defaultDepthCompareFunction);
  
  void* getPipelineState();
  void* getDepthState();
  
};

#endif /* Shader_hpp */
