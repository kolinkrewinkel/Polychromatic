//
//  Polychromatic.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "Polychromatic.h"

@interface Polychromatic()

@property (nonatomic, strong) NSBundle *bundle;

@end

@implementation Polychromatic

+ (void)pluginDidLoad:(NSBundle *)plugin
{
    NSString *currentApplicationName = [[NSBundle mainBundle] infoDictionary][@"CFBundleName"];

    if ([currentApplicationName isEqual:@"Xcode"])
    {
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
    if ((self = [super init]))
    {
        self.bundle = bundle;

        dispatch_async(dispatch_get_main_queue(), ^{
            NSMenuItem *editorMenuItem = [[NSApp mainMenu] itemWithTitle:@"Xcode"];
            NSUInteger startingIndex = 7;

            [[editorMenuItem submenu] insertItem:[NSMenuItem separatorItem] atIndex:startingIndex];

            NSMenuItem *installItem = [[NSMenuItem alloc] initWithTitle:@"Install Polychromatic Templates" action:@selector(showInstallWindow:) keyEquivalent:@"I"];
            installItem.target = self;
            [[editorMenuItem submenu] insertItem:installItem atIndex:startingIndex + 1];

            [[editorMenuItem submenu] insertItem:[NSMenuItem separatorItem] atIndex:startingIndex + 2];
        });

        BOOL hasCompletedFirstRun = [[NSUserDefaults standardUserDefaults] boolForKey:@"SMQHasCompletedFirstRun"];
        if (!hasCompletedFirstRun)
        {
            [self showInstallWindow:self];
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"SMQHasCompletedFirstRun"];
        }
    }

    return self;
}

- (void)showInstallWindow:(id)sender
{
    NSAlert *alert = [NSAlert alertWithMessageText:@"Polychromatic" defaultButton:@"Install Themes" alternateButton:@"Dismiss" otherButton:nil informativeTextWithFormat:@"This plugin is intended for use with monochromatic colors for all types except vibrant variables (local and instance variables, as well as properties.)\n\nTasteful sample themes are provided to demo the concept. Installing them as a basis is recommended."];

    if ([alert runModal] == 1)
    {
        __block NSError *error = nil;
        NSString *basePath = [self.bundle resourcePath];
        NSArray *themes = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:basePath error:&error] filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self.absoluteString ENDSWITH '.dvtcolortheme'"]];

        if (error)
        {
            NSLog(@"nsfilemanager error: %@", error);

            return;
        }

        [themes enumerateObjectsUsingBlock:^(NSString *themePath, NSUInteger idx, BOOL *stop) {
            NSString *replacementName = [themePath.lastPathComponent stringByReplacingOccurrencesOfString:@".dvtcolortheme" withString:@" (Polychromatic).dvtcolortheme"];
            [[NSFileManager defaultManager] copyItemAtPath:[NSString stringWithFormat:@"%@/%@", basePath, themePath] toPath:[NSString stringWithFormat:@"%@/Library/Developer/Xcode/UserData/FontAndColorThemes/%@", NSHomeDirectory(), replacementName] error:&error];
        }];
    }
}

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    return YES;
}

@end
