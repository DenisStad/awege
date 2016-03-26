//
//  VertexBufferObject.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "VertexBufferObject.hpp"
#import "GameViewController.h"
#include "Data.hpp"

VertexBufferObject VertexBufferObject::CreateWithData(Data data)
{
  VertexBufferObject buffer;
  buffer.allocateBuffer(data.getData(), data.getByteCount());
  return buffer;
}

void VertexBufferObject::allocateBuffer(char* bytes, std::size_t byteCount)
{
  auto device = [[GameViewController SharedInstance] device];
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

void* VertexBufferObject::getData()
{
  void* start = ((__bridge id<MTLBuffer>)buffer).contents;
  return start;
}