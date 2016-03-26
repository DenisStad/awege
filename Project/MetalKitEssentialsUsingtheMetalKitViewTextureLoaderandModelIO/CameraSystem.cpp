//
//  CameraSystem.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "CameraSystem.hpp"
#include "CameraComponent.hpp"

Transform CameraSystem::noCameraTransform = Transform();

CameraSystem::CameraSystem()
:
mainCameraTransform(noCameraTransform),
mainCamera(nullptr)
{
  
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::onCreate()
{
}

void CameraSystem::update()
{
  
}

void CameraSystem::registerCamera(CameraComponent* component)
{
  if (mainCamera == nullptr) {
    mainCamera = component;
    if (auto entity = component->getEntity().lock()) {
      mainCameraTransform = entity->getTransform();
    }
  }
}

void CameraSystem::unregisterCamera(CameraComponent* component)
{
  if (mainCamera == component) {
    mainCameraTransform = noCameraTransform;
  }
}