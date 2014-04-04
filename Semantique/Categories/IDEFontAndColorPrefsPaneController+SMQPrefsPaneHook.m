//
//  IDEFontAndColorPrefsPaneController+SMQPrefsPaneHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 4/3/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEFontAndColorPrefsPaneController+SMQPrefsPaneHook.h"
#import "SMQSwizzling.h"

static IMP originalViewLoadImp;

@implementation IDEFontAndColorPrefsPaneController (SMQPrefsPaneHook)

#pragma mark - Swizzling

+ (void)load
{
    originalViewLoadImp = SMQPoseSwizzle([IDEFontAndColorPrefsPaneController class], @selector(loadView), self, @selector(smq_loadView), YES);
}

#pragma mark - View Methods

- (void)smq_loadView
{
    // Load the original view.
    originalViewLoadImp(self, @selector(loadView));

    // This is the view that acts as a tab/replacement view.
    DVTTabChooserView *tabChooser = [self smq_tabChooserView];

    // Customize the choices in two stages:
    // First, add the variables object (for changing saturation and brightness and whatnot)
    // Change the original "Source Editor" one to be more descriptive.

    NSMutableArray *choices = [[NSMutableArray alloc] initWithArray:tabChooser.choices];
    [choices addObject:[[DVTChoice alloc] initWithTitle:@"Variables" toolTip:@"Variables" image:nil representedObject:nil]];

    DVTChoice *sourceCodeEditorChoice = choices[0];
    [sourceCodeEditorChoice setValue:@"Standard Type Coloring" forKey:@"title"];

    DVTChoice *consoleChoice = choices[1];
    [consoleChoice setValue:@"LLDB Output" forKey:@"title"];

    tabChooser.choices = choices;
}

#pragma mark - Convenience

- (DVTTabChooserView *)smq_tabChooserView
{
    return [self valueForKey:@"_tabChooserView"];
}

@end
