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
#import "CPXcodeInterfaces.h"
#import "SMQVariableManager.h"

static IMP originalColorAtCharacterIndexImplementation;

@implementation DVTTextStorage (SMQHighlightingHook)

+ (void)initialize
{
    originalColorAtCharacterIndexImplementation = SMQPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(smq_colorAtCharacterIndex:effectiveRange:context:), YES);
}

- (NSColor *)smq_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(NSDictionary *)context
{
    /* Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward. Once given a range, its broken down by the colorAt: method. It replaces the range pointer passed, which Xcode then applies changes, and adapts the numerical changes.  So, the next thing it asks about is whatever is just beyond whatever the replaced range is. It also takes the previous length (assuming it can fit in the total text range, at which point it defaults to the max value before subtracting), and subtracts the new range length from it to determine the next passed length.     */

    /* We should probably be doing the "effectiveRange" finding, but for now we'll let Xcode solve it out for us. */

    originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);

    NSRange newRange = *effectiveRange;
    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];
    NSString *string = [self.sourceModelService stringForItem:item];

    /* It's possible for us to simply use the source model, but we may want to express fine-grain control based on the node. Plus, we already have the item onhand. */

    NSColor *color = [NSColor whiteColor];

    if ([item smq_isComment])
    {
        color = [NSColor colorWithCalibratedWhite:0.45f alpha:1.f];
    }
    else if ([item smq_isPreprocessor])
    {
        color = [NSColor colorWithCalibratedWhite:0.4f alpha:1.f];
    }
    else if ([item smq_isKeyword])
    {
        color = [NSColor colorWithCalibratedWhite:0.5f alpha:1.000];
    }
    else if ([item smq_isString])
    {
        color = [NSColor colorWithCalibratedWhite:0.7f alpha:1.000];
    }
    else if ([item smq_isSystemFunction] || [item smq_isUserFunction])
    {
        color = [NSColor colorWithCalibratedWhite:0.6f alpha:1.f];
    }
    else if ([item smq_isSystemClass] || [item smq_isUserClass])
    {
        color = [NSColor colorWithCalibratedWhite:0.85f alpha:1.f];
    }
    else if ([item smq_isIdentifier])
    {
        if (![[DVTSourceNodeTypes nodeTypeNameForId:item.parent.nodeType] isEqualToString:@"xcode.syntax.name.partial"])
        {
            // Have as the last option. Otherwise, it'll apply to others and yeah... descendence.
            color = [[SMQVariableManager sharedManager] colorForVariable:string];
        }
        else
        {
            color = [NSColor colorWithCalibratedWhite:1.f alpha:1.f];
        }
    }
    else if ([item smq_isPlain])
    {
        color = [NSColor colorWithCalibratedWhite:0.6f alpha:1.000];
    }

    return color;
}

@end
