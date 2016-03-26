//
//  Entity.cpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Entity.hpp"
#include "World.hpp"

awege::Entity::Entity(World& world, EntityID id)
:
id(id),
world(world)
{
}

awege::EntityID awege::Entity::getID() const
{
  return id;
}

bool awege::Entity::isValid() const
{
  return world.isEntityValid(*this);
}