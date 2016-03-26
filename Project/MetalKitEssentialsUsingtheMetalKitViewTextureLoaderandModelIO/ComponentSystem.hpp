//
//  ComponentSystem.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef ComponentSystem_hpp
#define ComponentSystem_hpp

#include <memory>
#include <vector>
#include "Log.hpp"
#include "ComponentAllocator.hpp"
#include "Component.hpp"

namespace Engine {
  
  class World;
  
  class ComponentSystemBase {
    
    friend class World;
    
    int systemId;
    World *world;
    
    void assignNextSystemId();
    
  protected:
    
    void setWorld(World* world);
    World* getWorld();
    void setSystemOnComponent(ComponentBase* component);
    
  public:
    
    ComponentSystemBase();
    virtual ~ComponentSystemBase();
    
    int getSystemId();
    
    virtual void update() = 0;
    virtual void onUpdate() {};
  };
  
  
  
  #warning Default allocator should be changed to shared component allocator
  template <class Component, class ComponentAllocator = SameSizeComponentAllocator<Component, 10>>
  class ComponentSystem : public ComponentSystemBase {
    friend class Entity;
    
  protected:
    
    ComponentAllocator componentAllocator;
    
    std::vector<Component*> components;
    typedef typename std::vector<Component*>::iterator ComponentIterator;
    
    template <typename... Args> Component* createComponent(Args&&... args);
    
  public:
    
    typedef Component ComponentType;
    
    ComponentSystem();
    ~ComponentSystem();
    
    void removeAllComponentsFromEntities();
    void updateComponents();
    void update();
    void onCreate();
    
  };
}

#include "Entity.hpp"

template <class Component, class ComponentAllocator>
Engine::ComponentSystem<Component, ComponentAllocator>::ComponentSystem()
{
  DevLogTag("EntityComponentSystem", "Component system", this, "instantiated");
}

template <class Component, class ComponentAllocator>
Engine::ComponentSystem<Component, ComponentAllocator>::~ComponentSystem()
{
  removeAllComponentsFromEntities();
  DevLogTag("EntityComponentSystem", "Component system", this, "destroyed");
}

template <class Component, class ComponentAllocator>
template <typename ... Args>
Component* Engine::ComponentSystem<Component, ComponentAllocator>::createComponent(Args&&... args) {
  auto component = componentAllocator.allocateComponent(std::forward<Args>(args)...);
  components.push_back(component);
  setSystemOnComponent(component);
  return component;
}

template <class Component, class ComponentAllocator>
void Engine::ComponentSystem<Component, ComponentAllocator>::removeAllComponentsFromEntities()
{
  ComponentIterator it = components.begin();
  for (; it != components.end(); ++it) {
    if (auto entity = (*it)->getEntity().lock()) {
      entity->template removeComponent<Component>();
    }
  }
}

template <class Component, class ComponentAllocator>
void Engine::ComponentSystem<Component, ComponentAllocator>::update()
{
  updateComponents();
  onUpdate();
}

template <class Component, class ComponentAllocator>
void Engine::ComponentSystem<Component, ComponentAllocator>::updateComponents()
{
  for (ComponentIterator it = components.begin(); it != components.end(); ++it) {
    (*it)->update();
  }
}

template <class Component, class ComponentAllocator>
void Engine::ComponentSystem<Component, ComponentAllocator>::onCreate()
{
  
}

#endif /* ComponentSystem_hpp */
