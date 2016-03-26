//
//  TypeConversion.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 19/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef TypeConversion_hpp
#define TypeConversion_hpp

template <class T, class U>
class TypeConversion
{
  typedef char Small;
  class Big { char dummy[2]; };
  static Small Test(U);
  static Big Test(...);
  static T MakeT();
public:
  enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
  enum { sameType = false };
};

template <class T>
class TypeConversion<T, T>
{
public:
  enum { exists = 1, sameType = 1 };
};


#define SUPERSUBCLASS(T, U) (TypeConversion<const U*, const T*>::exists && !TypeConversion<const T*, const void*>::sameType)
#define SUPERSUBCLASS_STRICT(T, U) (SUPERSUBCLASS(T, U) && !TypeConversion<const T, const U>::sameType)

#endif /* TypeConversion_hpp */
