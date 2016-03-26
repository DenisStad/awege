/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 MetalKit view controller that's setup as the MTKViewDelegate.
 */

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "AAPLShaderTypes.h"
#import "AAPLMetalKitEssentialsViewController.h"
#import "GoSkate.hpp"
#import "WorldDirector.hpp"
#import "Window.hpp"

// The  number of command buffers in flight.
const NSUInteger AAPLBuffersInflightBuffers = 3;

@implementation AAPLMetalKitEssentialsViewController {
  /*
   Using ivars instead of properties to avoid any performance penalities with
   the Objective-C runtime.
   */
  
  // View.
  MTKView *_view;
  
  // View Controller.
  dispatch_semaphore_t _inflightSemaphore;
  uint8_t _constantDataBufferIndex;
  
  // Renderer.
  id <MTLDevice> _device;
  id <MTLCommandQueue> _commandQueue;
  id <MTLLibrary> _defaultLibrary;
  
  id <MTLRenderCommandEncoder> _currentRenderEncoder;
  
  GoSkate goSkate;
}

-(id<MTLDevice>)device
{
  return _device;
}

-(id <MTLLibrary>)defaultLibrary
{
  return _defaultLibrary;
}

-(NSUInteger)numberOfInflightBuffers
{
  return AAPLBuffersInflightBuffers;
}

-(id<MTLRenderCommandEncoder>)currentRenderEncoder
{
  return _currentRenderEncoder;
}

-(uint8_t)currentBufferIndex
{
  return _constantDataBufferIndex;
}

- (void)viewDidLoad {
  
  [super viewDidLoad];
  
  sharedInstance = self;
  
  _constantDataBufferIndex = 0;
  _inflightSemaphore = dispatch_semaphore_create(AAPLBuffersInflightBuffers);
  
  [self setupMetal];
  [self setupView];
  [self reshape];
  
  goSkate.didLaunch();
}

-(void)dealloc
{
  for (int i = 0; i < AAPLBuffersInflightBuffers; i++) {
    dispatch_semaphore_signal(_inflightSemaphore);
  }
}

- (void)setupView {
  _view = (MTKView *)self.view;
  _view.delegate = self;
  _view.device = _device;
  
  // Setup the render target, choose values based on your app.
  _view.sampleCount = 4;
  _view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
}

- (void)setupMetal {
  // Set the view to use the default device.
  _device = MTLCreateSystemDefaultDevice();
  
  // Create a new command queue.
  _commandQueue = [_device newCommandQueue];
  
  // Load all the shader files with a metal file extension in the project.
  _defaultLibrary = [_device newDefaultLibrary];
}

- (void)render {
  dispatch_semaphore_wait(_inflightSemaphore, DISPATCH_TIME_FOREVER);
  
  // Perofm any app logic, including updating any Metal buffers.
  
  // Create a new command buffer for each renderpass to the current drawable.
  id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
  commandBuffer.label = @"Main Command Buffer";
  
  // Obtain a renderPassDescriptor generated from the view's drawable textures.
  MTLRenderPassDescriptor* renderPassDescriptor = _view.currentRenderPassDescriptor;
  if (renderPassDescriptor == nil) {
    dispatch_semaphore_signal(_inflightSemaphore);
    return;
  }
  
  // Create a render command encoder so we can render into something.
  id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
  
  _currentRenderEncoder = renderEncoder;
  
//  [_currentRenderEncoder setCullMode:MTLCullModeFront];
  
  
  renderEncoder.label = @"Final Pass Encoder";
  [renderEncoder setViewport:{0, 0, _view.drawableSize.width, _view.drawableSize.height, 0, 1}];
  
  
  [self update];
  
  
  
  // We're done encoding commands.
  [renderEncoder endEncoding];
  
  /*
   Call the view's completion handler which is required by the view since
   it will signal its semaphore and set up the next buffer.
   */
  __block dispatch_semaphore_t block_sema = _inflightSemaphore;
  [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
    dispatch_semaphore_signal(block_sema);
  }];
  
  /*
   The renderview assumes it can now increment the buffer index and that
   the previous index won't be touched until we cycle back around to the same index.
   */
  _constantDataBufferIndex = (_constantDataBufferIndex + 1) % AAPLBuffersInflightBuffers;
  
  // Schedule a present once the framebuffer is complete using the current drawable.
  [commandBuffer presentDrawable:_view.currentDrawable];
  
  // Finalize rendering here & push the command buffer to the GPU.
  [commandBuffer commit];
}

- (void)reshape {
  /*
   When reshape is called, update the view and projection matricies since
   this means the view orientation or size changed.
   */
  Engine::Vector2 newSize;
  newSize.x(self.view.bounds.size.width);
  newSize.y(self.view.bounds.size.height);
  Engine::Window::SharedWindow().updateSize(newSize);
  Engine::Window::SharedWindow().updateScaleFactor([NSScreen mainScreen].backingScaleFactor);
}

- (void)update {
  Engine::DefaultWorldDirector::SharedDirector().updateWorlds();
}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
  [self reshape];
}


// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view {
  @autoreleasepool {
    [self render];
  }
}

AAPLMetalKitEssentialsViewController * sharedInstance;

+ (AAPLMetalKitEssentialsViewController*)SharedInstance
{
  return sharedInstance;
}


@end
