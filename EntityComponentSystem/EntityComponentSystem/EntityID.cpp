//
//  EntityID.cpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "EntityID.hpp"

awege::EntityID::EntityID(IndexType entityIndex, IndexType idCounter)
:
entityIndex(entityIndex),
idCounter(idCounter)
{
}

awege::EntityID::IndexType awege::EntityID::getEntityIndex()
{
  return entityIndex;
}