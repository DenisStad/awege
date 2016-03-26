//
//  FixedAllocator.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 19/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "FixedAllocator.hpp"
#include <assert.h>

#define USE_NEW_TO_ALLOCATE

bool MemoryBlock::initializeMemoryBlock(std::size_t partSize, unsigned char numberOfParts)
{
  assert(partSize > 0);
  assert(numberOfParts > 0);
  const std::size_t allocSize = partSize * numberOfParts;
  assert(allocSize / partSize == numberOfParts);
  
#ifdef USE_NEW_TO_ALLOCATE
  // If this new operator fails, it will throw, and the exception will get
  // caught one layer up.
  data = static_cast<unsigned char*>(::operator new (allocSize));
#else
  // malloc can't throw, so its only way to indicate an error is to return
  // a nullptr pointer, so we have to check for that.
  data = static_cast<unsigned char*>(::std::malloc(allocSize));
  if (data == nullptr) {
    return false;
  }
#endif
  
  resetParts(partSize, numberOfParts);
  return true;
}

void MemoryBlock::releaseMemoryBlock()
{
  assert(data != nullptr);
#ifdef USE_NEW_TO_ALLOCATE
  ::operator delete (data);
#else
  ::std::free(static_cast<void*>(data));
#endif
}

void MemoryBlock::resetParts(std::size_t partSize, unsigned char numberOfParts)
{
  assert(partSize > 0);
  assert(numberOfParts > 0);
  assert((partSize * numberOfParts) / partSize == numberOfParts);
  
  firstAvailablePartIndex = 0;
  numberOfPartsAvailable = numberOfParts;
  
  unsigned char i = 0;
  for (unsigned char* p = data; i != numberOfParts; p += partSize) {
    *p = ++i;
  }
}

void* MemoryBlock::allocatePart(std::size_t partSize)
{
  if (isFilled()) {
    return nullptr;
  }
  
  assert((firstAvailablePartIndex * partSize) / partSize == firstAvailablePartIndex);
  unsigned char *blockPointer = data + (firstAvailablePartIndex * partSize);
  firstAvailablePartIndex = *blockPointer;
  --numberOfPartsAvailable;
  
  return blockPointer;
}

void MemoryBlock::deallocatePart(void* partPointer, ::std::size_t partSize)
{
  assert(partPointer >= data);
  
  unsigned char* partToRelease = static_cast<unsigned char*>(partPointer);

  assert((partToRelease - data) % partSize == 0);
  unsigned char partIndex = static_cast<unsigned char>((partToRelease - data) / partSize);
  
#if defined(DEBUG) || defined(_DEBUG)
  // Check if block was already deleted.  Attempting to delete the same
  // block more than once causes Chunk's linked-list of stealth indexes to
  // become corrupt.  And causes count of blocksAvailable_ to be wrong.
  if (numberOfPartsAvailable > 0) {
    assert(firstAvailablePartIndex != partIndex);
  }
#endif
  
  *partToRelease = firstAvailablePartIndex;
  firstAvailablePartIndex = partIndex;
  
  assert(firstAvailablePartIndex == (partToRelease - data) / partSize);
  
  ++numberOfPartsAvailable;
}