//
//  Window.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <functional>
#include <vector>
#include "Vector.h"

namespace Engine {

class Window {
  
  Vector2 size;
  float scaleFactor;
  
  std::vector<std::function<void(const Vector2 newSize)>> updaters;
  
public:
  
  static Window& SharedWindow();
  
  void updateScaleFactor(float newScaleFactor);
  void updateSize(Vector2 newSize);
  
  Vector2 getSize();
  float getScaleFactor();
  
  void onSizeUpdate(std::function<void(const Vector2 newSize)> updater);
//  void onSizeUpdate(void (*updater)(Vector2 newSize));
};
  
}

#endif /* Window_hpp */
