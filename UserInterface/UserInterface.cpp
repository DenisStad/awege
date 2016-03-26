//
//  UserInterface.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "UserInterface.hpp"
#include "Shader.hpp"
#include "Label.hpp"
#include "MaxRectsPacker.hpp"
#include "RenderCommandBuffer.hpp"
#include "Window.hpp"
#include "CulledCanvas.hpp"

UserInterface& UserInterface::SharedUserInterface()
{
  static UserInterface userInterface;
  return userInterface;
}

UserInterface::UserInterface()
{
  std::vector<ShaderParameters::UniformBuffer> uniformBuffers;
  std::vector<VertexAttribute> attributes;
  attributes.push_back(VertexAttribute(VertexAttribute::VertexAttributePositionName, VertexAttribute::DataType_Float2, 0));
  VertexAttributeFormat attributeFormat(attributes, 8);
  ShaderParameters shaderParameters(attributeFormat, uniformBuffers);
  shaderParameters.vertexBuffer.parameterIndex = 0;
  uiShader = new Shader("vertexUI", "fragmentUI", shaderParameters, Shader::DepthCompareFunction::CompareFunction_Less);

  
  float boxData[] = {
    0, 1,
    1, 1,
    1, 0,
    
    0, 1,
    1, 0,
    0, 0
  };
  boxBuffer.allocateBuffer((char*) boxData, sizeof(float) * 12);
  
  rootView = std::shared_ptr<View>(new View());
  
  
  windowBuffer.allocateBuffer(sizeof(int) * 2);
  Window::SharedWindow().onSizeUpdate([this](awege::Size newSize) {
    onWindowSizeUpdate(newSize);
  });
  onWindowSizeUpdate(Window::SharedWindow().getSize());
  
  
  allocateNewBatch();
  
//  texture = new Engine::Texture({ 1024, 1024 });
//  
//  viewBuffers[0].allocateBuffer(sizeof(UIElementAttributes));
//  viewBuffers[1].allocateBuffer(sizeof(UIElementAttributes));
//  viewBuffers[2].allocateBuffer(sizeof(UIElementAttributes));
//  
//  views[0] = new View();
//  views[1] = new Label("Test");
//  views[2] = new View();
//  
//  views[0]->setBackgroundColor(Color::RGBA(1, 0, 0, 1));
//  views[1]->setBackgroundColor(Color::RGBA(0, 1, 0, 1));
//  views[2]->setBackgroundColor(Color::RGBA(0, 0, 1, 1));
}

void UserInterface::onWindowSizeUpdate(awege::Size newSize)
{
  int* windowUniform = (int*) windowBuffer.getData();
  windowUniform[0] = newSize.width;
  windowUniform[1] = newSize.height;
  
  rootView->setFrame({ { 0, 0 }, newSize });
}

void UserInterface::addView(std::shared_ptr<View> view)
{
  rootView->addSubView(view);
}

void UserInterface::draw()
{
  while (!viewsToAdd.empty()) {
    auto view = viewsToAdd.front();

    if (view->isCullingEnabled()) {
      CulledCanvas viewCanvas;
      view->draw(&viewCanvas);
      view->setNeedsUpdate(false);
      
      allocateBuffersForView(view, viewCanvas);
      view->needsFrameUpdate = false;
      
      
    } else {
      AutoSizeCanvas viewCanvas;
      view->draw(&viewCanvas);
      view->setNeedsUpdate(false);
      
      allocateBuffersForView(view, viewCanvas);
      view->needsFrameUpdate = false;
    }
    
    viewsToAdd.pop_front();
  }
  
  
  for (auto batch : viewBatches) {
    int i = 0;
    auto it = batch.views.begin();
    while (i < batch.views.size()) {
      auto view = *it;
      /*
      if (view->needsDrawUpdate) {
        
        PlainFrame textureFrame;
        if (view->isCullingEnabled()) {
          CulledCanvas viewCanvas;
          view->draw(&viewCanvas);
          view->setNeedsUpdate(false);
          
          textureFrame = batch.packer.placeNextFrame(viewCanvas.getSize());
          
          batch.texture->setDataInRegion(textureFrame, viewCanvas.getData());
        } else {
          AutoSizeCanvas viewCanvas;
          view->draw(&viewCanvas);
          view->setNeedsUpdate(false);
          
          textureFrame = batch.packer.placeNextFrame(viewCanvas.getSize());
          
          batch.texture->setDataInRegion(textureFrame, viewCanvas.getData());
        }
        
        UIElementAttributes* attributes = (UIElementAttributes*) batch.viewBuffers.getData(i, sizeof(UIElementAttributes));
        attributes->x = i * 20;
        attributes->y = i * 4;
        attributes->w = 10;
        attributes->h = 10;
        attributes->texX = (float) textureFrame.position.x / 1024.0f;
        attributes->texY = (float) textureFrame.position.y / 1024.0f;
        attributes->texW = (float) textureFrame.size.w / 1024.0f;
        attributes->texH = (float) textureFrame.size.h / 1024.0f;
      }
       */
      if (view->needsFrameUpdate) {
        auto attributes = getBufferAttributesAtIndex(batch, (unsigned int) i);
        updateFrameBufferAttributesForView(attributes, view);
        view->needsFrameUpdate = false;
      }
      
      ++i;
      ++it;
    }
  }
  
  
  RenderCommands commands;
  commands.setActiveShader(uiShader);
  commands.setActiveVertexBuffer(boxBuffer, 0);
  commands.setActiveUniformBuffer(windowBuffer, 2);
  
  for (auto batch : viewBatches) {
    commands.setActiveFragmentTexture(*batch.texture, 0);
    
    for (int i = 0; i < batch.views.size(); i++) {
      commands.setActiveUniformBuffer(batch.viewBuffers, 1, sizeof(UIElementAttributes) * i);
      commands.draw();
    }
  }
  
//  for (int i = 0; i < 3; i++) {
//    if (views[i]->needsDrawUpdate) {
//      AutoSizeCanvas viewCanvas;
//      views[i]->draw(&viewCanvas);
//      views[i]->setNeedsUpdate(false);
//      
//      auto textureFrame = packer.placeNextFrame(viewCanvas.getSize());
//      
//      texture->setDataInRegion(textureFrame, viewCanvas.getData());
//      
//      auto data = (UIElementAttributes*) viewBuffers[i].getData();
//      data->x = i * 20;
//      data->y = i * 4;
//      data->w = 10;
//      data->h = 10;
//      data->texX = (float) textureFrame.position.x / 1024.0f;
//      data->texY = (float) textureFrame.position.y / 1024.0f;
//      data->texW = (float) textureFrame.size.w / 1024.0f;
//      data->texH = (float) textureFrame.size.h / 1024.0f;
//      
////      fillVertexBufferForView(viewBuffers[i].getRawBuffer(), { {i * 10, i * 40}, { 10 * i, 10 * i} }, textureFrame);
//    }
//    
//    commands.setActiveUniformBuffer(viewBuffers[i], 1);
//    commands.draw();
//  }
}

void UserInterface::allocateBuffersForView(std::shared_ptr<View> view, Canvas & viewCanvas)
{
  if (viewCanvas.getSize().w > 0 && viewCanvas.getSize().h > 0) {
    bool foundBatch = false;
    
    for (ViewBatch & batch : viewBatches) {
      
      if (tryToAddViewToBatch(batch, view, viewCanvas)) {
        foundBatch = true;
        break;
      }
    }
    
    if (!foundBatch) {
      allocateNewBatch();
      tryToAddViewToBatch(viewBatches.back(), view, viewCanvas);
    }
  }
}

void UserInterface::allocateNewBatch()
{
  ViewBatch batch {
    std::list<std::shared_ptr<View>>(),
    new Engine::Texture({ 1024, 1024 }),
    UniformBufferObject(),
    MaxRectsPacker({ 1024, 1024 }),
    50
  };
  
  batch.viewBuffers.allocateBuffer(sizeof(UIElementAttributes) * 50);
  viewBatches.push_back(batch);
}

bool UserInterface::tryToAddViewToBatch(ViewBatch &batch, std::shared_ptr<View> view, Canvas &canvas)
{
  if (batch.views.size() >= batch.numAvailableUniformBuffers) {
    return false;
  }
  
  auto textureFrame = batch.packer.placeNextFrame(canvas.getSize());
  if (textureFrame.size.w > 0 && textureFrame.size.h > 0) {
    batch.texture->setDataInRegion(textureFrame, canvas.getData());
    
    auto attributes = getBufferAttributesAtIndex(batch, (unsigned int) batch.views.size());
    updateFrameBufferAttributesForView(attributes, view);
    updateTextureBufferAttributesForView(attributes, textureFrame, batch);
    
    batch.views.push_back(view);
    return true;
  }
  return false;
}

UserInterface::UIElementAttributes* UserInterface::getBufferAttributesAtIndex(ViewBatch &batch, unsigned int bufferIndex)
{
  return (UIElementAttributes*) batch.viewBuffers.getData(bufferIndex, sizeof(UIElementAttributes));
}

void UserInterface::updateFrameBufferAttributesForView(UIElementAttributes* attributes, std::shared_ptr<View> view)
{
  float scale = Window::SharedWindow().getScaleFactor();
  attributes->x = view->frame.position.x / scale;
  attributes->y = view->frame.position.y / scale;
  attributes->w = view->frame.size.width / scale;
  attributes->h = view->frame.size.height / scale;
}

void UserInterface::updateTextureBufferAttributesForView(UIElementAttributes* attributes, PlainFrame & textureFrame, ViewBatch & batch)
{
  attributes->texX = (float) textureFrame.position.x / (float) batch.texture->getSize().w;
  attributes->texY = (float) textureFrame.position.y / (float) batch.texture->getSize().h;
  attributes->texW = (float) textureFrame.size.w / (float) batch.texture->getSize().w;
  attributes->texH = (float) textureFrame.size.h / (float) batch.texture->getSize().h;
}

void UserInterface::viewTreeWasAdded(std::shared_ptr<View> view)
{
  if (view->getRootView() == rootView) {
    addViewToBatches(view);
  }
}

void UserInterface::addViewToBatches(std::shared_ptr<View> view)
{
  viewsToAdd.push_front(view);
  
  for (auto subView : view->subViews) {
    addViewToBatches(subView);
  }
}

void UserInterface::viewTreeWillBeRemoved(std::shared_ptr<View> view)
{
  if (view->getRootView() == rootView) {
    
  }
}