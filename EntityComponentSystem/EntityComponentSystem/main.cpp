//
//  main.cpp
//  EntityComponentSystem
//
//  Created by Denis Stadniczuk on 17/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

/*
#include <iostream>

int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "Hello, World!\n";
    return 0;
}
*/

#include "World.hpp"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


TEST_CASE("World creates entity with different IDs", "[world]") {
  awege::World world;
  
  auto entity1 = world.createEntity();
  auto entity2 = world.createEntity();
  
  REQUIRE(entity1.getID().getEntityIndex() == 0);
  REQUIRE(entity2.getID().getEntityIndex() == 1);
  REQUIRE(entity1.isValid() == true);
  REQUIRE(entity2.isValid() == true);
}

TEST_CASE("World destroys entities", "[world]") {
  awege::World world;
  
  auto entity1 = world.createEntity();
  auto entity2 = world.createEntity();
  
  REQUIRE(entity1.getID().getEntityIndex() == 0);
  REQUIRE(entity2.getID().getEntityIndex() == 1);
  REQUIRE(entity1.isValid() == true);
  REQUIRE(entity2.isValid() == true);
  
  world.destroyEntity(entity1);
  
  REQUIRE(entity1.isValid() == false);
}

TEST_CASE("World recycles entity ids", "[world]") {
  awege::World world;
  
  auto entity1 = world.createEntity();
  auto entity2 = world.createEntity();
  
  REQUIRE(entity1.getID().getEntityIndex() == 0);
  REQUIRE(entity2.getID().getEntityIndex() == 1);
  REQUIRE(entity1.isValid() == true);
  REQUIRE(entity2.isValid() == true);
  
  world.destroyEntity(entity1);
  
  REQUIRE(entity1.isValid() == false);
  
  auto entity3 = world.createEntity();
  REQUIRE(entity3.getID().getEntityIndex() == 0);
  REQUIRE(entity1.isValid() == false);
  REQUIRE(entity3.isValid() == true);
}

#include "ComponentSystem.hpp"

class TestComponent {
  float x;
  float y;
  
  TestComponent(float x, float y)
  :
  x(x),
  y(y)
  {
  }
  
};

class TestComponentSystem : public awege::ComponentSystem<TestComponent> {
  
public:
  
};

TEST_CASE("Add system to world", "[component system]") {
  awege::World world;
  
  world.addSystem();
}

/*
TEST_CASE("Add component to entity", "[component system]") {
  awege::World world;
  
  auto entity1 = world.createEntity();
  entity1.addComponent<TestComponent>();
}
*/