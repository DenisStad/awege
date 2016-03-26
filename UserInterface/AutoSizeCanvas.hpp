//
//  AutoSizeCanvas.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef AutoSizeCanvas_hpp
#define AutoSizeCanvas_hpp

#include "Canvas.hpp"

class AutoSizeCanvas : public Canvas {
  
public:
  
  void clearRect(PlainFrame rect, Color color);
  
  void drawPixel(PlainPosition position, Color color);
  void drawPoint(PlainPosition position, float radius, Color color);
  void drawLine(PlainPosition p1, PlainPosition p2, float width, Color color);
  void drawRect(PlainFrame rect, Color color);
  
  PlainFrame currentlyAllocatedFrame();
  
private:
  
  PlainPosition positionOffset;
  
  void ensureFrame(PlainFrame rect);
  void resizeDrawFrame(PlainFrame newFrame);
  
  PlainFrame convert(PlainFrame frame);
  PlainPosition convert(PlainPosition position);
  
};

#endif /* AutoSizeCanvas_hpp */
