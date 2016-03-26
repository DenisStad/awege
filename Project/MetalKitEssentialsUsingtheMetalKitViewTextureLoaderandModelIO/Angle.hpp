//
//  Angle.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Angle_hpp
#define Angle_hpp

namespace Engine {

class Angle {
  float degreesValue;
    
public:
  static Angle Degrees(float degrees);
  static Angle Radians(float radians);

  float degrees() const;
  float radians() const;
};
  
}

#endif /* Angle_hpp */
