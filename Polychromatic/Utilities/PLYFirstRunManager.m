//
//  PLYFirstRunManager.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 10/26/15.
//  Copyright © 2015 Kolin Krewinkel. All rights reserved.
//

@import AppKit;

#import "DVTInterfaces.h"
#import "PolychromaticPlugin.h"

#import "PLYFirstRunManager.h"

// External
NSString *kPLYHasCompletedFirstRunKey = @"PLYHasCompletedFirstRun";

// Internal
static NSString *kThemePath = @"Library/Developer/Xcode/UserData/FontAndColorThemes";

@implementation PLYFirstRunManager

- (BOOL)isFirstRun
{
    return ![[NSUserDefaults standardUserDefaults] boolForKey:kPLYHasCompletedFirstRunKey];
}

- (void)showFirstRunFlowIfNeeded
{
    if (self.isFirstRun) {
        [self showFirstRunFlow];
        
        // Make sure `isFirstRun` is updated so it doesn't get shown again.
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:kPLYHasCompletedFirstRunKey];
    }
}

- (void)showFirstRunFlow
{
    NSAlert *alert = [NSAlert alertWithMessageText:@"Polychromatic"
                                     defaultButton:@"Install Themes"
                                   alternateButton:@"Dismiss"
                                       otherButton:nil
                         informativeTextWithFormat:@"This plugin works best when everything is monochromatic except variables.\n\nSample themes are provided. Installing them is recommended to get started..."];
    
    if ([alert runModal] == 1) {
        [self installSampleThemes];
    }   
}

- (void)installSampleThemes
{
    // Get all the sample items included in the "Bundled Themes" directory.
    NSBundle *bundle = [PolychromaticPlugin sharedPlugin].bundle;
    NSString *basePath = [bundle.resourcePath stringByAppendingPathComponent:@"Bundled Themes"];
    
    NSError *readError = nil;
    NSArray *themeDirContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:basePath error:&readError];
    if (readError) {
        [[NSAlert alertWithError:readError] runModal];
        return;
    }
    
    // Filter out anything that's not a `dvtcolortheme`. This isn't really necessary, but it prevents random files from
    // getting copied in if anyone ever messed with the bundle contents.
    NSPredicate *filter = [NSPredicate predicateWithFormat:@"self.absoluteString ENDSWITH '.dvtcolortheme'"];
    NSArray *filteredThemes = [themeDirContents filteredArrayUsingPredicate:filter];

    // Create the directory to copy the themes into.
    NSString *destinationDirectory = [NSString stringWithFormat:@"%@/%@", NSHomeDirectory(), kThemePath];
    
    NSError *dirCreationError = nil;
    [[NSFileManager defaultManager] createDirectoryAtPath:destinationDirectory
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:&dirCreationError];
    if (dirCreationError) {
        [[NSAlert alertWithError:dirCreationError] runModal];
        return;
    }
    
    __block NSError *themeCopyError = nil;
    [filteredThemes enumerateObjectsUsingBlock:^(NSString *themePath, NSUInteger idx, BOOL *stop) {
        // Change all of the theme names to have "(Polychromatic)" at the end so it's clear why they're there.
        NSString *previousSuffix = @".dvtcolortheme";
        NSString *newSuffix = @" (Polychromatic).dvtcolortheme";
        NSString *replacementName = [themePath.lastPathComponent stringByReplacingOccurrencesOfString:previousSuffix
                                                                                           withString:newSuffix];
        
        NSString *destinationPath = [NSString stringWithFormat:@"%@/%@", destinationDirectory, replacementName];
        [[NSFileManager defaultManager] copyItemAtPath:[NSString stringWithFormat:@"%@/%@", basePath, themePath]
                                                toPath:destinationPath
                                                 error:&themeCopyError];
    }];
    
    if (themeCopyError) {
        [[NSAlert alertWithError:themeCopyError] runModal];
        return;
    }

    // Show the theme-preferences window; it must be async in order to have the new themes show.
    dispatch_async(dispatch_get_main_queue(), ^{
        IDEPreferencesController *preferences = [IDEPreferencesController defaultPreferencesController];
        [preferences showWindow:self];
        [preferences selectPreferencePaneWithIdentifier:@"Xcode.PreferencePane.FontAndColor"];       
    });
}

@end
