//
//  CameraComponent.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include "Component.hpp"

class CameraSystem;

class CameraComponent : public Engine::Component<CameraSystem> {
  
public:
  
  CameraComponent();
  void onAttach();
  void onDetach();
  void update();
};


#endif /* CameraComponent_hpp */
