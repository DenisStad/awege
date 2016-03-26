//
//  Log.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "Log.hpp"
#include <iostream>
#include <string>
#include <initializer_list>

const std::vector<std::string> disabledTags = {
  "EntityComponentSystem",
  "Graphics",
  "Memory"
//  "MeshLoader"
};
