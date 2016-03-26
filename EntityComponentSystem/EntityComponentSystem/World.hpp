//
//  World.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <vector>
#include "Entity.hpp"
#include "EntityIDManager.hpp"

namespace awege {
  
  class ComponentBaseSystem;
  
  class World {
    
  public:
    
    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isEntityValid(Entity entity) const;
    
    template <class Component>
    ComponentBaseSystem* getSystem();
    
  private:
    
//    std::vector<Entity> entities;
    EntityIDManager entityIDManager;
  };
  
}

template <class Component>
awege::ComponentBaseSystem* awege::World::getSystem()
{
  
}

#endif /* World_hpp */
