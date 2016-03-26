//
//  texture_pack_test.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 19/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "texture_pack_test.hpp"
#include "MaxRectsPacker.hpp"
#include "Color.hpp"

#include "catch.hpp"



void drawPack(MaxRectsPacker packer)
{
  Canvas canvas;
  canvas.setSize(packer.getSize());
  canvas.clearRect({{0, 0,}, packer.getSize()}, Color::RGBA(1, 1, 1, 1));
  
  auto used = packer.getUsedFrames();
  for (auto it = used.begin(); it != used.end(); ++it) {
    auto frame = *it;
    
    unsigned char g = 50 + (rand() % 205);
    unsigned char b = 50 + (rand() % 205);
    canvas.drawRect(frame, Color::RGBA(0, g/255.0f, b/255.0f, 1.0f));
  }

  auto free = packer.getFreeFrames();
  for (auto it = free.begin(); it != free.end(); ++it) {
    auto frame = *it;
    float v = (200 + rand() % 55)/255.0f;
    canvas.drawRect(frame, Color::RGBA(v, v, v, 1.0f));
  }
  
    {
      int width = canvas.getSize().w;
      int height = canvas.getSize().h;
  
      CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, canvas.getData(), width*height*4, NULL);
  
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
}



TEST_CASE("MaxRectsPacker packs ", "[MaxRectsPacker]") {
  
  MaxRectsPacker packer({ 1024, 1024 });
  
  srand(time(nullptr));
  for (int i = 0; i < 80; i++) {
    int w = 40 + rand() % 200;
    int h = 40 + rand() % 200;
    
    packer.placeNextFrame({ w, h });
  }
  
//  packer.placeNextFrame({ 10, 10 });
//  
//  packer.placeNextFrame({ 20, 10 });
  
  drawPack(packer);
}