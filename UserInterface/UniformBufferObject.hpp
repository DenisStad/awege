//
//  UniformBufferObject.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef UniformBufferObject_hpp
#define UniformBufferObject_hpp

#include <vector>

class UniformBufferObject {
  
  std::size_t singleBufferSize;
  void* buffer;
  
public:
  
  void allocateBuffer(std::size_t byteCount);
  void allocateBuffer(std::size_t byteCount, unsigned int bufferCount);
  void deallocateBuffer();
  void* getData();
  void* getData(unsigned int index, std::size_t byteCount);
  void* getRawBuffer();
  
};

class InflightUniformBufferObject {
  
  std::vector<UniformBufferObject> buffers;
  
public:
  
  void allocateBuffers(std::size_t byteCount);
  void allocateBuffers(std::size_t byteCount, unsigned int bufferCount);
  void deallocateBuffers();
  void* getData();
  void* getData(unsigned int index, std::size_t byteCount);
  UniformBufferObject getCurrentBuffer();
  
};

#endif /* UniformBufferObject_hpp */
