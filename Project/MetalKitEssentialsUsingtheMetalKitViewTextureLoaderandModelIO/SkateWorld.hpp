//
//  SkateWorld.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 28/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef SkateWorld_hpp
#define SkateWorld_hpp

#include "World.hpp"

class SkateWorld : public Engine::World {
  
public:
  
  void wasCreated();
  void willBeDestroyed();
  
  void setupUI();
  
};

#endif /* SkateWorld_hpp */
