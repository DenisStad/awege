//
//  View.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 26/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef View_hpp
#define View_hpp

#include "Rectangle.h"
#include <memory>
#include "Drawable.hpp"

namespace Engine {
  
class World;
  
namespace UI {
  
class UIElement;
  
class UserInterface;

class View : public Drawable {
  
  friend class UserInterface;
  friend class UIElement;
  
  Rectangle frame;
  UIElement* uiElement;
  
  bool needsRenderUpdate;
  
protected:
  
  virtual void render();
  UIElement* getUIElement();
  void setNeedsRendering(bool needsRendering);
  
public:
  
  View();
  
  void setNeedsRendering();
  bool needsRendering();
  
  void setFrame(Rectangle frame);
  void setPosition(Vector2 position);
  void setSize(Vector2 size);
  
  Rectangle getFrame();
  Vector2 getPosition();
  Vector2 getSize();
  
  void addSubView(View *view);
  void removeFromParentView();
  
};
  
}
}

#endif /* View_hpp */
