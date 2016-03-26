//
//  View.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef View_hpp
#define View_hpp

#include <set>
#include "Frame.hpp"
#include "AutoSizeCanvas.hpp"

#include "Color.hpp"

class View : public std::enable_shared_from_this<View> {
  
public:
  
  View();
  
  virtual ~View();
  
  virtual void draw(Canvas* canvas);
  void setNeedsUpdate();
  
  void setBackgroundColor(Color color);
  
  bool isCullingEnabled();
  void setCullingEnabled(bool enabled);
  
  void addSubView(std::shared_ptr<View> view);
  void removeSubView(std::shared_ptr<View> view);
  void removeFromSuperView();
  
  void setFrame(awege::Frame frame);
  
  virtual void parentFrameDidUpdate(awege::Frame parentFrame);
  
private:
  
  awege::Frame frame;
  
  std::set<std::shared_ptr<View>> subViews;
  std::weak_ptr<View> parentView;
  
  Color backgroundColor;
  bool needsDrawUpdate;
  bool needsFrameUpdate;
  bool cullingEnabled;

  void setNeedsUpdate(bool newValue);
  std::shared_ptr<View> getRootView();
  
  friend class UserInterface;
};

#endif /* View_hpp */
