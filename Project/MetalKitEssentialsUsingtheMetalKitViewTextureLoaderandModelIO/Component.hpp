//
//  Component.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <memory>

namespace Engine {
  class Entity;
  class ComponentSystemBase;
  
  class ComponentBase
  {
  protected:
    friend class Entity;
    friend class ComponentSystemBase;
    
    ComponentSystemBase *system;
    std::weak_ptr<Entity> entity;
    bool active;
    
    void setSystem(ComponentSystemBase* system);
    void setEntity(std::weak_ptr<Entity> entity);
    
  public:
    bool isActive();
    void setActive(bool active);
    
    ComponentSystemBase* getBaseSystem();
    std::weak_ptr<Entity> getEntity();
  };
  
  template <class System>
  class Component : public ComponentBase {
  public:
    typedef System SystemType;
    SystemType* getSystem()
    {
      return dynamic_cast<SystemType*>(getBaseSystem());
    }
  };
}

#endif /* Component_hpp */
