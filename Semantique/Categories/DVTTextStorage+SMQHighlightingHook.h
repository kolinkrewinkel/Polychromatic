//
//  DVTTextStorage+SMQHighlightingHook.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTTextStorage (SMQHighlightingHook)

- (NSColor *)smq_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(id)context;

@end
