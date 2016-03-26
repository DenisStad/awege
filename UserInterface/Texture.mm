//
//  Texture.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Texture.hpp"
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "GameViewController.h"

Engine::Texture Engine::Texture::FromFile(std::string filename)
{
  id<MTLDevice> device = [[GameViewController SharedInstance] device];
  
  NSURL *textureURL = [NSURL fileURLWithPath:[NSString stringWithCString:filename.c_str() encoding:[NSString defaultCStringEncoding]]];
  
  MTKTextureLoader *textureLoader = [[MTKTextureLoader alloc] initWithDevice:device];
  
  NSError *error;
  id <MTLTexture> texture = [textureLoader newTextureWithContentsOfURL:textureURL options:nil error:&error];
  
  NSLog(@"%@", texture);
  return Texture((void*) CFBridgingRetain(texture));
}

Engine::Texture::Texture(void* textureId)
{
  this->textureId = textureId;
  id <MTLTexture> texture = (__bridge id <MTLTexture>) textureId;
  size = PlainSize((int) [texture width], (int) [texture height]);
}

Engine::Texture::Texture(PlainSize size)
:
size(size)
{
  id<MTLDevice> device = [[GameViewController SharedInstance] device];
  
  MTLTextureDescriptor *texDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:size.w height:size.h mipmapped:NO];
  id <MTLTexture> texture = [device newTextureWithDescriptor:texDesc];
  
  textureId = (void*) CFBridgingRetain(texture);
}

Engine::Texture::~Texture()
{
  //  CFBridgingRelease(textureId);
}

PlainSize Engine::Texture::getSize()
{
  return size;
}

void Engine::Texture::setDataInRegion(PlainFrame region, unsigned char *data)
{
  id <MTLTexture> texture = (__bridge id<MTLTexture>) textureId;
  
  int pixelSize = 4 * 1;
  NSUInteger rowBytes = region.size.w * pixelSize;
  NSUInteger imageBytes = region.size.h * rowBytes;
  
  [texture replaceRegion:MTLRegionMake2D(region.position.x, region.position.y, region.size.w, region.size.h) mipmapLevel:0 slice:0 withBytes:data bytesPerRow:rowBytes bytesPerImage:imageBytes];
 
  
//  {
//    int width = size.w;
//    int height = size.h;
//    
//    void* tData = malloc(width*height*4);
//    [texture getBytes:tData bytesPerRow:width*4 fromRegion:MTLRegionMake2D(0, 0, size.w, size.h) mipmapLevel:0];
//    
//    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
//                                                              tData,
//                                                              width*height*4,
//                                                              NULL);
//    
//    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
////    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedLast;
//    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedFirst;
//    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
//    CGImageRef imageRef = CGImageCreate(width,
//                                        height,
//                                        8,
//                                        32,
//                                        4*width,colorSpaceRef,
//                                        bitmapInfo,
//                                        provider,NULL,NO,renderingIntent);
//    
//    CFStringRef type = UTTypeCreatePreferredIdentifierForTag(kUTTagClassMIMEType, (__bridge CFStringRef) @"image/png", kUTTypeImage);
//    CGImageDestinationRef destination =  CGImageDestinationCreateWithURL((__bridge CFURLRef) [NSURL fileURLWithPath:[NSString stringWithFormat:@"/Users/denis/out%px.png", textureId]], type, 1, nil);
//    CGImageDestinationAddImage(destination, imageRef, nil);
//    
//    if (!CGImageDestinationFinalize(destination)) {
//      NSLog(@"Failed to write image to");
//    }
//    
//    CFRelease(destination);
//    free(tData);
//  }

}

void* Engine::Texture::getRawTexture()
{
  return textureId;
}