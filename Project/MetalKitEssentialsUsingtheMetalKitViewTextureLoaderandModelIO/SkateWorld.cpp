//
//  SkateWorld.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 28/02/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "SkateWorld.hpp"
#include "Entity.hpp"

//#include "Transform.hpp"
#include "Renderer.hpp"
#include "RenderSystem.hpp"
#include "MeshComponent.hpp"

void SkateWorld::wasCreated()
{
  /*
   auto world = new Engine::World();
   {
   auto entityPtr = world->createEntity();
   if (auto entity = entityPtr.lock()) {
   entity->addComponent<Renderer>();
   }
   }
   delete world;
   */
  
  
  /*
   //test multi systems
   auto systemPtr1 = world.getOrCreateSystem<RenderSystem>();
   auto systemPtr2 = world.getOrCreateSystem<RenderSystem>();
   DevLog(systemPtr1.lock() == systemPtr2.lock(), "same");
   */
  
  /*
   //test adding and remoce entities
   auto entity = world.createEntity();
   world.destroyEntity(entity);
   world.destroyEntity(entity);
   
   auto entity2 = world.createEntity();
   auto entity3 = world.createEntity();
   world.destroyEntity(entity3);
   auto entity4 = world.createEntity();
   world.destroyEntity(entity2);
   world.destroyEntity(entity4);
   */
  
  /*
   //test adding components 1
   if (auto entity = world.createEntity().lock()) {
   auto renderer = entity->getComponent<Renderer>();
   DevLog("has renderer", renderer.lock());
   
   auto systemPtr = world.getOrCreateSystem<RenderSystem>();
   if (auto system = systemPtr.lock()) {
   auto component = std::shared_ptr<Renderer>(system->createComponent());
   entity->addComponent(component);
   }
   renderer = entity->getComponent<Renderer>();
   DevLog("has renderer", renderer.lock());
   }
   */
  
  /*
   //test adding components 2
   if (auto entity = world.createEntity().lock()) {
   auto renderer = entity->getComponent<Renderer>();
   DevLog("has renderer", renderer.lock());
   auto systemPtr = world.getOrCreateSystem<RenderSystem>();
   if (auto system = systemPtr.lock()) {
   renderer = entity->addComponent<Renderer>(system);
   }
   DevLog("has renderer", renderer.lock());
   }
   */
  
  //test adding components 3
  //  if (auto entity = world.createEntity().lock()) {
  //    auto renderer = entity->getComponent<Renderer>();
  //    DevLog("has renderer", renderer.lock());
  //    renderer = entity->addComponent<Renderer>();
  //    DevLog("has renderer", renderer.lock());
  //    entity->removeComponent<Renderer>();
  //    DevLog("has renderer", renderer.lock());
  //  }

  
  for (int i = 0; i < 10; i++) {
    if (auto entity = createEntity().lock()) {
      //    entity->addComponent<MeshComponent>(MeshIdentifier(MeshDataSourceType_File, "/Users/denis/Projects/BlenderImporter/export_script/out.test"));
      entity->addComponent<MeshComponent>(MeshIdentifier(MeshDataSourceType_File, "/Users/denis/Projects/Awege/BlenderImporter/export_script/scripts/out.test"));
      //    entity->addComponent<MeshComponent>(MeshIdentifier(MeshDataSourceType_CompiledAssets, "/Users/denis/Projects/BlenderImporter/export_script/out.test"));
      entity->addComponent<Renderer>();
    }
  }
  
//  setupUI();
  
  /*
   if (auto entity = world.createEntity().lock()) {
   world.destroyEntity(entity);
   DevLog("1");
   }
   DevLog("2");
   */
  
  //  auto t = std::unique_ptr<Transform>(new Transform());
  //  entity.addComponent(std::move(t));
}

void SkateWorld::willBeDestroyed()
{
  
}

#include "UserInterface.hpp"
#include "Label.hpp"

void SkateWorld::setupUI()
{
  auto uiPtr = getOrCreateSystem<Engine::UI::UserInterface>();
  if (auto ui = uiPtr.lock()) {
    auto view = new Engine::UI::View();
    ui->addView(view);
    
    auto label = new Engine::UI::Label("My label");
    view->addSubView(label);
  }
}
