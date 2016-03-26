//
//  Matrix.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 08/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include <iostream>
#include "Matrix.h"

namespace Engine {
  template <typename TYPE, unsigned ROWS, unsigned COLUMNS>
  std::ostream& operator<<(std::ostream& os, const Matrix<TYPE, ROWS, COLUMNS>& obj)
  {
    os << std::string("[");
    for (int r = 0; r < ROWS; r++) {
      if (r > 0) {
        os << std::string(" ");
      }
      for (int c = 0; c < COLUMNS; c++) {
        os << obj.get(r, c);
        if (c < COLUMNS-1) {
          os << std::string("\t\t\t\t\t");
        }
      }
      if (r < ROWS-1) {
        os << std::endl;
      }
    }
    os << std::string("]") << std::endl;
    return os;
  }
  /*
  std::ostream& operator<<(std::ostream& os, const Matrix3x4& obj)
  {
    os << std::string("[");
    for (int r = 0; r < 3; r++) {
      if (r > 0) {
        os << std::string(" ");
      }
      for (int c = 0; c < 4; c++) {
        os << obj.get(r, c);
        if (c < 4-1) {
          os << std::string("\t\t\t\t\t");
        }
      }
      if (r < 3-1) {
        os << std::endl;
      }
    }
    os << std::string("]") << std::endl;
    return os;
  }
   */
  
  std::ostream& operator<<(std::ostream& os, const Matrix4x4& obj)
  {
    os << std::string("[");
    for (int r = 0; r < 4; r++) {
      if (r > 0) {
        os << std::string(" ");
      }
      for (int c = 0; c < 4; c++) {
        os << obj.get(r, c);
        if (c < 4-1) {
          os << std::string("\t\t\t\t\t");
        }
      }
      if (r < 4-1) {
        os << std::endl;
      }
    }
    os << std::string("]") << std::endl;
    return os;
  }
}