//
//  World.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <vector>
#include <typeinfo>

namespace Engine {
  
  class Entity;
  class ComponentSystemBase;
  
  class World {
    
    template <class T> friend class WorldDirector;
    
  private:
    
    typedef std::shared_ptr<ComponentSystemBase> WorldOwnedSystemPointer;
    typedef std::weak_ptr<ComponentSystemBase> WeakSystemPointer;
    typedef std::shared_ptr<Entity> WorldOwnedEntityPointer;
    typedef std::weak_ptr<Entity> WeakEntityPointer;
    
    std::vector<WorldOwnedSystemPointer> systems;
    std::vector<WorldOwnedEntityPointer> entities;
    
    WorldOwnedSystemPointer findSystemWithTypeId(const std::type_info* id);
    template <class T> std::weak_ptr<T> createNewSystem();
    
  protected:
    
    World();
    
  public:
    virtual ~World();
    
    virtual void wasCreated() {}
    virtual void willBeDestroyed() {}
    
    template <class T> std::weak_ptr<T> getOrCreateSystem();
    WeakEntityPointer createEntity();
    void destroyEntity(WeakEntityPointer entity);
    
    void destroyAllEntities();
    void destroyAllSystems();
    
    void update();
    void updateComponentSystems();
    
  };
}

#include "TypeConversion.hpp"
#include "Log.hpp"

template <class T> std::weak_ptr<T> Engine::World::createNewSystem()
{
  auto system = std::shared_ptr<T>(new T());
  system->setWorld(this);
  systems.push_back(system);
  DevLogTag("EntityComponentSystem", "World", this, "added system", system, "with id", system->getSystemId());
  system->onCreate();
  return system;
}

template <class T> std::weak_ptr<T> Engine::World::getOrCreateSystem()
{
  static_assert(SUPERSUBCLASS_STRICT(ComponentSystemBase, T), "system must be derived from ComponentSystem");
  
  auto systemPtr = findSystemWithTypeId(&typeid(T));
  if (systemPtr) {
    return std::static_pointer_cast<T>(systemPtr);
  }
  return createNewSystem<T>();
}

#endif /* World_hpp */
