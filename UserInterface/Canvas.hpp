//
//  Canvas.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include "Color.hpp"

struct PlainPosition {
  int x;
  int y;
  
  PlainPosition();
  PlainPosition(int x, int y);
};

struct PlainSize {
  int w;
  int h;
  
  PlainSize();
  PlainSize(int w, int h);
};

struct PlainFrame {
  PlainPosition position;
  PlainSize size;
  
  PlainFrame();
  PlainFrame(PlainPosition position, PlainSize size);
  
  
  int leftSide();
  int rightSide();
  int topSide();
  int bottomSide();
  
  bool intersects(PlainFrame other);
  PlainFrame intersection(PlainFrame other);
  bool liesCompletelyIn(PlainFrame other);
  static PlainFrame FrameThatContainsBoth(PlainFrame one, PlainFrame other);
  
};

class Color;

class Canvas {
  
public:
  
  Canvas();
  ~Canvas();
  
  void setSize(PlainSize size);
  
  void copyDataFromCanvas(Canvas canvas, PlainFrame sourceFrame, PlainFrame targetFrame);
  
  virtual void clearRect(PlainFrame rect, Color color);
  
  virtual void drawPixel(PlainPosition position, Color color);
  virtual void drawPoint(PlainPosition position, float radius, Color color);
  virtual void drawLine(PlainPosition p1, PlainPosition p2, float width, Color color);
  virtual void drawRect(PlainFrame rect, Color color);
  
  unsigned char* getData();
  PlainSize getSize();
  virtual void clear(Color color = Color::RGBA(0, 0, 0, 0));
  
protected:
  
  unsigned char* data;
  PlainSize size;
  
  void freeData();
  
};

#endif /* Canvas_hpp */
