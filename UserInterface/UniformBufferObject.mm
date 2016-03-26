//
//  UniformBufferObject.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "UniformBufferObject.hpp"
#import "GameViewController.h"

typedef id<MTLBuffer> BufferType;


void UniformBufferObject::allocateBuffer(std::size_t byteCount)
{
  auto device = [[GameViewController SharedInstance] device];
  buffer = (void*) CFBridgingRetain([device newBufferWithLength:byteCount options:0]);
}

void UniformBufferObject::allocateBuffer(std::size_t byteCount, unsigned int bufferCount)
{
  auto device = [[GameViewController SharedInstance] device];
  buffer = (void*) CFBridgingRetain([device newBufferWithLength:byteCount * bufferCount options:0]);
}

void UniformBufferObject::deallocateBuffer()
{
  CFBridgingRelease(buffer);
}

void* UniformBufferObject::getData()
{
  return ((__bridge BufferType)buffer).contents;
}

void* UniformBufferObject::getData(unsigned int index, std::size_t byteCount)
{
  void* start = ((__bridge BufferType)buffer).contents;
  return ((char*)start) + index * byteCount;
}

void* UniformBufferObject::getRawBuffer()
{
  return buffer;
}


void InflightUniformBufferObject::allocateBuffers(std::size_t byteCount)
{
  NSUInteger numberOfBuffers = [[GameViewController SharedInstance] numberOfInflightBuffers];
  for (uint8_t i = 0; i < numberOfBuffers; i++) {
    UniformBufferObject buffer;
    buffer.allocateBuffer(byteCount);
    buffers.push_back(buffer);
  }
}

void InflightUniformBufferObject::allocateBuffers(std::size_t byteCount, unsigned bufferCount)
{
  NSUInteger numberOfBuffers = [[GameViewController SharedInstance] numberOfInflightBuffers];
  for (uint8_t i = 0; i < numberOfBuffers; i++) {
    UniformBufferObject buffer;
    buffer.allocateBuffer(byteCount, bufferCount);
    buffers.push_back(buffer);
  }
}


void InflightUniformBufferObject::deallocateBuffers()
{
  for (auto buffer : buffers) {
    buffer.deallocateBuffer();
  }
  buffers.clear();
}

void* InflightUniformBufferObject::getData()
{
  auto currentBufferIndex = [[GameViewController SharedInstance] currentBufferIndex];
  return buffers[currentBufferIndex].getData();
}

void* InflightUniformBufferObject::getData(unsigned int index, std::size_t byteCount)
{
  auto currentBufferIndex = [[GameViewController SharedInstance] currentBufferIndex];
  return buffers[currentBufferIndex].getData(index, byteCount);
}

UniformBufferObject InflightUniformBufferObject::getCurrentBuffer()
{
  auto currentBufferIndex = [[GameViewController SharedInstance] currentBufferIndex];
  return buffers[currentBufferIndex];
}