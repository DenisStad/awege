//
//  test.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "test.hpp"

#import <Foundation/Foundation.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Length.hpp"
#include "Canvas.hpp"
#include "AutoSizeCanvas.hpp"
#include "Color.hpp"

void test()
{
}


TEST_CASE("Length stores pixel values", "[length]") {
  
  auto length = Length::Pixels(5);
  
  REQUIRE(length->pixels() == 5);
  REQUIRE(length->fractionOfParent() == 0.0f);
  REQUIRE(length->isPixelsDeterminable() == true);
}

TEST_CASE("Length stores fraction values", "[length]") {
  
  auto length = Length::Fraction(0.3f, nullptr);
  
  REQUIRE(length->fractionOfParent() == 0.3f);
  REQUIRE(length->pixels() == 0.0f);
  REQUIRE(length->isPixelsDeterminable() == false);
}

TEST_CASE("Length determine pixels of fraction", "[length]") {
  
  auto pixelLength = Length::Pixels(300);
  auto length = Length::Fraction(0.3f, pixelLength);
  
  REQUIRE(length->fractionOfParent() == 0.3f);
  REQUIRE(length->pixels() == 90.0f);
  REQUIRE(length->isPixelsDeterminable() == true);
}

TEST_CASE("Length determine pixels with nested fractions", "[length]") {
  
  auto pixelLength = Length::Pixels(300);
  auto length1 = Length::Fraction(0.3f, pixelLength);
  auto length2 = Length::Fraction(0.5f, length1);
  
  REQUIRE(length1->fractionOfParent() == 0.3f);
  REQUIRE(length1->pixels() == 90.0f);
  REQUIRE(length1->isPixelsDeterminable() == true);
  
  REQUIRE(length2->fractionOfParent() == 0.5f);
  REQUIRE(length2->pixels() == 45.0f);
  REQUIRE(length2->isPixelsDeterminable() == true);
}

TEST_CASE("Length get fraction of unrelated lengths", "[length]") {
  
  auto pixelLength = Length::Pixels(300);
  auto length1 = Length::Fraction(0.3f, pixelLength);
  auto length2 = Length::Fraction(0.5f, nullptr);
  auto length3 = Length::Fraction(0.5f, length1);
  
  REQUIRE(length1->fractionOfParent() == 0.3f);
  REQUIRE(length1->pixels() == 90.0f);
  REQUIRE(length1->isPixelsDeterminable() == true);
  
  REQUIRE(length2->fractionOfParent() == 0.5f);
  REQUIRE(length2->pixels() == 0.0f);
  REQUIRE(length2->isPixelsDeterminable() == false);
  
  REQUIRE(length1->fraction(length2) == 0.0f);
  REQUIRE(length2->fraction(length1) == 0.0f);
  REQUIRE(length2->fraction(length3) == 0.0f);
  REQUIRE(length3->fraction(pixelLength) == 0.15f);
}

TEST_CASE("Plain frame intersection 1", "[plain frame]") {
  
  PlainFrame frame1({0,0}, {10, 10});
  PlainFrame frame2({2,3}, {10, 10});
  
  auto intersection = frame1.intersection(frame2);
  
  REQUIRE(intersection.position.x == 2);
  REQUIRE(intersection.position.y == 3);
  REQUIRE(intersection.size.w == 8);
  REQUIRE(intersection.size.h == 7);
}

TEST_CASE("Plain frame intersection 2", "[plain frame]") {
  
  PlainFrame frame1({2,3}, {10, 10});
  PlainFrame frame2({1,1}, {2, 4});
  
  auto intersection = frame1.intersection(frame2);
  
  REQUIRE(intersection.position.x == 2);
  REQUIRE(intersection.position.y == 3);
  REQUIRE(intersection.size.w == 1);
  REQUIRE(intersection.size.h == 2);
}

TEST_CASE("Plain frame intersection 3", "[plain frame]") {
  
  PlainFrame frame1({20,30}, {10, 10});
  PlainFrame frame2({1,1}, {2, 4});
  
  auto intersection = frame1.intersection(frame2);
  
  REQUIRE(intersection.position.x == 20);
  REQUIRE(intersection.position.y == 30);
  REQUIRE(intersection.size.w == 0);
  REQUIRE(intersection.size.h == 0);
}

TEST_CASE("Should clear rect", "[canvas]") {
  
  Canvas canvas;
  canvas.setSize({100, 100});
  canvas.clearRect(PlainFrame({1, 1}, {98, 98}), Color::RGBA(0, 0.5, 0.5, 1));
  canvas.drawPixel(PlainPosition({2, 2}), Color::RGBA(0, 0, 0, 0.5));
  canvas.drawPixel(PlainPosition({2, 3}), Color::RGBA(0, 0, 1, 0.1));
  canvas.drawPixel(PlainPosition({2, 4}), Color::RGBA(1, 0, 0, 0.8));
  canvas.drawPoint(PlainPosition({20, 20}), 10, Color::RGBA(0, 0, 1, 1));
  canvas.drawRect({{20, 10}, {10, 20}}, Color::RGBA(1, 0, 0, 0.3));
  
//  {
//    int width = 100;
//    int height = 100;
//    
//    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, canvas.getData(), width*height*4, NULL);
//    
//    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
//    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
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
//    CGImageDestinationRef destination =  CGImageDestinationCreateWithURL((__bridge CFURLRef) [NSURL fileURLWithPath:@"/Users/denis/out.png"], type, 1, nil);
//    CGImageDestinationAddImage(destination, imageRef, nil);
//    
//    if (!CGImageDestinationFinalize(destination)) {
//      NSLog(@"Failed to write image to");
//    }
//    
//    CFRelease(destination);
//  }
}

TEST_CASE("Should draw on auto resized canvas", "[canvas]") {
  
  AutoSizeCanvas canvas;
  canvas.clearRect(PlainFrame({1, 1}, {10, 10}), Color::RGBA(0, 0.5, 0.5, 1));
  canvas.drawPoint(PlainPosition({20, -20}), 10, Color::RGBA(0, 0, 1, 1));
  canvas.drawRect({{20, 10}, {100, 80}}, Color::RGBA(1, 0, 0, 0.3));
  
//  {
//    int width = canvas.getSize().w;
//    int height = canvas.getSize().h;
//    
//    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, canvas.getData(), width*height*4, NULL);
//    
//    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
//    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
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
//    CGImageDestinationRef destination =  CGImageDestinationCreateWithURL((__bridge CFURLRef) [NSURL fileURLWithPath:@"/Users/denis/out.png"], type, 1, nil);
//    CGImageDestinationAddImage(destination, imageRef, nil);
//    
//    if (!CGImageDestinationFinalize(destination)) {
//      NSLog(@"Failed to write image to");
//    }
//    
//    CFRelease(destination);
//  }
}

