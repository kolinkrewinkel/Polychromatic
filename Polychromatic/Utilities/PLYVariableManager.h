//
//  PLYVariableManager.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <AppKit/AppKit.h>

@class IDEWorkspace;
@interface PLYVariableManager : NSObject

+ (instancetype)sharedManager;

- (NSColor *)colorForVariable:(NSString *)variable;

@end
