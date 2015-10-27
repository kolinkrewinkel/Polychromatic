//
//  Polychromatic.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2015 Kolin Krewinkel. All rights reserved.
//

@import AppKit;

#import "PLYFirstRunManager.h"

#import "PolychromaticPlugin.h"

@interface PolychromaticPlugin ()

@property (nonatomic, strong) NSBundle *bundle;

@property (nonatomic) PLYFirstRunManager *firstRunManager;

@property (nonatomic, strong) NSMenuItem *enableItem;

@end

@implementation PolychromaticPlugin

#pragma mark - Xcode

/**
 * Xcode will message this class method on statrtup to allow us to allocate a singleton for the plugin. No work should
 * be done in this method other than its allocation.
 */
+ (void)pluginDidLoad:(NSBundle *)plugin
{
    NSString *appName = [[NSBundle mainBundle] infoDictionary][(NSString *)kCFBundleNameKey];
    if (![appName isEqual:@"Xcode"]) {
        return;
    }
    
    [self sharedPluginWithBundle:plugin];
}

#pragma mark - Instantiation

+ (instancetype)sharedPluginWithBundle:(NSBundle *)bundle
{
    static id sharedPlugin;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        sharedPlugin = [[self alloc] initWithBundle:bundle];
    });

    return sharedPlugin;
}

+ (instancetype)sharedPlugin
{
    // Pass in nil for the bundle because the dispatch_once has already been executed with the bundle assigned, so it's
    // unneeded.
    return [self sharedPluginWithBundle:nil];
}

- (instancetype)initWithBundle:(NSBundle *)bundle
{
    if (self = [super init]) {
        self.bundle = bundle;

        // This needs to be wrapped in a dispatch because any references back to sharedPlugin called within will trigger
        // a deadlock.
        dispatch_async(dispatch_get_main_queue(), ^{
            [[NSUserDefaults standardUserDefaults] registerDefaults:@{kPLYHasCompletedFirstRunKey: @NO, @"PLYPluginEnabled": @YES}];
            
            self.firstRunManager = [[PLYFirstRunManager alloc] init];
            [self.firstRunManager showFirstRunFlowIfNeeded];
            
            [[NSNotificationCenter defaultCenter] addObserver:self
                                                     selector:@selector(modifyEditorMenu:)
                                                         name:NSMenuDidChangeItemNotification
                                                       object:nil];
        });
    }

    return self;
}

- (void)toggleEnabled:(id)sender
{
    BOOL newValue = ![[NSUserDefaults standardUserDefaults] boolForKey:@"PLYPluginEnabled"];
    [[NSUserDefaults standardUserDefaults] setBool:newValue forKey:@"PLYPluginEnabled"];

    [self.enableItem setState:newValue ? NSOnState : NSOffState];
}

- (void)modifyEditorMenu:(id)sender
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMenuItem *editorMenuItem = [[NSApp mainMenu] itemWithTitle:@"Editor"];

        if ([editorMenuItem.submenu itemWithTitle:@"Polychromatic"]) {
            return;
        }

        NSMenu *polychromaticMenu = [[NSMenu alloc] initWithTitle:@"Polychromatic"];
        NSMenuItem *menuItem = [[NSMenuItem alloc] init];
        menuItem.title = @"Polychromatic";

        NSMenuItem *installItem = [[NSMenuItem alloc] initWithTitle:@"Install Sample Themes"
                                                             action:@selector(showFirstRunFlow)
                                                      keyEquivalent:@"I"];
        installItem.target = self.firstRunManager;
        [polychromaticMenu addItem:installItem];

        self.enableItem = [[NSMenuItem alloc] initWithTitle:@"Enabled" action:@selector(toggleEnabled:) keyEquivalent:@"E"];

        if ([[NSUserDefaults standardUserDefaults] boolForKey:@"PLYPluginEnabled"]) {
            [self.enableItem setState:NSOnState];
        }

        self.enableItem.target = self;
        [polychromaticMenu addItem:self.enableItem];

        menuItem.submenu = polychromaticMenu;
        [editorMenuItem.submenu addItem:[NSMenuItem separatorItem]];
        [editorMenuItem.submenu addItem:menuItem];
    });
}

- (BOOL)pluginEnabled
{
    return [[NSUserDefaults standardUserDefaults] boolForKey:@"PLYPluginEnabled"];
}

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    return YES;
}

@end
