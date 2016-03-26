//
//  VertexBufferObject.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 06/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "VertexBufferObject.hpp"
#import "AAPLMetalKitEssentialsViewController.h"
#include "Data.hpp"

VertexBufferObject VertexBufferObject::CreateWithData(Data data)
{
  VertexBufferObject buffer;
  buffer.allocateBuffer(data.getData(), data.getByteCount());
  return buffer;
}

//VertexBufferObject::VertexBufferObject(char* bytes, unsigned int byteCount)
//{
//  auto device = [[AAPLMetalKitEssentialsViewController SharedInstance] device];
//  auto object = [device newBufferWithBytes:bytes length:byteCount options:MTLResourceOptionCPUCacheModeDefault];
//  buffer = (void*) CFBridgingRetain(object);
//}

void VertexBufferObject::allocateBuffer(char* bytes, std::size_t byteCount)
{
  auto device = [[AAPLMetalKitEssentialsViewController SharedInstance] device];
  auto object = [device newBufferWithBytes:bytes length:byteCount options:MTLResourceOptionCPUCacheModeDefault];
  buffer = (void*) CFBridgingRetain(object);
}

void VertexBufferObject::deallocateBuffer()
{
  CFBridgingRelease(buffer);
}

void* VertexBufferObject::getRawBuffer()
{
  return buffer;
}