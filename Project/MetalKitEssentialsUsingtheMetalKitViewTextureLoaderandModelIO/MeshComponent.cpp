//
//  MeshComponent.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 25/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "MeshComponent.hpp"
#include "Log.hpp"

MeshComponent::MeshComponent(const MeshIdentifier identifer)
:identifierToLoad(identifer)
{
}

void MeshComponent::onAttach()
{
}

void MeshComponent::onDetach()
{
}

MeshIdentifier MeshComponent::getIdentifier()
{
  return identifierToLoad;
}

void MeshComponent::update()
{
}