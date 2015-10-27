//
//  DVTTextStorage+PLYHighlightingHook.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2015 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTTextStorage (PLYHighlightingHook)

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index
                        effectiveRange:(NSRangePointer)effectiveRange
                               context:(id)context;

@end
