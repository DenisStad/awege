//
//  World.cpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "World.hpp"

awege::Entity awege::World::createEntity()
{
  auto entityId = entityIDManager.getFreeID();
  Entity entity(*this, entityId);
//  entities.push_back(entity);
  return entity;
}

void awege::World::destroyEntity(Entity entity)
{
  entityIDManager.returnID(entity.getID());
}

bool awege::World::isEntityValid(Entity entity) const
{
  return entityIDManager.isIDValid(entity.getID());
}