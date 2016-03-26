//
//  ArrayComponentStorage.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef ArrayComponentStorage_hpp
#define ArrayComponentStorage_hpp

#include <vector>
#include "EntityID.hpp"

namespace awege {
  
  class Entity;
  
  template <class Component>
  class ArrayComponentStorage {
    
  public:
    
    template <class ...Args>
    void addComponentToEntity(Entity entity, Args && ...componentArgs);
    Component* getComponentOfEntity(Entity entity);
    void removeComponentFromEntity(Entity entity);
    
  private:
    
    std::vector<int> componentEntityIDMap;
    std::vector<Component> components;
    
    void swapComponentsAtIndices(unsigned int index1, unsigned int index2);
    unsigned int getIndexForEntity(Entity entity);
  };
  
}

#include "Entity.hpp"
#include <algorithm>

template <class Component>
template <class ...Args>
void awege::ArrayComponentStorage<Component>::addComponentToEntity(Entity entity, Args && ...componentArgs)
{
  auto component = Component(std::forward<Args>(componentArgs)...);
  components.push_back(component);
  
  while (componentEntityIDMap.size() <= entity.getID().getEntityIndex()) {
    componentEntityIDMap.push_back(-1);
  }
  
  componentEntityIDMap[entity.getID().getEntityIndex()] = component.size() - 1;
}

template <class Component>
Component* awege::ArrayComponentStorage<Component>::getComponentOfEntity(Entity entity)
{
  auto componentIndex = getIndexForEntity(entity);
  if (componentIndex != -1) {
    return &components[componentIndex];
  }
  return nullptr;
}

template <class Component>
void awege::ArrayComponentStorage<Component>::removeComponentFromEntity(Entity entity)
{
  auto componentIndex = getIndexForEntity(entity);
  if (componentIndex != -1) {
    swapComponentsAtIndices(componentIndex, components.size() - 1);
    components.pop_back();
    componentEntityIDMap.pop_back();
  }
}

template <class Component>
unsigned int awege::ArrayComponentStorage<Component>::getIndexForEntity(Entity entity)
{
  if (entity.getID().getEntityIndex() < componentEntityIDMap.size()) {
    auto componentID = componentEntityIDMap[entity.getID().getEntityIndex()];
    return componentID;
  }
  return -1;
}

template <class Component>
void awege::ArrayComponentStorage<Component>::swapComponentsAtIndices(unsigned int index1, unsigned int index2)
{
  std::iter_swap(components.begin() + index1, components.begin() + index2);
  std::iter_swap(componentEntityIDMap.begin() + index1, componentEntityIDMap.begin() + index2);
}

#endif /* ArrayComponentStorage_hpp */
