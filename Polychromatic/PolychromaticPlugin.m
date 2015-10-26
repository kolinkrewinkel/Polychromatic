//
//  Polychromatic.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "PolychromaticPlugin.h"

@interface PolychromaticPlugin ()

@property (nonatomic, strong) NSBundle *bundle;

@property (nonatomic, strong) NSMenuItem *enableItem;

@end

@implementation PolychromaticPlugin

+ (void)pluginDidLoad:(NSBundle *)plugin
{
    NSString *currentApplicationName = [[NSBundle mainBundle] infoDictionary][@"CFBundleName"];

    if ([currentApplicationName isEqual:@"Xcode"]) {
        [self sharedPluginWithBundle:plugin];
    }
}

+ (instancetype)sharedPluginWithBundle:(NSBundle *)bundle
{
    static id sharedPlugin = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        sharedPlugin = [[self alloc] initWithBundle:bundle];
    });

    return sharedPlugin;
}

+ (instancetype)sharedPlugin
{
    return [self sharedPluginWithBundle:nil];
}

- (id)initWithBundle:(NSBundle *)bundle
{
    if ((self = [super init])) {
        self.bundle = bundle;

        [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"PLYHasCompletedFirstRun": @NO, @"PLYPluginEnabled": @YES}];

        BOOL hasCompletedFirstRun = [[NSUserDefaults standardUserDefaults] boolForKey:@"PLYHasCompletedFirstRun"];
        if (!hasCompletedFirstRun) {
            [self showInstallWindow:self];
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"PLYHasCompletedFirstRun"];
        }

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(modifyEditorMenu:)
                                                     name:NSMenuDidChangeItemNotification
                                                   object:nil];
    }

    return self;
}

- (void)showInstallWindow:(id)sender
{
    NSAlert *alert = [NSAlert alertWithMessageText:@"Polychromatic"
                                     defaultButton:@"Install Themes"
                                   alternateButton:@"Dismiss"
                                       otherButton:nil
                         informativeTextWithFormat:@"This plugin is intended for use with monochromatic colors for all types except vibrant variables (local and instance variables, as well as properties.)\n\nSample themes are provided to demo the concept. Installing them as a basis is recommended."];

    if ([alert runModal] == 1) {
        __block NSError *error = nil;
        NSString *basePath = [self.bundle resourcePath];
        basePath = [basePath stringByAppendingPathComponent:@"Bundled Themes"];
        NSArray *themes = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:basePath error:&error] filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self.absoluteString ENDSWITH '.dvtcolortheme'"]];

        if (error) {
            NSLog(@"nsfilemanager error: %@", error);

            return;
        }

        NSString *destinationDirectory =
        [NSString stringWithFormat:@"%@/Library/Developer/Xcode/UserData/FontAndColorThemes", NSHomeDirectory()];

        [themes enumerateObjectsUsingBlock:^(NSString *themePath, NSUInteger idx, BOOL *stop) {
            NSString *replacementName = [themePath.lastPathComponent stringByReplacingOccurrencesOfString:@".dvtcolortheme" withString:@" (Polychromatic).dvtcolortheme"];
            NSString *destinationPath = [NSString stringWithFormat:@"%@/%@", destinationDirectory, replacementName];

            [[NSFileManager defaultManager] createDirectoryAtPath:destinationDirectory
                                      withIntermediateDirectories:YES
                                                       attributes:nil
                                                            error:NULL];

            [[NSFileManager defaultManager] copyItemAtPath:[NSString stringWithFormat:@"%@/%@", basePath, themePath]
                                                    toPath:destinationPath
                                                     error:&error];
        }];
    }
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

        NSMenuItem *installItem = [[NSMenuItem alloc] initWithTitle:@"Install Sample Themes" action:@selector(showInstallWindow:) keyEquivalent:@"I"];
        installItem.target = self;
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
