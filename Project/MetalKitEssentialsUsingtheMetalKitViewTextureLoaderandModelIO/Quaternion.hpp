//
//  Quaternion.h
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 05/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Quaternion_h
#define Quaternion_h


namespace Engine {
  
template <typename TYPE, unsigned SIZE> class Vector;
typedef Vector<float, 3> Vector3;
class Angle;

class Quaternion {

  float m[4];

public:
  
  static Quaternion AxisAngle(Vector3 axis, Engine::Angle angle);
  
  Quaternion operator*(Quaternion other);
  
  float x();
  float y();
  float z();
  float w();
  
};

}
#endif /* Quaternion_h */
