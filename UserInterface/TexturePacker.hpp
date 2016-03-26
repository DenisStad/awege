//
//  TexturePacker.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef TexturePacker_hpp
#define TexturePacker_hpp

#include "Canvas.hpp"

class TexturePacker {
  
private:
  
  struct Node {
    PlainFrame frame;
    Node *left;
    Node *right;
  };
  
public:
  
  TexturePacker(PlainSize size);
  
  PlainFrame addFrameWihtSize(PlainSize size);
  
  
private:
  
  Node rootNode;
  
};

#endif /* TexturePacker_hpp */
