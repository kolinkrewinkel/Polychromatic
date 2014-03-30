//
//  SMQVariableManager.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "SMQVariableManager.h"
#import "DVTInterfaces.h"

static NSString *const IDEIndexDidIndexWorkspaceNotification = @"IDEIndexDidIndexWorkspaceNotification";

@interface SMQVariableManager ()

@property (nonatomic, strong) NSMutableOrderedSet *variables;

@end

@implementation SMQVariableManager

#pragma mark - Singleton

+ (instancetype)sharedManager
{
    static dispatch_once_t onceToken;
    static id sharedManager;
    dispatch_once(&onceToken, ^{
        sharedManager = [[self alloc] init];
    });

    return sharedManager;
}

#pragma mark - Initialization

- (id)init
{
    if ((self = [super init]))
    {
        self.variables = [[NSMutableOrderedSet alloc] init];

        [[NSNotificationCenter defaultCenter] addObserverForName:IDEIndexDidIndexWorkspaceNotification object:nil queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification *note) {
            NSLog(@"Reindexed.");
        }];
    }

    return self;
}

#pragma mark - Variable Management

- (NSColor *)colorForVariable:(NSString *)variable
{
    if (![self.variables containsObject:variable])
    {
        [self.variables addObject:variable];
        [self.variables sortUsingDescriptors:@[[[NSSortDescriptor alloc] initWithKey:@"self" ascending:YES selector:@selector(localizedCaseInsensitiveCompare:)]]];
    }

    NSUInteger index = [self.variables indexOfObject:variable];
    CGFloat hueValue = (CGFloat)index/self.variables.count;

    return [NSColor colorWithCalibratedHue:hueValue saturation:0.55f brightness:0.8f alpha:1.f];
}

@end