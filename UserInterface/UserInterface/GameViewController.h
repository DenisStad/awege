//
//  GameViewController.h
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright (c) 2016 Awege. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <MetalKit/MTKView.h>
#include "UserInterface.hpp"

@interface GameViewController : NSViewController<MTKViewDelegate>

+(GameViewController*)SharedInstance;

-(id<MTLDevice>)device;
-(id <MTLLibrary>)defaultLibrary;
-(NSUInteger)numberOfInflightBuffers;
-(id<MTLRenderCommandEncoder>)currentRenderEncoder;
-(uint8_t)currentBufferIndex;

@end