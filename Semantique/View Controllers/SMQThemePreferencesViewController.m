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

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if ((self = [super initWithNibName:self.className bundle:nibBundleOrNil]))
    {

    }

    return self;
}

#pragma mark - NSViewController

- (void)loadView
{
    [super loadView];

    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"NSConstraintBasedLayoutVisualizeMutuallyExclusiveConstraints"];

    self.view.layer.backgroundColor = [NSColor redColor].CGColor;
}

#pragma mark - DVTViewController

- (void)viewWillUninstall
{

}

#pragma mark - View Management

- (void)setupContentView
{
    NSView *contentView = [self.view valueForKey:@"contentView"];
    [contentView.layer setBackgroundColor:[NSColor greenColor].CGColor];
    contentView.frame = contentView.superview.frame;

    NSLog(@"%@", NSStringFromRect(contentView.frame));
    NSLog(@"%@", NSStringFromRect(contentView.bounds));
    NSLog(@"%@", NSStringFromRect(self.view.frame));
    NSLog(@"%@", NSStringFromRect(self.view.bounds));

//    NSTableView *tableView = [[NSTableView alloc] initWithFrame:NSMakeRect(20.f, 20.f, 144.f, 144.f)];
//    tableView.autoresizingMask = NSViewHeightSizable;
//
//    [self.view addSubview:tableView];
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

    self.view.layer.backgroundColor = [[NSColor redColor] colorWithAlphaComponent:0.1f].CGColor;

//    NSLayoutConstraint *width = [NSLayoutConstraint constraintWithItem:self.view attribute:NSLayoutAttributeWidth relatedBy:0 toItem:self.view.superview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
//    NSLayoutConstraint *height = [NSLayoutConstraint constraintWithItem:self.view attribute:NSLayoutAttributeHeight relatedBy:0 toItem:self.view.superview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
//
//    [self.view addConstraints:@[width, height]];

//    NSView *contentView = [[NSView alloc] initWithFrame:self.view.bounds];
//    contentView.wantsLayer = YES;
//    contentView.layer.backgroundColor = [[NSColor redColor] colorWithAlphaComponent:0.1f].CGColor;
//
//    [self.view setValue:contentView forKey:@"contentView"];

    [self setupContentView];

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(4 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"%@", NSStringFromRect(self.view.frame));
    });
}

#pragma mark - Sizing

- (CGFloat)preferredContentHeight
{
    return 472.f;
}

@end
