//
//  Semantique.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <AppKit/AppKit.h>

@class BBUIndexHelper;

@interface Semantique : NSObject

+ (instancetype)sharedPlugin;

@property (nonatomic, strong) BBUIndexHelper* indexHelper;

@end