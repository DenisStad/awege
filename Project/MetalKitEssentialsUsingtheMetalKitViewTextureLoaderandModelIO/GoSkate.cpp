//
//  GoSkate.cpp
//  GameEngine
//
//  Created by Denis Stadniczuk on 18/02/16.
//  Copyright © 2016 Denis Stadniczuk. All rights reserved.
//

#include "GoSkate.hpp"
#include "Log.hpp"
#include "WorldDirector.hpp"
#include "SkateWorld.hpp"

void GoSkate::didLaunch()
{
  DevLog("GoSkate did launch");
  
  Engine::DefaultWorldDirector::SharedDirector().createWorld<SkateWorld>();
}
