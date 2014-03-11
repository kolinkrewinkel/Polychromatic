//
//  DVTTextStorage+SMQHighlightingHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTTextStorage+SMQHighlightingHook.h"
#import "SMQSwizzling.h"

@implementation DVTTextStorage (SMQHighlightingHook)

+ (void)initialize
{
    SMQPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(smq_colorAtCharacterIndex:effectiveRange:context:));
    SMQPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"fixSyntaxColoringInRange:"), self, @selector(smq_fixSyntaxColoringInRange:));
}

- (void)smq_fixSyntaxColoringInRange:(NSRange)range
{

}

- (NSColor *)smq_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(id)context
{
    return [NSColor redColor];
}

@end
