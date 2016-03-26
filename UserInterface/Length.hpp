//
//  Length.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef Length_hpp
#define Length_hpp

class Length {
  
public:
  
  Length();
  Length(const float &value);
  operator float() const;
  
private:
  
  float value;
  
};

/*
#include <vector>

class Window;

class Length {
  
public:
  
  static Length* Pixels(float numPixels);
  static Length* Points(float points, Window* window = nullptr);
  static Length* Fraction(float fraction, Length* parentLength);
  
  Length();
  ~Length();
  
  float fraction(Length* otherLength);
  Length* getParentLength();
  float fractionOfParent();
  
  float points();
  float pixels();
  
  bool isPixelsDeterminable();
  
private:
  
  enum LengthType {
    LengthTypePixels,
    LengthTypeFraction,
    LengthTypePoints
  };
  
  LengthType type;
  float value;
  
  Window* window;
  Length* parentLength;
  std::vector<Length*> childLengths;
  
  bool isAncestor(Length *possibleAncestor);
  bool isDescendant(Length *possibleDescendant);
  
};
*/

#endif /* Length_hpp */
