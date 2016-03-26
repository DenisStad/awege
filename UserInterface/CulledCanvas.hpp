//
//  CulledCanvas.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 21/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef CulledCanvas_hpp
#define CulledCanvas_hpp

#include "Canvas.hpp"

class CulledCanvas : public Canvas {
  
public:
  
  void clearRect(PlainFrame rect, Color color);
  
  void drawPixel(PlainPosition position, Color color);
//  void drawLine(PlainPosition p1, PlainPosition p2, float width, Color color);
  void drawRect(PlainFrame rect, Color color);
  
};


#endif /* CulledCanvas_hpp */
