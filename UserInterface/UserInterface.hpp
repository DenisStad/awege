//
//  UserInterface.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef UserInterface_hpp
#define UserInterface_hpp

#include "View.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "MaxRectsPacker.hpp"
#include "VertexBufferObject.hpp"
#include "UniformBufferObject.hpp"
#include <vector>
#include <forward_list>
#include <list>

class UserInterface {
  
public:
  
  static UserInterface& SharedUserInterface();
  
  void draw();
  
  void addView(std::shared_ptr<View> view);
  
private:
  
  UserInterface();
  
  std::shared_ptr<View> rootView;
  
  typedef struct __attribute__((__aligned__(256))) {
    float x;
    float y;
    float w;
    float h;
    float texX;
    float texY;
    float texW;
    float texH;
  } UIElementAttributes;
  
  Shader* uiShader;
  VertexBufferObject boxBuffer;
  UniformBufferObject windowBuffer;
  
  
  struct ViewBatch {
    std::list<std::shared_ptr<View>> views;
    Engine::Texture* texture;
    UniformBufferObject viewBuffers;
    MaxRectsPacker packer;
    unsigned numAvailableUniformBuffers;
  };
  
  std::vector<ViewBatch> viewBatches;
  
  std::forward_list<std::shared_ptr<View>> viewsToAdd;
//
//  View* views[3];
//  UniformBufferObject viewBuffers[3];
//  Engine::Texture* texture;
//  MaxRectsPacker packer;
  
  void allocateBuffersForView(std::shared_ptr<View> view, Canvas & viewCanvas);
  void allocateNewBatch();
  bool tryToAddViewToBatch(ViewBatch &batch, std::shared_ptr<View> view, Canvas &canvas);
  UIElementAttributes* getBufferAttributesAtIndex(ViewBatch &batch, unsigned int bufferIndex);
  void updateFrameBufferAttributesForView(UIElementAttributes* attributes, std::shared_ptr<View> view);
  void updateTextureBufferAttributesForView(UIElementAttributes* attributes, PlainFrame & textureFrame, ViewBatch & batch);
  
  void addViewToBatches(std::shared_ptr<View> view);
  
  void onWindowSizeUpdate(awege::Size newSize);
  
  
  friend class View;
  void viewTreeWasAdded(std::shared_ptr<View> view);
  void viewTreeWillBeRemoved(std::shared_ptr<View> view);

};

#endif /* UserInterface_hpp */
