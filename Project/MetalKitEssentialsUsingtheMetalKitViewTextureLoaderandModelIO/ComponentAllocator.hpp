//
//  ComponentAllocator.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 22/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef ComponentAllocator_hpp
#define ComponentAllocator_hpp

#include <vector>
#include "FixedAllocator.hpp"
#include "Log.hpp"

template <class T, unsigned ExpectedNumberOfObjects>
class SameSizeComponentAllocator : protected FastFixedSizeMemoryAllocator<> {
//  std::vector<T> components;
public:
  SameSizeComponentAllocator()
  {
    initialize(sizeof(T), ExpectedNumberOfObjects);
  }
  
  template <class ... Args>
  T* allocateComponent(Args&&... args)
  {
    DevLogTag("Memory", "Allocating", sizeof(T), "Bytes");
    return new (allocateFixedSizeMemory()) T(std::forward<Args>(args)...);
  }
  void deallocateComponent(T* p)
  {
    DevLogTag("Memory", "Deallocating", sizeof(T), "Bytes");
    deallocateFixedSizeMemory(p, nullptr);
  }
};

#endif /* ComponentAllocator_hpp */
