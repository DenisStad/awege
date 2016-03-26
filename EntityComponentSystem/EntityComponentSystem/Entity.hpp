//
//  Entity.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "EntityID.hpp"

namespace awege {
  
  class World;
  
  class Entity final {
    
    friend class World;
    
  public:
    
    EntityID getID() const;
    bool isValid() const;
    
  private:
    
    const EntityID id;
    World const & world;
    
    Entity(World& world, EntityID id);
    
    template <class Component, class ...Args>
    void addComponent(Args && ... args);
    
  };
  
}

//template <class Component, class ...Args>
//void awege::Entity::addComponent(Args && ... args)
//{
//  world.getSystem();
//}

#endif /* Entity_hpp */
