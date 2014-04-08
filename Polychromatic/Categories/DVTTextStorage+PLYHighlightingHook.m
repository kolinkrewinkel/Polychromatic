//
//  DVTTextStorage+PLYHighlightingHook.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTTextStorage+PLYHighlightingHook.h"

#import "Polychromatic.h"
#import "PLYSwizzling.h"
#import "PLYVariableManager.h"
#import "DVTSourceModelItem+PLYIdentification.h"
#import "DVTFontAndColorTheme+PLYDataInjection.h"

static IMP originalColorAtCharacterIndexImplementation;

@implementation DVTTextStorage (PLYHighlightingHook)

+ (void)initialize
{
    originalColorAtCharacterIndexImplementation = PLYPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(ply_colorAtCharacterIndex:effectiveRange:context:), YES);
}

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(NSDictionary *)context
{
    /* Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward. Once given a range, its broken down by the colorAt: method. It replaces the range pointer passed, which Xcode then applies changes, and adapts the numerical changes.  So, the next thing it asks about is whatever is just beyond whatever the replaced range is. It also takes the previous length (assuming it can fit in the total text range, at which point it defaults to the max value before subtracting), and subtracts the new range length from it to determine the next passed length.     */

    /* We should probably be doing the "effectiveRange" finding, but for now we'll let Xcode solve it out for us. */

    if (![[DVTFontAndColorTheme currentTheme] ply_enabled] || ![[Polychromatic sharedPlugin] pluginEnabled])
    {
        return originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);
    }

    NSColor *color = originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);
    NSRange newRange = *effectiveRange;

    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];
    NSString *string = [self.sourceModelService stringForItem:item];

    IDEIndex *workspaceIndex = context[@"IDEIndex"];
    IDEWorkspace *workspace = [workspaceIndex valueForKey:@"_workspace"];

    /* It's possible for us to simply use the source model, but we may want to express fine-grain control based on the node. Plus, we already have the item onhand. */

    if ([item ply_isIdentifier] && ![[DVTSourceNodeTypes nodeTypeNameForId:item.parent.nodeType] isEqualToString:@"xcode.syntax.name.partial"] && workspaceIndex)
    {
        color = [[PLYVariableManager sharedManager] colorForVariable:string inWorkspace:workspace];
    }

    return color;
}

@end
