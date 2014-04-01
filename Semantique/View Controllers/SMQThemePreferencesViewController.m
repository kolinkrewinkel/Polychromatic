//
//  SMQThemePreferencesViewController.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/31/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "SMQThemePreferencesViewController.h"
#import "Semantique.h"

@implementation SMQThemePreferencesViewController

#pragma mark - NSViewController

- (id)init
{
    if ((self = [super init]))
    {
        DVTExtension *extension = [[DVTExtension alloc] init];
        [self setValue:extension forKey:@"representedExtension"];
    }

    return self;
}

- (void)setRepresentedExtension:(DVTExtension *)extension
{
    if (!self.representedExtension)
    {
        [super setRepresentedExtension:extension];
    }
}

- (void)loadView
{
    self.view = [[NSClassFromString(@"DVTControllerContentView") alloc] init];
    [self.view setValue:self forKey:@"viewController"];
}

- (void)setView:(NSView *)view
{
    [super setView:view];

    self.view.wantsLayer = YES;
    self.view.layer.backgroundColor = [NSColor blueColor].CGColor;

    self.view.layer.bounds = CGRectMake(0.f, 0.f, 300.f, 500.f);
//    self.view.layer.

    NSView *contentView = [[NSView alloc] initWithFrame:self.view.layer.bounds];
    contentView.wantsLayer = YES;
    contentView.layer.backgroundColor = [NSColor blueColor].CGColor;

    [self.view setValue:contentView forKey:@"contentView"];
}

@end
