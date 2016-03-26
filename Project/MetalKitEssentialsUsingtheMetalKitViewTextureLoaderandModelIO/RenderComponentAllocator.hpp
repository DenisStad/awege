//
//  RenderComponentAllocator.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 09/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef RenderComponentAllocator_hpp
#define RenderComponentAllocator_hpp

#include "FixedAllocator.hpp"
#include "Renderer.hpp"
#include "Log.hpp"

class RenderMemoryBlock
{
private:
  template <class MEMORY_BLOCK> friend class FastFixedSizeMemoryAllocator;
  
  unsigned char* data;
  unsigned char firstAvailablePartIndex;
  unsigned char numberOfPartsAvailable;
//  InflightUniformBufferObject perModelBuffer;
  
  
  bool initializeMemoryBlock(std::size_t partSize, unsigned char numberOfParts);
  void releaseMemoryBlock();
  void resetParts(std::size_t partsSize, unsigned char numberOfParts);
  
  void* allocatePart(std::size_t partSize);
  void deallocatePart(void *p, std::size_t partSize);
  
  inline bool hasPart(void* pointer, std::size_t blockLength) const;
  inline bool isFilled() const;
  
  //    bool isCorrupt(unsigned char numBlocks, std::size_t blockSize, bool checkIndexes) const;
  //    bool isBlockAvailable(void* p, unsigned char numBlocks, std::size_t blockSize) const;
  
  inline bool isEmpty(unsigned char numberOfParts) const;
};


class RenderSystemComponentAllocator : protected FastFixedSizeMemoryAllocator<RenderMemoryBlock> {
public:
  RenderSystemComponentAllocator()
  {
    initialize(sizeof(Renderer), 255);
  }
  
  Renderer* allocateComponent()
  {
    DevLogTag("Memory", "Renderer allocating", sizeof(Renderer), "Bytes");
    return new (allocateFixedSizeMemory()) Renderer();
  }
  
  void deallocateComponent(Renderer* p)
  {
    DevLogTag("Memory", "Renderer deallocating", sizeof(Renderer), "Bytes");
    deallocateFixedSizeMemory(p, nullptr);
  }
};


#endif /* RenderComponentAllocator_hpp */
