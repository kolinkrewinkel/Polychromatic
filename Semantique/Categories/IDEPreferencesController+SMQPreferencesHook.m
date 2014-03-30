//
//  IDEPreferencesController+SMQPreferencesHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/30/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEPreferencesController+SMQPreferencesHook.h"
#import "SMQSwizzling.h"

static IMP originalWindowDidLoadImplementation;

@implementation IDEPreferencesController (SMQPreferencesHook)

+ (void)initialize
{
    originalWindowDidLoadImplementation = SMQPoseSwizzle(self, @selector(windowDidLoad), self, @selector(smq_windowDidLoad), YES);
}

- (void)smq_windowDidLoad
{
    originalWindowDidLoadImplementation(self, @selector(windowDidLoad));

//    [[self.window toolbar] insertItemWithItemIdentifier:@"TEST" atIndex:0];
}

@end
