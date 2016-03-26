//
//  Label.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 26/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include "View.hpp"
#include <string>

namespace Engine {
namespace UI {
  
class Label : public View {
  
  typedef std::string String;
  
  String text;
  
public:
  
  Label(String text);
  
  String getText();
  void setText(String text);
  
  virtual void render();
  
};

}
}

#endif /* Label_hpp */
