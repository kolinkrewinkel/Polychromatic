//
//  PolychromaticPlugin.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

@import AppKit;

@interface PolychromaticPlugin : NSObject

/**
 * One instance of this class is instantatied per Xcode instance.
 *
 * @return Shared plugin instance
 */
+ (instancetype)sharedPlugin;

- (BOOL)pluginEnabled;

@end