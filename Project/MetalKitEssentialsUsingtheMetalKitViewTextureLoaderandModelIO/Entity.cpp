//
//  Entity.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "Entity.hpp"
#include "Log.hpp"
#include "WorldDirector.hpp"

std::weak_ptr<Engine::Entity> Engine::Entity::Create()
{
  auto world = DefaultWorldDirector::SharedDirector().getCurrentWorld();
  if (world) {
    return world->createEntity();
  }
  return std::weak_ptr<Entity>();
}

Engine::Entity::Entity()
{
  DevLogTag("EntityComponentSystem", "Entity", this, "instantiated");
}

Engine::Entity::~Entity()
{
  DevLogTag("EntityComponentSystem", "Entity", this, "destroyed");
  void removeAllComponents();
}

void Engine::Entity::removeAllComponents()
{
  components.clear();
}

Transform& Engine::Entity::getTransform()
{
  return transform;
}

//void Engine::Entity::removeComponent(Component *component)
//{
//  std::vector<Component*>::iterator iterator = components.begin();
//  for (; iterator != components.end(); ++iterator) {
//    removeComponent(*iterator);
//  }
//}