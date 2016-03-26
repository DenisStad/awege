//
//  CameraComponent.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "CameraComponent.hpp"
#include "CameraSystem.hpp"

void CameraComponent::onAttach()
{
  getSystem()->registerCamera(this);
}

void CameraComponent::onDetach()
{
  getSystem()->unregisterCamera(this);
}

void CameraComponent::update()
{
}