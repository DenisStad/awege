//
//  EntityIDManager.cpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "EntityIDManager.hpp"

awege::EntityIDManager::EntityIDManager()
:
nextUnusedIndex(0)
{
}

awege::EntityID awege::EntityIDManager::getFreeID()
{
  if (!freeIndices.empty()) {
    auto index = freeIndices.front();
    freeIndices.pop_front();
    return getEntityIDForIndex(index);
  }

  return getEntityIDForIndex(nextUnusedIndex++);
}

awege::EntityID awege::EntityIDManager::getEntityIDForIndex(EntityID::IndexType index)
{
  auto count = increaseCountAtIndex(index);
  return EntityID(index, count);
}

unsigned int awege::EntityIDManager::increaseCountAtIndex(EntityID::IndexType index)
{
  if (indexCounts.size() <= index) {
    indexCounts.resize(index+1);
//    indexCounts.push_back(0);
  }
  return ++indexCounts[index];
}

unsigned int awege::EntityIDManager::getCountAtIndex(EntityID::IndexType index) const
{
  if (indexCounts.size() <= index) {
    return 0;
  }
  return indexCounts[index];
}


void awege::EntityIDManager::returnID(EntityID id)
{
  increaseCountAtIndex(id.getEntityIndex());
  freeIndices.push_front(id.getEntityIndex());
}


bool awege::EntityIDManager::isIDValid(EntityID id) const
{
  return getCountAtIndex(id.getEntityIndex()) == id.idCounter;
}