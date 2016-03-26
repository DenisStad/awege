//
//  UIElement.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 27/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "Component.hpp"
#include "Vector.h"
#include "View.hpp"

namespace Engine {
  namespace UI {
    
    class UserInterface;
    
    class UIElement : public Component<UserInterface> {
      
      friend class UserInterface;
      
      View *view;
      
    protected:
      
      void setView(View* view);
      
    public:
      
      UIElement(View* view);
      
      void onAttach();
      void onDetach();
      void update();
      
    };
    
  }
}

#endif /* UIElement_hpp */
