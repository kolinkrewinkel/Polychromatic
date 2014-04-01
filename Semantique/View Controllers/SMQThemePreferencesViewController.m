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

    NSView *contentView = [[NSView alloc] initWithFrame:self.view.bounds];
    contentView.wantsLayer = YES;

    [self.view setValue:contentView forKey:@"contentView"];
}

#pragma mark - Sizing

- (CGFloat)preferredContentHeight
{
    return 472.f;
}

@end
