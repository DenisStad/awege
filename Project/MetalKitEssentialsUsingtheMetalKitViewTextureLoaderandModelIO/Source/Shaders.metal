/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Main application delegate.
 */

#include <metal_stdlib>
#include <simd/simd.h>
#include <metal_texture>
#include <metal_matrix>
#include <metal_geometric>
#include <metal_math>
#include <metal_graphics>
#include "AAPLShaderTypes.h"

using namespace metal;

// Variables in constant address space.
constant float3 WorldLightDirection = float3(0.0, 1.0, 1.0);
constant half4 WorldAmbientLight = half4(0.1, 0.1, 0.1, 1.0);


// Per-vertex input structure
struct VertexInput {
    float3 position [[attribute(AAPLVertexAttributePosition)]];
    float3 normal   [[attribute(AAPLVertexAttributeNormal)]];
    float3 tangent   [[attribute(AAPLVertexAttributeTangent)]];
    half2  texcoord [[attribute(AAPLVertexAttributeTexcoord)]];
};

// Per-vertex output and per-fragment input
typedef struct {
    float4 position [[position]];
    float3 normal;
    float3 tangent;
    half2  texcoord;
    half4  color;
} ShaderInOut;

// Vertex shader function
vertex ShaderInOut vertexLight(VertexInput in [[stage_in]],
                               constant AAPLFrameUniforms& frameUniforms [[ buffer(AAPLFrameUniformBuffer) ]],
                               constant AAPLMaterialUniforms& materialUniforms [[ buffer(AAPLMaterialUniformBuffer) ]]) {
    ShaderInOut out;
    
    // Vertex projection and translation
    float4 in_position = float4(in.position, 1.0);
    out.position = frameUniforms.projectionView * in_position;
    float4 in_normal = float4(in.normal, 0.0);
  out.normal = in.normal;
//  float4 normal = frameUniforms.projectionView * in_normal;
//  out.normal = normal.xyz;
//  out.normal = in_normal.xyz;
    float4 in_tangent = float4(in.tangent, 0.0);
    out.tangent = (frameUniforms.projectionView * in_tangent).xyz;
  
//  float4 eye_normal = normalize(frameUniforms.normal * float4(in.normal, 0.0));
//  out.normal = eye_normal.xyz;
  
  /*
    // Per vertex lighting calculations
    float4 eye_normal = normalize(frameUniforms.normal * float4(in.normal, 0.0));
  
    float n_dot_l = dot(eye_normal.rgb, normalize(lightPosition));
    n_dot_l = fmax(0.0, n_dot_l);
    out.color = half4(materialUniforms.emissiveColor + n_dot_l);
  out.color = half4(materialUniforms.emissiveColor);// * n_dot_l;
  out.color = half4(1,1,1,1) * n_dot_l;
//  out.color = half4(1,1,1,1);
   */
  

    // Pass through texture coordinate
    out.texcoord = in.texcoord;
    
    return out;
}

// Fragment shader function
fragment half4 fragmentLight(ShaderInOut in [[stage_in]],
                             constant AAPLFrameUniforms& frameUniforms [[ buffer(AAPLFrameUniformBuffer) ]],
                             texture2d<half>  diffuseTexture [[ texture(AAPLDiffuseTextureIndex) ]],
                             texture2d<half>  normalTexture [[ texture(AAPLNormalTextureIndex) ]]) {
  constexpr sampler defaultSampler;
  
  float3 normal = in.normal;
  float3 tangent = in.tangent;
  tangent = normalize(tangent - dot(tangent, normal) * normal);
  float3 bitangent = cross(tangent, normal);
  float3 bumpNormal = float3(normalTexture.sample(defaultSampler, float2(in.texcoord)).xyz);
  bumpNormal = 2.0 * bumpNormal - float3(1.0, 1.0, 1.0);
  float3 newNormal;
  float3x3 TBN { tangent, bitangent, normal };
  newNormal = normalize(TBN * bumpNormal);
  
  float3 transformedNormal = normalize(frameUniforms.normal * float4(newNormal, 0.0)).xyz;
  

  
  half4 trueColor = diffuseTexture.sample(defaultSampler, float2(in.texcoord));
  
  
  //AMBIENT
  half4 ambientColor = WorldAmbientLight * trueColor;
  
  
  //DIFFUSE
  float dotNormalLightDir = dot(transformedNormal.rgb, normalize(-WorldLightDirection));
  dotNormalLightDir = fmax(0.0, dotNormalLightDir);
  half4 diffuseColor = dotNormalLightDir * trueColor;
  
  
  //SPECULAR
  float3 viewDirection = float3(0, 0, 1);
  float shininess = 100;
  
  float mirroredLightDot = max(0.0, dot(reflect(normalize(-WorldLightDirection), normalize(transformedNormal)), viewDirection));
  float specularIntensity = saturate(pow(mirroredLightDot, shininess) * 4);
  //add specularity at edge
//  float viewNormalDot = 1.0 - abs(dot(viewDirection, normalize(transformedNormal))*3);
//  specularIntensity += fmin(0.5 * viewNormalDot, 1.0);
  
  //specular
  specularIntensity = fmax(specularIntensity, 0);
  half4 specularColor = specularIntensity * /*half4(0.9, 0.9, 0.9, 1) */ trueColor;
  
  
  
  
  half4 color = ambientColor + diffuseColor + specularColor;
//  color = specularColor;
//  color = diffuseColor;
//  color = half4(half3(transformedNormal), 1);
//  color = specularColor;
//  color = half4(half3(bumpNormal.xyz), 1);
//  color.r = viewNormalDot/2+0.5;
//  color.r = dotNormalLightDir;
//  color.g = 0;
//  color.b = 0;
//  color = half4(half3(newNormal/2 + 0.5), 1);
    return color;
}