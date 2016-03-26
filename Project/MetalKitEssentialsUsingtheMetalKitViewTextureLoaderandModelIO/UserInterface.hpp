//
//  UserInterface.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include "ComponentSystem.hpp"
#include "UIElement.hpp"

#include "View.hpp"
#include "Label.hpp"
#include "Texture.hpp"

namespace Engine {
namespace UI {
    
class UserInterface : public ComponentSystem<UIElement> {
  
  friend class UIElement;
  
  std::weak_ptr<Entity> uiEntity;
  
protected:
  
  Vector2 textureSize;
  unsigned char* textureData;
  
  Texture* texture;
  
public:
//  UserInterface();
  
  void onCreate();
  void onUpdate();
  
  void addView(View *view);
};
  
}
}

#endif /* UserInterface_hpp */
