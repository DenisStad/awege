//
//  MeshComponent.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 25/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef MeshComponent_hpp
#define MeshComponent_hpp

#include "Component.hpp"
#include "ComponentSystem.hpp"
#include "VBOManager.hpp"

class MeshComponent : public Engine::Component<Engine::ComponentSystem<MeshComponent>> {
  MeshIdentifier identifierToLoad;
  
public:
  MeshComponent(const MeshIdentifier identifer);
  void onAttach();
  void onDetach();
  void update();
  
  MeshIdentifier getIdentifier();
};

#endif /* MeshComponent_hpp */
