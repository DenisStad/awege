//
//  MaxRectsPacker.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "MaxRectsPacker.hpp"

MaxRectsPacker::MaxRectsPacker(PlainSize size)
:
size(size)
{
  freeFrames.push_back(PlainFrame({0, 0}, size));
}

PlainFrame MaxRectsPacker::placeNextFrame(PlainSize size)
{
  std::list<PlainFrame>::iterator frameToPlaceNextFrameInto = findPositionForNextFrame(size);
  
  if (frameToPlaceNextFrameInto == freeFrames.end()) {
    return PlainFrame();
  }
  
  PlainFrame nextFrame { frameToPlaceNextFrameInto->position, size };
  
  splitFreeFramesForFrame(nextFrame);

//  for(size_t i = 0; i < freeRectangles.size(); ++i) {
//    if (SplitFreeNode(freeRectangles[i], newFrame)) {
//      freeRectangles.erase(freeRectangles.begin() + i);
//      --i;
//      --numRectanglesToProcess;
//    }
//  }
//  PruneFreeList();
  
//  usedRectangles.push_back(newFrame);
  
  return nextFrame;
}

std::list<PlainFrame>::iterator MaxRectsPacker::findPositionForNextFrame(PlainSize size)
{
//  switch(method) {
//    case RectBestShortSideFit:
//      newFrame = findPositionForNewNodeBestShortSideFit(size);
//      break;
//    case RectBottomLeftRule:
//      newFrame = findPositionForNewNodeBottomLeft(size);
//      break;
//    case RectContactPointRule:
//      newFrame = findPositionForNewNodeContactPoint(size);
//      break;
//    case RectBestLongSideFit:
//      newFrame = findPositionForNewNodeBestLongSideFit(size);
//      break;
//    case RectBestAreaFit:
      return placeNextFrameBestArea(size);
//      break;
//  }
}

void MaxRectsPacker::splitFreeFramesForFrame(PlainFrame nextFrame)
{
  auto stopFrame = --freeFrames.end();
  for (auto it = freeFrames.begin(); it != freeFrames.end(); ++it) {
    if (nextFrame.intersects(*it)) {
      
      PlainFrame freeFrame = *it;
      
      bool frameWasSplit = false;
      
      if (nextFrame.leftSide() > freeFrame.leftSide() && nextFrame.leftSide() < freeFrame.rightSide()) {
        PlainFrame splitFrame;
        splitFrame.position.x = freeFrame.leftSide();
        splitFrame.size.w = nextFrame.leftSide() - freeFrame.leftSide();
        splitFrame.position.y = freeFrame.topSide();
        splitFrame.size.h = freeFrame.size.h;
        freeFrames.push_back(splitFrame);
        frameWasSplit = true;
      }
      
      if (nextFrame.rightSide() < freeFrame.rightSide() && nextFrame.rightSide() > freeFrame.leftSide()) {
        PlainFrame splitFrame;
        splitFrame.position.x = nextFrame.rightSide();
        splitFrame.size.w = freeFrame.rightSide() - nextFrame.rightSide();
        splitFrame.position.y = freeFrame.topSide();
        splitFrame.size.h = freeFrame.size.h;
        freeFrames.push_back(splitFrame);
        frameWasSplit = true;
      }
      
      if (nextFrame.topSide() > freeFrame.topSide() && nextFrame.topSide() < freeFrame.bottomSide()) {
        PlainFrame splitFrame;
        splitFrame.position.x = freeFrame.leftSide();
        splitFrame.size.w = freeFrame.size.w;
        splitFrame.position.y = freeFrame.topSide();
        splitFrame.size.h = nextFrame.topSide() - freeFrame.topSide();
        freeFrames.push_back(splitFrame);
        frameWasSplit = true;
      }
      
      if (nextFrame.bottomSide() < freeFrame.bottomSide() && nextFrame.bottomSide() > freeFrame.topSide()) {
        PlainFrame splitFrame;
        splitFrame.position.x = freeFrame.leftSide();
        splitFrame.size.w = freeFrame.size.w;
        splitFrame.position.y = nextFrame.bottomSide();
        splitFrame.size.h = freeFrame.bottomSide() - nextFrame.bottomSide();
        freeFrames.push_back(splitFrame);
        frameWasSplit = true;
      }

      
      if (frameWasSplit) {
        auto oldIt = it;
        --it;
        freeFrames.erase(oldIt);
      }
      
      
      if (it == stopFrame) {
        break;
      }
    }
  }
  
  for (auto it1 = freeFrames.begin(); it1 != freeFrames.end(); ++it1) {
    for (auto it2 = freeFrames.begin(); it2 != freeFrames.end(); ++it2) {
      if (it1 == it2) {
        continue;
      }
      if (it2->liesCompletelyIn(*it1)) {
        auto del = it2;
        --it2;
        freeFrames.erase(del);
      }
    }
  }
  
  usedFrames.push_back(nextFrame);
  
}


//PlainFrame findPositionForNewNodeBottomLeft(PlainSize size) const;
//PlainFrame findPositionForNewNodeBestShortSideFit(PlainSize size) const;
//PlainFrame findPositionForNewNodeBestLongSideFit(PlainSize size) const;
std::list<PlainFrame>::iterator MaxRectsPacker::placeNextFrameBestArea(PlainSize size)
{
  
  std::list<PlainFrame>::iterator frameToPlaceNextFrameInto = freeFrames.end();
  
  if (freeFrames.size() < 1) {
    return frameToPlaceNextFrameInto;
  }
  
//  //best fit
//  int sizeArea = size.w * size.h;
//  int bestFitArea = 0;
//  
//  for (auto it = freeFrames.begin(); it != freeFrames.end(); ++it) {
//    int freeFrameArea = it->size.w * it->size.h;
//    if (sizeArea < freeFrameArea && size.w < it->size.w && size.h < it->size.h) {
//      if (frameToPlaceNextFrameInto == freeFrames.end() || freeFrameArea - sizeArea > bestFitArea) {
//        frameToPlaceNextFrameInto = it;
//        bestFitArea = freeFrameArea - sizeArea;
//      }
//    }
//  }
  
  //perfect or worst
  int sizeArea = size.w * size.h;
  int bestFitArea = 0;
  
  for (auto it = freeFrames.begin(); it != freeFrames.end(); ++it) {
    int freeFrameArea = it->size.w * it->size.h;
    if (sizeArea < freeFrameArea && size.w <= it->size.w && size.h <= it->size.h) {
      if (freeFrameArea - sizeArea == 0) {
        frameToPlaceNextFrameInto = it;
        break;
      }
      if (frameToPlaceNextFrameInto == freeFrames.end() || freeFrameArea - sizeArea < bestFitArea) {
        frameToPlaceNextFrameInto = it;
        bestFitArea = freeFrameArea - sizeArea;
      }
    }
  }
  
  return frameToPlaceNextFrameInto;
}

//PlainFrame findPositionForNewNodeContactPoint(PlainSize size) const;

PlainSize MaxRectsPacker::getSize()
{
  return size;
}

std::list<PlainFrame> MaxRectsPacker::getUsedFrames()
{
  return usedFrames;
}
std::list<PlainFrame> MaxRectsPacker::getFreeFrames()
{
  return freeFrames;
}