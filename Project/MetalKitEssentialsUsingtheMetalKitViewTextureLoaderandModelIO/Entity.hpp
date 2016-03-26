//
//  Entity.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "Log.hpp"
#include "TypeConversion.hpp"
#include <memory>
#include <vector>
#include "Node.hpp"
#include "Transform.h"

namespace Engine {
  
  class World;
  class ComponentBase;
  
  class Entity final : public Node<Entity> {
    friend class World;
    
  protected:
    World* world;
    Transform transform;
    std::vector<std::shared_ptr<ComponentBase>> components;
    
    
//    template <class T> std::weak_ptr<T> addComponent(std::shared_ptr<ComponentSystem<T>> system);
    template <class T> std::weak_ptr<T> addComponent(std::shared_ptr<T> component);
    
    Entity();
    
  public:
    
    ~Entity();
    
    static std::weak_ptr<Entity> Create();

    template <class T, typename... Args> std::weak_ptr<T> addComponent(Args&&... args);
    template <class T> std::weak_ptr<T> getComponent();
    template <class T> void removeComponent();
    void removeAllComponents();
    
    Transform& getTransform();
    
  };

}

#include "World.hpp"
#include "ComponentSystem.hpp"

template <class T, typename... Args> std::weak_ptr<T> Engine::Entity::addComponent(Args&&... args)
{
  if (auto component = getComponent<T>().lock()) {
    return component;
  }
  if (world != nullptr) {
    auto systemPtr = world->getOrCreateSystem<typename T::SystemType>();
    if (auto system = systemPtr.lock()) {
      auto component = std::shared_ptr<T>(system->createComponent(std::forward<Args>(args)...));
      return addComponent(component);
    }
  }
  return std::weak_ptr<T>();
}

template <class T> std::weak_ptr<T> Engine::Entity::addComponent(std::shared_ptr<T> component)
{
  static_assert(SUPERSUBCLASS_STRICT(Component<typename T::SystemType>, T), "component must derived from Component");
  DevLogTag("EntityComponentSystem", "Added Component to entity");
  components.push_back(component);
  
  auto thisPtr = std::static_pointer_cast<Entity>(shared_from_this());
  component->setEntity(thisPtr);
  component->onAttach();
  return component;
}

template <class T> std::weak_ptr<T> Engine::Entity::getComponent()
{
  static_assert(SUPERSUBCLASS_STRICT(Component<typename T::SystemType>, T), "component must be derived from Component");
  
  auto systemPtr = world->getOrCreateSystem<typename T::SystemType>();
  if (auto system = systemPtr.lock()) {
    auto systemIdToLookFor = system->getSystemId();
    
    std::vector<std::shared_ptr<ComponentBase>>::iterator it = components.begin();
    for (; it != components.end(); ++it) {
      auto component = dynamic_cast<ComponentBase*>(it->get());
      if (systemIdToLookFor == component->getBaseSystem()->getSystemId()) {
        auto ptr = std::static_pointer_cast<T>(*it);
        return ptr;
      }
    }
    
  }
  
  return std::weak_ptr<T>();
}

template <class T> void Engine::Entity::removeComponent()
{
  auto componentPtr = getComponent<T>();
  if (auto component = componentPtr.lock()) {
    std::vector<std::shared_ptr<ComponentBase>>::iterator position = std::find(components.begin(), components.end(), component);
    if (position != components.end()) {
      component->onDetach();
      components.erase(position);
    }
  }
}

#endif /* Entity_hpp */
