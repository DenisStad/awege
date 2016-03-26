//
//  World.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "World.hpp"
#include "Entity.hpp"
#include <typeinfo>

using namespace Engine;

World::World()
{
  
}

World::~World()
{
}

World::WorldOwnedSystemPointer World::findSystemWithTypeId(const std::type_info* id)
{
  std::vector<WorldOwnedSystemPointer>::iterator it = systems.begin();
  for (; it != systems.end(); ++it) {
    ComponentSystemBase* system = it->get();
    
    if (*id == typeid(*system)) {
      return *it;
    }
  }
  return WorldOwnedSystemPointer();
}

World::WeakEntityPointer World::createEntity()
{
  DevLogTag("EntityComponentSystem", "World", this, "creates new entity");
  auto entity = WorldOwnedEntityPointer(new Entity());
  entity->world = this;
  entities.push_back(entity);
  return entity;
}

void World::destroyEntity(WeakEntityPointer entityPtr)
{
  DevLogTag("EntityComponentSystem", "World", this, "destroys entity");
  if (auto entity = entityPtr.lock()) {
    if (entity->world != this) {
      //Todo: add log message that gets sent to us
      return;
    }
    std::vector<WorldOwnedEntityPointer>::iterator position = std::find(entities.begin(), entities.end(), entity);
    if (position != entities.end()) {
      (*position)->world = nullptr;
      entities.erase(position);
    }
  }
}

void World::destroyAllEntities()
{
  entities.clear();
}

void World::destroyAllSystems()
{
  systems.clear();
}

void World::update()
{
  updateComponentSystems();
}

void World::updateComponentSystems()
{
  std::vector<WorldOwnedSystemPointer>::iterator it = systems.begin();
  for (; it != systems.end(); ++it) {
    ComponentSystemBase* system = it->get();
    system->update();
  }
}