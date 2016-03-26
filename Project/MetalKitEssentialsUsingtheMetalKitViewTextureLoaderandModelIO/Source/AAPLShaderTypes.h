/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Data types and values shared between the application Objective-C and Metal shading source.
 */

#ifndef AAPLShaderTypes_h
#define AAPLShaderTypes_h

#include <simd/simd.h>
//#ifdef __cplusplus
//#include "Matrix.h"
//#endif

using namespace simd;

/// Indices of vertex attribute in descriptor.
enum AAPLVertexAttributes {
    AAPLVertexAttributePosition = 0,
    AAPLVertexAttributeNormal   = 1,
    AAPLVertexAttributeTangent  = 2,
    AAPLVertexAttributeTexcoord = 3,
};

/// Indices for texture bind points.
enum AAPLTextureIndex {
    AAPLDiffuseTextureIndex = 0,
    AAPLNormalTextureIndex = 1
};

/// Indices for buffer bind points.
enum AAPLBufferIndex  {
    AAPLMeshVertexBuffer      = 0,
    AAPLFrameUniformBuffer    = 1,
    AAPLMaterialUniformBuffer = 2,
};

//#ifdef __cplusplus
///// Per frame uniforms.
//struct EngineFrameUniforms {
//  Engine::Matrix4x4 model;
//  Engine::Matrix4x4 view;
//  Engine::Matrix4x4 projection;
//  Engine::Matrix4x4 projectionView;
//  Engine::Matrix4x4 normal;
//};
//#endif
struct AAPLFrameUniforms {
    float4x4 model;
    float4x4 view;
    float4x4 projection;
    float4x4 projectionView;
    float4x4 normal;
};

/// Material uniforms.
struct AAPLMaterialUniforms {
    float4 emissiveColor;
    float4 diffuseColor;
    float4 specularColor;
    
    float specularIntensity;
    float pad1;
    float pad2;
    float pad3;
};

#endif /* AAPLShaderTypes_h */
