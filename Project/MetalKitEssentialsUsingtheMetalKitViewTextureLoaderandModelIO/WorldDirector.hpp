//
//  WorldDirector.hpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 28/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#ifndef WorldDirector_hpp
#define WorldDirector_hpp

#include <memory>
#include <vector>
#include <thread>

namespace Engine {
  
  class World;
  
  
  
  class OneThreadPerWorldThreadingType {
    
    class WorldRunner {
      
      World *world;
      std::thread thread;
      std::atomic<bool> shouldStopThread;
      
      void runLoop();
      
    public:
      
      WorldRunner(World* world);
      WorldRunner(WorldRunner const &runner);
      WorldRunner(WorldRunner&& runner);
      
      void startRunning();
      void stopRunning();
      
      World* getWorld();
      
      std::thread::id getThreadId();
      
    };
    
    std::vector<WorldRunner> worldRunners;
    
  public:
    
    World* getCurrentWorld();
    template <class T> void createWorld();

  };
  
  
  class OneWorldCalledFromMainThreadThreadingType {
    
    World* currentWorld;
    
  public:
    OneWorldCalledFromMainThreadThreadingType();
    
    World* getCurrentWorld();
    template <class T> void createWorld();
    void updateWorlds();
    
  };

  
  
  
  template <class ThreadingType>
  class WorldDirector : public ThreadingType {
  public:
    static WorldDirector<ThreadingType>& SharedDirector();
  };
  
  
  typedef WorldDirector<OneWorldCalledFromMainThreadThreadingType> DefaultWorldDirector;
}

#include "TypeConversion.hpp"
#include "World.hpp"

template <class ThreadingType>
Engine::WorldDirector<ThreadingType>& Engine::WorldDirector<ThreadingType>::SharedDirector()
{
  static WorldDirector director;
  return director;
}

template <class T> void Engine::OneThreadPerWorldThreadingType::createWorld()
{
  static_assert(SUPERSUBCLASS_STRICT(World, T), "world must derived from World");
  auto world = new T();
  WorldRunner runner(world);
  worldRunners.push_back(runner);
  worldRunners.back().startRunning();
}

template <class T> void Engine::OneWorldCalledFromMainThreadThreadingType::createWorld()
{
  if (currentWorld) {
    delete currentWorld;
  }
  currentWorld = new T();
  currentWorld->wasCreated();
}

#endif /* WorldDirector_hpp */
