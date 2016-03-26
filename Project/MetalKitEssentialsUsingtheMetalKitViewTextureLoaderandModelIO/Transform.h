//
//  Transform.h
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#include "Vector.h"
#include "Quaternion.hpp"
#include "Matrix.h"

class Transform
{
  
  Engine::Vector3 position;
  Engine::Quaternion rotation;
  Engine::Vector3 scale;
  
public:
  Transform add(Transform const & other)
  {
    Transform newTransform;
    newTransform.position = position + other.position;
    newTransform.rotation = rotation * other.rotation;
    newTransform.scale = scale * other.scale;
    return newTransform;
  }
  
  Engine::Matrix3x4 getMatrix();
};

#endif /* Transform_h */
