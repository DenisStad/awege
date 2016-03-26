//
//  Texture.cpp
//  MetalKitEssentials
//
//  Created by Denis Stadniczuk on 01/03/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#include "Texture.hpp"

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import "AAPLMetalKitEssentialsViewController.h"

Engine::Texture Engine::Texture::FromFile(std::string filename)
{
  id<MTLDevice> device = [[AAPLMetalKitEssentialsViewController SharedInstance] device];
  
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
  size = Vector2i((int) [texture width], (int) [texture height]);
}

Engine::Texture::Texture(Vector2i size)
:
size(size)
{
  id<MTLDevice> device = [[AAPLMetalKitEssentialsViewController SharedInstance] device];
  
  MTLTextureDescriptor *texDesc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:size.x() height:size.y() mipmapped:NO];
  id <MTLTexture> texture = [device newTextureWithDescriptor:texDesc];
  
  textureId = (void*) CFBridgingRetain(texture);
}

Engine::Texture::~Texture()
{
//  CFBridgingRelease(textureId);
}

Engine::Vector2i Engine::Texture::getSize()
{
  return size;
}

void Engine::Texture::setDataInRegion(Rectangle region, unsigned char *data)
{
  {
    int width = size.x();
    int height = size.y();
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              data,
                                                              width*height*4,
                                                              NULL);
    
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(width,
                                        height,
                                        8,
                                        32,
                                        4*width,colorSpaceRef,
                                        bitmapInfo,
                                        provider,NULL,NO,renderingIntent);

    CFStringRef type = UTTypeCreatePreferredIdentifierForTag(kUTTagClassMIMEType, (__bridge CFStringRef) @"image/png", kUTTypeImage);
    CGImageDestinationRef destination =  CGImageDestinationCreateWithURL((__bridge CFURLRef) [NSURL fileURLWithPath:@"/Users/denis/out.png"], type, 1, nil);
    CGImageDestinationAddImage(destination, imageRef, nil);
    
    if (!CGImageDestinationFinalize(destination)) {
      NSLog(@"Failed to write image to");
    }
    
    CFRelease(destination);
  }
  
  id <MTLTexture> texture = (__bridge id<MTLTexture>) textureId;
 
  int pixelSize = 4 * 1;
  NSUInteger rowBytes = region.getSize().x() * pixelSize;
  NSUInteger imageBytes = region.getSize().y() * rowBytes;
  
  [texture replaceRegion:MTLRegionMake2D(region.getPosition().x(), region.getPosition().y(), region.getSize().x(), region.getSize().y()) mipmapLevel:0 slice:0 withBytes:data bytesPerRow:rowBytes bytesPerImage:imageBytes];
  
}

void* Engine::Texture::getRawTexture()
{
  return textureId;
}