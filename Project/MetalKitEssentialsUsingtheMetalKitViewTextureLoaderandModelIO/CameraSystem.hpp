//
//  CameraSystem.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef CameraSystem_hpp
#define CameraSystem_hpp

#include "ComponentSystem.hpp"
#include "Transform.h"

class CameraComponent;

class CameraSystem : public Engine::ComponentSystem<CameraComponent> {
  
  friend class CameraComponent;
  static Transform noCameraTransform;
  Transform& mainCameraTransform;
  CameraComponent *mainCamera;
  
protected:
  
  void registerCamera(CameraComponent* component);
  void unregisterCamera(CameraComponent* component);
  
public:
  
  CameraSystem();
  ~CameraSystem();
  void onCreate();
  void update();
};

#endif /* CameraSystem_hpp */
