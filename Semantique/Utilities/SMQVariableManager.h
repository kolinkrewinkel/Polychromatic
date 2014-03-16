//
//  SMQVariableManager.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface SMQVariableManager : NSObject

+ (instancetype)sharedManager;

- (NSColor *)colorForVariable:(NSString *)variable;

@end
