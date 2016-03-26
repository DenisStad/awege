//
//  ComponentSystem.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef ComponentSystem_hpp
#define ComponentSystem_hpp

#include "ArrayComponentStorage.hpp"

namespace awege {
  
  class Entity;
  
  class ComponentBaseSystem {
    
  };
  
  template <class Component, class ComponentStorage = ArrayComponentStorage<Component>>
  class ComponentSystem : public ComponentBaseSystem, public ComponentStorage {
    
  public:
    
    typedef Component ComponentType;
    
  };
  
}

#endif /* ComponentSystem_hpp */
