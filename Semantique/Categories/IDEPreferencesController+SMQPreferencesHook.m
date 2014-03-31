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
static IMP originalReplacementViewWillInstallViewControllerImplementation;

@implementation IDEPreferencesController (SMQPreferencesHook)

+ (void)load
{
    originalWindowDidLoadImplementation = SMQPoseSwizzle(self, @selector(windowDidLoad), self, @selector(smq_windowDidLoad), YES);
    originalReplacementViewWillInstallViewControllerImplementation = SMQPoseSwizzle(self, @selector(replacementView:willInstallViewController:), self, @selector(smq_replacementView:willInstallViewController:), YES);
}

- (void)smq_windowDidLoad
{
    originalWindowDidLoadImplementation(self, @selector(windowDidLoad));
}

- (void)smq_replacementView:(DVTReplacementView *)replacementView willInstallViewController:(IDEViewController *)viewController
{
    originalReplacementViewWillInstallViewControllerImplementation(self, @selector(replacementView:willInstallViewController:), replacementView, viewController);

    if ([self.window.toolbar.selectedItemIdentifier isEqualToString:@"Xcode.PreferencePane.FontAndColor"])
    {
        [viewController.view.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    }
}

@end
