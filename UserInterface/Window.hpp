//
//  Window.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Frame.hpp"
#include <functional>
#include <vector>

class Window {
  
public:
  
  static Window& SharedWindow();
  
  void updateScaleFactor(float newScaleFactor);
  void updateSize(awege::Size newSize);
  
  awege::Size getSize();
  float getScaleFactor();
  
  void onSizeUpdate(std::function<void(const awege::Size newSize)> updater);
  
  
private:
  
  float scaleFactor;
  awege::Size size;
  
  std::vector<std::function<void(const awege::Size newSize)>> updaters;
  
};

#endif /* Window_hpp */
