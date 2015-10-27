//
//  PLYVariableManager.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2015 Kolin Krewinkel. All rights reserved.
//

@import AppKit;

@interface PLYVariableManager : NSObject

+ (instancetype)sharedManager;

- (NSColor *)colorForVariable:(NSString *)variable;

@end
