//
//  WorldDirector.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 28/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "WorldDirector.hpp"

Engine::OneThreadPerWorldThreadingType::WorldRunner::WorldRunner(WorldRunner const &runner)
{
  this->world = runner.world;
}

Engine::OneThreadPerWorldThreadingType::WorldRunner::WorldRunner(WorldRunner&& runner)
{
  this->thread = std::move(runner.thread);
  this->world = runner.world;
}

Engine::OneThreadPerWorldThreadingType::WorldRunner::WorldRunner(World *world)
{
  this->world = world;
}

Engine::World* Engine::OneThreadPerWorldThreadingType::WorldRunner::getWorld()
{
  return world;
}

void Engine::OneThreadPerWorldThreadingType::WorldRunner::startRunning()
{
  shouldStopThread = false;
  thread = std::thread(&Engine::OneThreadPerWorldThreadingType::WorldRunner::runLoop, this);
}

void Engine::OneThreadPerWorldThreadingType::WorldRunner::stopRunning()
{
  shouldStopThread = true;
}

void Engine::OneThreadPerWorldThreadingType::WorldRunner::runLoop()
{
  world->wasCreated();
  while (true) {
    if (shouldStopThread) {
      return;
    }
    world->update();
    sleep(0.033);
  }
}

Engine::World* Engine::OneThreadPerWorldThreadingType::getCurrentWorld()
{
  auto id = std::this_thread::get_id();
  for (std::vector<WorldRunner>::iterator it = worldRunners.begin(); it != worldRunners.end(); ++it) {
    if ((*it).getThreadId() == id) {
      return (*it).getWorld();
    }
  }
  return nullptr;
}

std::thread::id Engine::OneThreadPerWorldThreadingType::WorldRunner::getThreadId()
{
  return thread.get_id();
}



Engine::OneWorldCalledFromMainThreadThreadingType::OneWorldCalledFromMainThreadThreadingType()
{
  currentWorld = nullptr;
}

Engine::World* Engine::OneWorldCalledFromMainThreadThreadingType::getCurrentWorld()
{
  return currentWorld;
}

void Engine::OneWorldCalledFromMainThreadThreadingType::updateWorlds()
{
  if (currentWorld) {
    currentWorld->update();
  }
}