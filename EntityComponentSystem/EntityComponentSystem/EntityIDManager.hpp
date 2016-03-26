//
//  EntityIDManager.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef EntityIDManager_hpp
#define EntityIDManager_hpp

#include "EntityID.hpp"
#include <forward_list>
#include <vector>

namespace awege {
  
  class EntityIDManager {
    
  public:
    
    EntityIDManager();
    
    EntityID getFreeID();
    void returnID(EntityID id);
    bool isIDValid(EntityID id) const;
    
  private:
    
    EntityID::IndexType nextUnusedIndex;
    std::forward_list<EntityID::IndexType> freeIndices;
    std::vector<unsigned int> indexCounts;
    
    unsigned int increaseCountAtIndex(EntityID::IndexType index);
    unsigned int getCountAtIndex(EntityID::IndexType index) const;
    EntityID getEntityIDForIndex(EntityID::IndexType index);
  };
  
}

#endif /* EntityIDManager_hpp */
