//
//  Shader.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Shader.hpp"
#import "GameViewController.h"

Shader::Shader(std::string vertexShaderName, std::string fragmentShaderName, ShaderParameters parameters, DepthCompareFunction defaultDepthCompareFunction)
{
  auto viewController = [GameViewController SharedInstance];
  auto defaultLibrary = [viewController defaultLibrary];
  // Load the fragment program into the library.
  
  NSString *fragmentName = [NSString stringWithCString:fragmentShaderName.c_str() encoding:[NSString defaultCStringEncoding]];
  NSString *vertexName = [NSString stringWithCString:vertexShaderName.c_str() encoding:[NSString defaultCStringEncoding]];
  
  id <MTLFunction> fragmentProgram = [defaultLibrary newFunctionWithName:fragmentName];
  
  // Load the vertex program into the library.
  id <MTLFunction> vertexProgram = [defaultLibrary newFunctionWithName:vertexName];
  
  //        Create a vertex descriptor for our Metal pipeline. Specifies the layout
  //        of vertices the pipeline should expect.
  MTLVertexDescriptor* mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];
  
  unsigned int index = 0;
  for (auto vertexAttribute : parameters.vertexBuffer.format.getAttributes()) {
    mtlVertexDescriptor.attributes[index].format = (MTLVertexFormat) vertexAttribute.getDataType();
    mtlVertexDescriptor.attributes[index].offset = vertexAttribute.getByteOffset();
    mtlVertexDescriptor.attributes[index].bufferIndex = parameters.vertexBuffer.parameterIndex;
    index++;
  }
  
  mtlVertexDescriptor.layouts[parameters.vertexBuffer.parameterIndex].stride = parameters.vertexBuffer.format.getByteStride();
  mtlVertexDescriptor.layouts[parameters.vertexBuffer.parameterIndex].stepRate = 1;
  mtlVertexDescriptor.layouts[parameters.vertexBuffer.parameterIndex].stepFunction = MTLVertexStepFunctionPerVertex;
  
  MTKView* view = (MTKView*) viewController.view;
  
  // Create a reusable pipeline state
  MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
  pipelineStateDescriptor.label = @"MyPipeline";
  pipelineStateDescriptor.sampleCount = view.sampleCount;
  pipelineStateDescriptor.vertexFunction = vertexProgram;
  pipelineStateDescriptor.fragmentFunction = fragmentProgram;
  pipelineStateDescriptor.vertexDescriptor = mtlVertexDescriptor;
  pipelineStateDescriptor.colorAttachments[0].pixelFormat = view.colorPixelFormat;
  
  pipelineStateDescriptor.colorAttachments[0].blendingEnabled = YES;
  pipelineStateDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
  pipelineStateDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
  pipelineStateDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne;
  pipelineStateDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
  pipelineStateDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
  pipelineStateDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
  
  pipelineStateDescriptor.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
  pipelineStateDescriptor.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;
  
  NSError *error;
  id <MTLRenderPipelineState> _pipelineState = [viewController.device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
  
  if (!_pipelineState) {
    NSLog(@"Failed to create pipeline state, error %@", error);
  }
  
  MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
  depthStateDesc.depthCompareFunction = (MTLCompareFunction) defaultDepthCompareFunction;// MTLCompareFunctionLess;
//  depthStateDesc.depthWriteEnabled = YES;
  id <MTLDepthStencilState> _depthState = [viewController.device newDepthStencilStateWithDescriptor:depthStateDesc];
  
  pipelineState = (void*) CFBridgingRetain(_pipelineState);
  depthState = (void*) CFBridgingRetain(_depthState);
  
  
  size_t completeBuffersSize = 0;
  for (auto uniformBufferParameter : parameters.uniformBuffers) {
    completeBuffersSize += uniformBufferParameter.sizeInBytes;
  }
}

void* Shader::getPipelineState()
{
  return pipelineState;
}

void* Shader::getDepthState()
{
  return depthState;
}
