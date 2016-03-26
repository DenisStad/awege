//
//  EntityID.hpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef EntityID_hpp
#define EntityID_hpp

#include <cstdint>

namespace awege {
 
  class EntityID final {
    
    friend class EntityIDManager;
    
  public:
    
    typedef std::uint32_t IndexType;
    
  public:
    
    IndexType getEntityIndex();
    
  private:
    
    const IndexType entityIndex;
    const IndexType idCounter;
    
    
    EntityID(IndexType entityIndex, IndexType idCounter);
    
  };
  
}

#endif /* EntityID_hpp */
