//
//  FixedAllocator.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 19/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef FixedAllocator_hpp
#define FixedAllocator_hpp

#include <vector>

class MemoryBlock
{
private:
  template <class MEMORY_BLOCK> friend class FastFixedSizeMemoryAllocator;
  
  unsigned char* data;
  unsigned char firstAvailablePartIndex;
  unsigned char numberOfPartsAvailable;
  
  
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

template <class MEMORY_BLOCK = MemoryBlock>
class FastFixedSizeMemoryAllocator
{

private:
  
  typedef std::vector<MEMORY_BLOCK> MemoryBlocks;
  typedef typename MemoryBlocks::iterator BlockIterator;
  typedef typename MemoryBlocks::const_iterator BlockConstantIterator;
  static unsigned char MinObjectsPerMemoryBlock;
  static unsigned char MaxObjectsPerMemoryBlock;
  ::std::size_t fixedObjectSize;
  unsigned char numberOfObjectsPerMemoryBlock;
  MemoryBlocks blocks;
  MEMORY_BLOCK* allocBlock;
  MEMORY_BLOCK* deallocBlock;
  MEMORY_BLOCK* emptyBlock;
  
  
  void deallocateBlock(void* pointer);
  bool makeNewBlock();
  MEMORY_BLOCK* findNearBlock(void* pointer) const;

  FastFixedSizeMemoryAllocator(const FastFixedSizeMemoryAllocator&);
  FastFixedSizeMemoryAllocator& operator=(const FastFixedSizeMemoryAllocator&);
  
public:
  
  FastFixedSizeMemoryAllocator();
  ~FastFixedSizeMemoryAllocator();
  void initialize(std::size_t fixedObjectSize, std::size_t numberOfObjectsPerMemoryBlock);
  void* allocateFixedSizeMemory();
  bool deallocateFixedSizeMemory(void* pointer, MEMORY_BLOCK* hint);
//  inline std::size_t BlockSize() const { return blockSize; }
//  bool TrimEmptyChunk( void );
//  bool TrimChunkList( void );
  std::size_t numberOfEmptyBlocks() const;
  
//  bool IsCorrupt( void ) const;
  const MEMORY_BLOCK* hasPointer(void* objectPointer) const;
  inline MEMORY_BLOCK* hasPointer(void* objectPointer);
};



#include <assert.h>

inline bool MemoryBlock::hasPart(void* partPointer, std::size_t blockLength) const
{
  unsigned char* pointerToStart = static_cast<unsigned char *>(partPointer);
  return data <= pointerToStart && pointerToStart < data + blockLength;
}

inline bool MemoryBlock::isFilled() const
{
  return numberOfPartsAvailable == 0;
}

inline bool MemoryBlock::isEmpty(unsigned char numberOfParts) const
{
  return numberOfPartsAvailable == numberOfParts;
}



template <class MEMORY_BLOCK> unsigned char FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::MinObjectsPerMemoryBlock = 1;
template <class MEMORY_BLOCK> unsigned char FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::MaxObjectsPerMemoryBlock = 255;

template <class MEMORY_BLOCK>
FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::FastFixedSizeMemoryAllocator()
:
fixedObjectSize(0),
numberOfObjectsPerMemoryBlock(0),
blocks(0),
allocBlock(nullptr),
deallocBlock(nullptr),
emptyBlock(nullptr)
{
}

template <class MEMORY_BLOCK>
FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::~FastFixedSizeMemoryAllocator()
{
  for (BlockIterator i(blocks.begin()); i != blocks.end(); ++i) {
    i->releaseMemoryBlock();
  }
}

template <class MEMORY_BLOCK>
void FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::initialize(std::size_t fixedObjectSize, std::size_t numberOfObjectsPerMemoryBlock)
{
  assert(fixedObjectSize > 0);
  assert(numberOfObjectsPerMemoryBlock > 0);
  this->fixedObjectSize = fixedObjectSize;
  
  if (numberOfObjectsPerMemoryBlock > MaxObjectsPerMemoryBlock) {
    numberOfObjectsPerMemoryBlock = MaxObjectsPerMemoryBlock;
  } else if (numberOfObjectsPerMemoryBlock < MinObjectsPerMemoryBlock) {
    numberOfObjectsPerMemoryBlock = MinObjectsPerMemoryBlock;
  }
  
  this->numberOfObjectsPerMemoryBlock = static_cast<unsigned char>(numberOfObjectsPerMemoryBlock);
  assert(this->numberOfObjectsPerMemoryBlock == numberOfObjectsPerMemoryBlock);
}

template <class MEMORY_BLOCK>
void* FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::allocateFixedSizeMemory()
{
  assert(emptyBlock == nullptr || emptyBlock->isEmpty(numberOfObjectsPerMemoryBlock));
  assert(numberOfEmptyBlocks() < 2);
  
  if (allocBlock == nullptr || allocBlock->isFilled()) {
    if (emptyBlock != nullptr) {
      allocBlock = emptyBlock;
      emptyBlock = nullptr;
    } else {
      for (BlockIterator i(blocks.begin()); ;++i) {
        if (i == blocks.end()) {
          if (!makeNewBlock()) {
            return nullptr;
          }
          break;
        }
        if (!i->isFilled()) {
          allocBlock = &*i;
          break;
        }
      }
    }
  } else if (allocBlock == emptyBlock) {
    emptyBlock = nullptr;
  }
  
  assert(allocBlock != nullptr);
  assert(!allocBlock->isFilled());
  void* partPointer = allocBlock->allocatePart(fixedObjectSize);
  
  assert(emptyBlock == nullptr || emptyBlock->isEmpty(numberOfObjectsPerMemoryBlock));
  assert(numberOfEmptyBlocks() < 2);
  
  return partPointer;
}

template <class MEMORY_BLOCK>
bool FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::makeNewBlock()
{
  bool allocated = false;
  try {
    std::size_t size = blocks.size();
    if (blocks.capacity() == size) {
      if (size == 0) {
        size = 4;
      }
      blocks.reserve(size * 2);
    }
    MEMORY_BLOCK newBlock;
    allocated = newBlock.initializeMemoryBlock(fixedObjectSize, numberOfObjectsPerMemoryBlock);
    if (allocated) {
      blocks.push_back(newBlock);
    }
  } catch (...) {
    allocated = false;
  }
  if (!allocated) return false;
  
  allocBlock = &blocks.back();
  deallocBlock = &blocks.front();
  return true;
}

template <class MEMORY_BLOCK>
std::size_t FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::numberOfEmptyBlocks() const
{
  return emptyBlock == nullptr ? 0 : 1;
}

template <class MEMORY_BLOCK>
const MEMORY_BLOCK* FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::hasPointer(void* objectPointer) const
{
  const std::size_t memoryBlockSize = numberOfObjectsPerMemoryBlock * fixedObjectSize;
  for (BlockConstantIterator it(blocks.begin()); it != blocks.end(); ++it) {
    const MEMORY_BLOCK& block = *it;
    if (block.hasPart(objectPointer, memoryBlockSize)) {
      return &block;
    }
  }
  return nullptr;
}

template <class MEMORY_BLOCK>
inline MEMORY_BLOCK* FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::hasPointer(void* objectPointer)
{
  return const_cast<MEMORY_BLOCK*>(const_cast<const FastFixedSizeMemoryAllocator*>(this)->hasPointer(objectPointer));
}

template <class MEMORY_BLOCK>
bool FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::deallocateFixedSizeMemory(void* pointer, MEMORY_BLOCK* hint) {
  assert(!blocks.empty());
  assert(&blocks.front() <= deallocBlock);
  assert(&blocks.back() >= deallocBlock);
  assert(&blocks.front() <= allocBlock);
  assert(&blocks.back() >= allocBlock);
  assert(numberOfEmptyBlocks() < 2);
  
  MEMORY_BLOCK* foundBlock = nullptr;
  const std::size_t memoryBlockSize = numberOfObjectsPerMemoryBlock * fixedObjectSize;
  if (hint != nullptr && hint->hasPart(pointer, memoryBlockSize)) {
    foundBlock = hint;
  } else if (deallocBlock->hasPart(pointer, memoryBlockSize)) {
    foundBlock = deallocBlock;
  } else if (allocBlock->hasPart(pointer, memoryBlockSize)) {
    foundBlock = allocBlock;
  } else {
    foundBlock = findNearBlock(pointer);
  }
  
  if (foundBlock == nullptr) {
    return false;
  }
  
  assert(foundBlock->hasPart(pointer, memoryBlockSize));
  deallocBlock = foundBlock;
  deallocateBlock(pointer);
  assert(numberOfEmptyBlocks() < 2);
  
  return true;
}

template <class MEMORY_BLOCK>
MEMORY_BLOCK* FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::findNearBlock(void* pointer) const
{
  if (blocks.empty()) {
    return nullptr;
  }
  assert(deallocBlock);
  
  const std::size_t memoryBlockSize = numberOfObjectsPerMemoryBlock * fixedObjectSize;
  MEMORY_BLOCK* lo = deallocBlock;
  MEMORY_BLOCK* hi = deallocBlock + 1;
  const MEMORY_BLOCK* loBound = &blocks.front();
  const MEMORY_BLOCK* hiBound = &blocks.back() + 1;
  
  if (hi == hiBound) {
    hi = nullptr;
  }
  
  while (true) {
    if (lo) {
      if (lo->hasPart(pointer, memoryBlockSize)) {
        return lo;
      }
      if (lo == loBound) {
        lo = nullptr;
        if (hi == nullptr) {
          break;
        }
      } else {
        --lo;
      }
    }
    
    if (hi) {
      if (hi->hasPart(pointer, memoryBlockSize)) {
        return hi;
      }
      if (++hi == hiBound) {
        hi = nullptr;
        if (lo == nullptr) {
          break;
        }
      }
    }
  }
  
  return nullptr;
}

template <class MEMORY_BLOCK>
void FastFixedSizeMemoryAllocator<MEMORY_BLOCK>::deallocateBlock(void* pointer)
{
  assert(deallocBlock->hasPart(pointer, numberOfObjectsPerMemoryBlock * fixedObjectSize));
  assert(emptyBlock != deallocBlock);
  assert(!deallocBlock->isEmpty(numberOfObjectsPerMemoryBlock));
  assert(emptyBlock == nullptr || emptyBlock->isEmpty(numberOfObjectsPerMemoryBlock));
  
  deallocBlock->deallocatePart(pointer, fixedObjectSize);
  
  if (deallocBlock->isEmpty(numberOfObjectsPerMemoryBlock)) {
    assert(emptyBlock != deallocBlock);
    if (emptyBlock != nullptr) {
      MEMORY_BLOCK* lastBlock = &blocks.back();
      if (lastBlock == deallocBlock) {
        deallocBlock = emptyBlock;
      } else if (lastBlock != emptyBlock) {
        std::swap(*emptyBlock, *lastBlock);
      }
      assert(lastBlock->isEmpty(numberOfObjectsPerMemoryBlock));
      lastBlock->releaseMemoryBlock();
      blocks.pop_back();
      if (allocBlock == lastBlock || allocBlock->isFilled()) {
        allocBlock = deallocBlock;
      }
    }
    emptyBlock = deallocBlock;
  }
  
  assert(emptyBlock == nullptr || emptyBlock->isEmpty(numberOfObjectsPerMemoryBlock));
}



#endif /* FixedAllocator_hpp */
