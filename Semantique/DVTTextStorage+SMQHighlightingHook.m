//
//  DVTTextStorage+SMQHighlightingHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTTextStorage+SMQHighlightingHook.h"
#import "SMQSwizzling.h"
#import "DVTSourceModelItem+SMQIdentification.h"

static IMP originalColoring;

@implementation DVTTextStorage (SMQHighlightingHook)

+ (void)initialize
{
    originalColoring = SMQPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(smq_colorAtCharacterIndex:effectiveRange:context:));
//    SMQPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"fixSyntaxColoringInRange:"), self, @selector(smq_fixSyntaxColoringInRange:));
}

- (void)smq_fixSyntaxColoringInRange:(NSRange)range
{
}

- (DVTSourceModelItem *)smq_handleItem:(DVTSourceModelItem *)item
{
    if (item.children.count > 0)
    {
        for (DVTSourceModelItem *child in item.children)
        {
            [self smq_handleItem:child];
        }
    }

    return item;
}

- (NSColor *)smq_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(NSDictionary *)context
{
    /* Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward. Once given a range, its broken down by the colorAt: method. It replaces the range pointer passed, which Xcode then applies changes, and adapts the numerical changes.  So, the next thing it asks about is whatever is just beyond whatever the replaced range is. It also takes the previous length (assuming it can fit in the total text range, at which point it defaults to the max value before subtracting), and subtracts the new range length from it to determine the next passed length.     */

    /* We should probably be doing the "effectiveRange" finding, but for now we'll let Xcode solve it out for us. */

    NSColor *color = originalColoring(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);

    NSRange newRange = *effectiveRange;
    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];
    DVTSourceModel *sourceModel = self.sourceModel;

//    NSLog(@"Name: %@\nID: %i", [DVTSourceNodeTypes nodeTypeNameForId:item.nodeType], item.nodeType);
    

    if ([item smq_isString])
    {
        color = [NSColor purpleColor];
    }


    return color;
}

@end
