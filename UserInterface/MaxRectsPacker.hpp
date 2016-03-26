//
//  MaxRectsPacker.hpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#ifndef MaxRectsPacker_hpp
#define MaxRectsPacker_hpp

#include <list>
#include "Canvas.hpp"

class MaxRectsPacker {
  
public:
  
  enum FreeRectChoiceHeuristic
  {
    RectBestShortSideFit, ///< -BSSF: Positions the rectangle against the short side of a free rectangle into which it fits the best.
    RectBestLongSideFit, ///< -BLSF: Positions the rectangle against the long side of a free rectangle into which it fits the best.
    RectBestAreaFit, ///< -BAF: Positions the rectangle into the smallest free rect into which it fits.
    RectBottomLeftRule, ///< -BL: Does the Tetris placement.
    RectContactPointRule ///< -CP: Choosest the placement where the rectangle touches other rects as much as possible.
  };
  
  MaxRectsPacker(PlainSize size/*, FreeRectChoiceHeuristic */);
  
  PlainFrame placeNextFrame(PlainSize size);
  
  PlainSize getSize();
  std::list<PlainFrame> getUsedFrames();
  std::list<PlainFrame> getFreeFrames();

private:
  
  PlainSize size;
  
  std::list<PlainFrame> usedFrames;
  std::list<PlainFrame> freeFrames;
  
  
  std::list<PlainFrame>::iterator findPositionForNextFrame(PlainSize size);
  
  std::list<PlainFrame>::iterator placeNextFrameBestArea(PlainSize size);
  void splitFreeFramesForFrame(PlainFrame nextFrame);

  /*
  PlainFrame findPositionForNewNodeBottomLeft(PlainSize size) const;
  PlainFrame findPositionForNewNodeBestShortSideFit(PlainSize size) const;
  PlainFrame findPositionForNewNodeBestLongSideFit(PlainSize size) const;
  PlainFrame findPositionForNewNodeBestAreaFit(PlainSize size) const;
  PlainFrame findPositionForNewNodeContactPoint(PlainSize size) const;
  */
};

#endif /* MaxRectsPacker_hpp */
