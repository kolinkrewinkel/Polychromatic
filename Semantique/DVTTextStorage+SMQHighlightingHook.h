//
//  DVTTextStorage+SMQHighlightingHook.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVT Classes/OhNoMoreXcodeInterfaces.h"

@interface DVTTextStorage (SMQHighlightingHook)

- (NSColor *)smq_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(id)context;
- (void)smq_fixSyntaxColoringInRange:(NSRange)range;

@end
