//
//  SMQView.m
//  Semantique
//
//  Created by Kolin Krewinkel on 4/3/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

// SMQ-GODDAMN-VIEW
// This is so stupid-unnecessary why did i ever leave iOS

#import "SMQView.h"

@implementation SMQView

#pragma mark - Initialization

- (void)commonInit // LOL as if this name will never collide cause everyone uses it
{
    self.wantsLayer = YES;
}

- (id)init
{
    if ((self = [super init]))
    {
        [self commonInit];
    }

    return self;
}

- (id)initWithFrame:(NSRect)frameRect
{
    if ((self = [super initWithFrame:frameRect]))
    {
        [self commonInit];
    }

    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    if ((self = [super initWithCoder:aDecoder]))
    {
        [self commonInit];
    }

    return self;
}

#pragma mark - Bullshit

- (BOOL)isFlipped
{
    return YES;
}

@end
