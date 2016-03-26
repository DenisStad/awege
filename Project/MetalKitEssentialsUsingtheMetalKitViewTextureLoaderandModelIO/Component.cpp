//
//  Component.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "Component.hpp"

void Engine::ComponentBase::setSystem(ComponentSystemBase* system)
{
  this->system = system;
}

Engine::ComponentSystemBase* Engine::ComponentBase::getBaseSystem()
{
  return system;
}

void Engine::ComponentBase::setEntity(std::weak_ptr<Entity> entity)
{
  this->entity = entity;
}

std::weak_ptr<Engine::Entity> Engine::ComponentBase::getEntity()
{
  return entity;
}

bool Engine::ComponentBase::isActive()
{
  return active;
}

void Engine::ComponentBase::setActive(bool newActive)
{
  active = newActive;
}