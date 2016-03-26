//
//  MaterialComponent.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef MaterialComponent_hpp
#define MaterialComponent_hpp

#include "Component.hpp"
#include "ComponentSystem.hpp"

class MaterialComponent : public Engine::Component<Engine::ComponentSystem<MaterialComponent>> {
  
public:
  
  float redColor;
  
  MaterialComponent();
  void onAttach();
  void onDetach();
  void update();
};

#endif /* MaterialComponent_hpp */
