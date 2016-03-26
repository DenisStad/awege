//
//  Label.cpp
//  UserInterface
//
//  Created by Denis Stadniczuk on 18/03/16.
//  Copyright © 2016 Awege. All rights reserved.
//

#include "Label.hpp"
#import <Cocoa/Cocoa.h>

Label::Label(std::string text)
:
text(text)
{
  @autoreleasepool {
    NSString *string = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];
    NSDictionary * attributes = @{ NSFontAttributeName: [NSFont systemFontOfSize:17], NSForegroundColorAttributeName: [NSColor whiteColor] };
    NSSize size = [string sizeWithAttributes:attributes];
    naturalSize = { size.width, size.height };
  }
}

awege::Size Label::getNaturalSize()
{
  return naturalSize;
}

void Label::draw(Canvas* canvas)
{
  
  /*
  
  if (UIGraphicsBeginImageContextWithOptions != NULL)
    UIGraphicsBeginImageContextWithOptions(size,NO,0.0);
  else
    // iOS is < 4.0
    UIGraphicsBeginImageContext(size);
  
  // optional: add a shadow, to avoid clipping the shadow you should make the context size bigger
  //
  // CGContextRef ctx = UIGraphicsGetCurrentContext();
  // CGContextSetShadowWithColor(ctx, CGSizeMake(1.0, 1.0), 5.0, [[UIColor grayColor] CGColor]);
  
  // draw in context, you can use also drawInRect:withFont:
  [text drawAtPoint:CGPointMake(0.0, 0.0) withFont:font];
  
  // transfer image
  UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
  UIGraphicsEndImageContext();
  
  return image;
   */
  
  @autoreleasepool {
    NSString *string = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];
    NSDictionary * attributes = @{ NSFontAttributeName: [NSFont systemFontOfSize:17], NSForegroundColorAttributeName: [NSColor whiteColor] };
    
    NSSize size = [string sizeWithAttributes:attributes];
    naturalSize = { size.width, size.height };
    
    NSImage *image = [NSImage imageWithSize:size flipped:YES drawingHandler:^BOOL(NSRect dstRect) {
                      [string drawAtPoint:NSMakePoint(0, 0) withAttributes:attributes];
                      return YES;
                      }];
    
    NSBitmapImageRep *rep = [[NSBitmapImageRep alloc] initWithCGImage:[image CGImageForProposedRect:NULL context:nil hints:nil]];
    
    for (int y = 0; y < rep.size.height; y++) {
      for (int x = 0; x < rep.size.width; x++) {
        NSColor * color = [rep colorAtX:x y:y];
        canvas->drawPixel({ x, y }, Color::RGBA(color.redComponent, color.greenComponent, color.blueComponent, color.alphaComponent));
      }
    }
  }
}