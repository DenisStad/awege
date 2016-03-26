//
//  Log.hpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#ifndef Log_hpp
#define Log_hpp

#include <iostream>
#include <vector>

extern const std::vector<std::string> disabledTags;

template <typename T>
void DevLog_log(T t)
{
  std::cout << t << std::endl;
}

template<typename T, typename... Args>
void DevLog_log(T t, Args... args)
{
  std::cout << t << " ";
  
  DevLog_log(args...) ;
}

template<typename... Args>
void DevLog_tag(std::string tag, Args... args)
{
  for (auto disabledTag : disabledTags) {
    if (tag == disabledTag) {
      return;
    }
  }
  std::cout << tag << " | ";
  DevLog_log(args...) ;
}

#define DevLog(x, ...) DevLog_log(x, ##__VA_ARGS__);
#define DevLogTag(x, y, ...) DevLog_tag(x, y, ##__VA_ARGS__);

#endif /* Log_hpp */
