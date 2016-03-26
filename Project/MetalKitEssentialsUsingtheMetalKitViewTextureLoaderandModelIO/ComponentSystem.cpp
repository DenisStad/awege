//
//  ComponentSystem.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "ComponentSystem.hpp"

Engine::ComponentSystemBase::ComponentSystemBase()
{
  assignNextSystemId();
}

Engine::ComponentSystemBase::~ComponentSystemBase()
{
}

void Engine::ComponentSystemBase::assignNextSystemId()
{
  static int nextId = 1;
  systemId = nextId++;
}

void Engine::ComponentSystemBase::setSystemOnComponent(ComponentBase* component)
{
  component->setSystem(this);
}

void Engine::ComponentSystemBase::setWorld(World* world)
{
  this->world = world;
}

Engine::World* Engine::ComponentSystemBase::getWorld()
{
  return world;
}

int Engine::ComponentSystemBase::getSystemId()
{
  return systemId;
}