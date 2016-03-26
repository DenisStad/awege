//
//  Color.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

class Color {
  
public:
  
  static Color RGBA(float r, float g, float b, float a);
//  static Color RGBA(unsigned r, float g, float b, float a);
  
  Color();
  
  unsigned char r();
  unsigned char g();
  unsigned char b();
  unsigned char a();
  
private:
  
  unsigned char m[4];
  
};

#endif /* Color_hpp */
