//
//  IDEPreferencesController+SMQPreferencesHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/30/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEPreferencesController+SMQPreferencesHook.h"
#import "SMQSwizzling.h"
#import "SMQThemePreferencesViewController.h"

static IMP originalWindowDidLoadImplementation;
static IMP originalReplacementViewWillInstallViewControllerImplementation;

static char *SMQThemePreferencesViewControllerName = "SMQThemePreferencesViewControllerName";

@implementation IDEPreferencesController (SMQPreferencesHook)

#pragma mark - NSObject

+ (void)load
{
    originalWindowDidLoadImplementation = SMQPoseSwizzle(self, @selector(windowDidLoad), self, @selector(smq_windowDidLoad), YES);
    originalReplacementViewWillInstallViewControllerImplementation = SMQPoseSwizzle(self, @selector(replacementView:willInstallViewController:), self, @selector(smq_replacementView:willInstallViewController:), YES);
}

#pragma mark - Swizzled Methods

- (void)smq_windowDidLoad
{
    originalWindowDidLoadImplementation(self, @selector(windowDidLoad));
}

- (void)smq_replacementView:(DVTReplacementView *)replacementView willInstallViewController:(IDEViewController *)viewController
{

    if ([self.window.toolbar.selectedItemIdentifier isEqualToString:@"Xcode.PreferencePane.FontAndColor"] && ![viewController isKindOfClass:[SMQThemePreferencesViewController class]])
    {
        SMQThemePreferencesViewController *newViewController = [[SMQThemePreferencesViewController alloc] init];
//
//        [self smq_setReplacementThemePreferencesViewController:newViewController];
//
//        [viewController.view.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
//        newViewController.view = viewController.view;
        replacementView.installedViewController = newViewController;

        originalReplacementViewWillInstallViewControllerImplementation(self, @selector(replacementView:willInstallViewController:), replacementView, newViewController);

    }
    else
    {
        [self smq_setReplacementThemePreferencesViewController:nil];

        originalReplacementViewWillInstallViewControllerImplementation(self, @selector(replacementView:willInstallViewController:), replacementView, viewController);

    }


}

#pragma mark - Setters

- (void)smq_setReplacementThemePreferencesViewController:(SMQThemePreferencesViewController *)replacementViewController
{
//    SMQThemePreferencesViewController *existingViewController = [self replacementThemePreferencesViewController];
//
//    if (existingViewController && !replacementViewController)
//    {
//        [existingViewController.view removeFromSuperview];
//    }

    objc_setAssociatedObject(self, SMQThemePreferencesViewControllerName, replacementViewController, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

#pragma mark - Getters

- (SMQThemePreferencesViewController *)replacementThemePreferencesViewController
{
    return objc_getAssociatedObject(self, SMQThemePreferencesViewControllerName);
}

@end
