//
//  VertexBufferObject.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 06/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp

#include <string>

class Data;

class VertexBufferObject {
  
  void* buffer;
  
public:
  
  static VertexBufferObject CreateWithData(Data data);
  
  void allocateBuffer(char* bytes, std::size_t byteCount);
  void deallocateBuffer();
  void* getRawBuffer();
  
};

#endif /* VertexBufferObject_hpp */
