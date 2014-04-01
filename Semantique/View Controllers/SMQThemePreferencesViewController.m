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

#pragma mark - NSObject

- (id)init
{
    if ((self = [super init]))
    {
        DVTExtension *extension = [[DVTExtension alloc] init];
        [self setValue:extension forKey:@"representedExtension"];
    }

    return self;
}

#pragma mark - NSViewController

- (void)loadView
{
    self.view = [[NSClassFromString(@"DVTControllerContentView") alloc] init];
    [self.view setValue:self forKey:@"viewController"];
}

#pragma mark - DVTViewController

- (void)viewWillUninstall
{

}

#pragma mark - View Management

- (void)setupContentView
{
    NSView *contentView = [self.view valueForKey:@"contentView"];

    NSView *tableView = [[NSView alloc] initWithFrame:NSMakeRect(0.f, 0.f, 100.f, 100.f)];
    tableView.wantsLayer = YES;
    tableView.layer.backgroundColor = [[NSColor redColor] colorWithAlphaComponent:0.1f].CGColor;
    [contentView addSubview:tableView];
}

#pragma mark - Setters

- (void)setRepresentedExtension:(DVTExtension *)extension
{
    if (!self.representedExtension)
    {
        [super setRepresentedExtension:extension];
    }
}

- (void)setView:(NSView *)view
{
    [super setView:view];

    self.view.wantsLayer = YES;
//    self.view.bounds = CGRectMake(0.f, 0.f, 1.f, 1.f);

    self.view.layer.backgroundColor = [[NSColor redColor] colorWithAlphaComponent:0.1f].CGColor;

//    NSLayoutConstraint *width = [NSLayoutConstraint constraintWithItem:self.view attribute:NSLayoutAttributeWidth relatedBy:0 toItem:self.view.superview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
//    NSLayoutConstraint *height = [NSLayoutConstraint constraintWithItem:self.view attribute:NSLayoutAttributeHeight relatedBy:0 toItem:self.view.superview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
//
//    [self.view addConstraints:@[width, height]];

    NSView *contentView = [[NSView alloc] initWithFrame:self.view.bounds];
    contentView.wantsLayer = YES;
    contentView.layer.backgroundColor = [[NSColor redColor] colorWithAlphaComponent:0.1f].CGColor;

    [self.view setValue:contentView forKey:@"contentView"];

    [self setupContentView];
}

#pragma mark - Sizing

- (CGFloat)preferredContentHeight
{
    return 472.f;
}

@end
