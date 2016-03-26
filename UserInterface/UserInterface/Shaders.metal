//
//  Shaders.metal
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright (c) 2016 Awege. All rights reserved.
//

#include <metal_stdlib>
#include <simd/simd.h>
#include "SharedStructures.h"

using namespace metal;

// Variables in constant address space
constant float3 light_position = float3(0.0, 1.0, -1.0);
constant float4 ambient_color  = float4(0.18, 0.24, 0.8, 1.0);
constant float4 diffuse_color  = float4(0.4, 0.4, 1.0, 1.0);

typedef struct
{
    float3 position [[attribute(0)]];
    float3 normal [[attribute(1)]];
} vertex_t;

typedef struct {
    float4 position [[position]];
    half4  color;
} ColorInOut;

// Vertex shader function
vertex ColorInOut lighting_vertex(vertex_t vertex_array [[stage_in]],
                                  constant uniforms_t& uniforms [[ buffer(1) ]])
{
    ColorInOut out;
    
    float4 in_position = float4(vertex_array.position, 1.0);
    out.position = uniforms.modelview_projection_matrix * in_position;
    
    float4 eye_normal = normalize(uniforms.normal_matrix * float4(vertex_array.normal, 0.0));
    float n_dot_l = dot(eye_normal.rgb, normalize(light_position));
    n_dot_l = fmax(0.0, n_dot_l);
    
    out.color = half4(ambient_color + diffuse_color * n_dot_l);
    return out;
}

// Fragment shader function
fragment half4 lighting_fragment(ColorInOut in [[stage_in]])
{
    return in.color;
}





struct UIWindowUniformAttributes {
  int2 size;
};

struct UIElementAttributes {
  float2 position;
  float2 size;
  float2 texPosition;
  float2 texSize;
};

typedef struct {
  float2 position [[attribute(0)]];
} ui_vertex_t;

typedef struct {
  float4 position [[position]];
  float2 texCoord;
} UIColorInOut;

vertex UIColorInOut vertexUI(ui_vertex_t vertex_array [[stage_in]], constant UIElementAttributes& elementUniform [[ buffer(1) ]], constant UIWindowUniformAttributes& windowUniform [[ buffer(2) ]])
{
  UIColorInOut out;
  
  float4 in_position = float4(vertex_array.position, 0.0, 1.0f);
  out.position = in_position;
  
  
  out.position.x = out.position.x * elementUniform.size.x + elementUniform.position.x;
  out.position.y = out.position.y * elementUniform.size.y + elementUniform.position.y;

  out.position.x /= (float) windowUniform.size.x/2;
  out.position.y /= (float) windowUniform.size.y/2;
  
  out.position.x = out.position.x * 2 - 1;
  out.position.y = (1-out.position.y) * 2 - 1;
  
  out.texCoord.x = in_position.x * elementUniform.texSize.x + elementUniform.texPosition.x;
  out.texCoord.y = in_position.y * elementUniform.texSize.y + elementUniform.texPosition.y;
  
  return out;
}

// Fragment shader function
fragment half4 fragmentUI(UIColorInOut in [[stage_in]], texture2d<half> texture [[ texture(0) ]])
{
  constexpr sampler defaultSampler;
  return texture.sample(defaultSampler, float2(in.texCoord));
//  half4 color = texture.sample(defaultSampler, float2(in.texCoord));
//  if (color.a < 0.99) {
//    discard_fragment();
//  }
//  return color;
}