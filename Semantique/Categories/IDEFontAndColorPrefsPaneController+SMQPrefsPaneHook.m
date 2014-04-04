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
static IMP originalTabChangeImp;

static char *SMQVariableColorModifierViewIdentifier = "SMQVariableColorModifierViewIdentifier";

@implementation IDEFontAndColorPrefsPaneController (SMQPrefsPaneHook)

#pragma mark - Swizzling

+ (void)load
{
    originalViewLoadImp = SMQPoseSwizzle([IDEFontAndColorPrefsPaneController class], @selector(loadView), self, @selector(smq_loadView), YES);
    originalTabChangeImp = SMQPoseSwizzle([IDEFontAndColorPrefsPaneController class], @selector(_handleTabChanged), self, @selector(smq_handleTabChanged), YES);
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

    // Create the variable prefs view.
    NSView *variablePrefsView = [[NSView alloc] initWithFrame:[self smq_fontAndColorItemTable].frame];
    variablePrefsView.wantsLayer = YES;
    variablePrefsView.alphaValue = 0.f;

    [[self smq_fontAndColorItemTable].superview addSubview:variablePrefsView];

    [self smq_setVarPrefsView:variablePrefsView];
}

- (void)smq_handleTabChanged
{
    if ([[self smq_tabChooserView].choices indexOfObject:[self smq_tabChooserView].selectedChoice] < 2)
    {
        [self setVariablePrefsViewHidden:YES];
        originalTabChangeImp(self, @selector(_handleTabChanged));

        return;
    }

    [self setVariablePrefsViewHidden:NO];
}

- (void)setVariablePrefsViewHidden:(BOOL)hidden
{
    // Hide the font/color list view
    [self smq_fontAndColorItemTable].alphaValue = hidden;
    [self smq_varPrefsView].alphaValue = !hidden;
}

#pragma mark - Convenience

- (DVTTabChooserView *)smq_tabChooserView
{
    return [self valueForKey:@"_tabChooserView"];
}

- (NSTableView *)smq_fontAndColorItemTable
{
    return [self valueForKey:@"_fontAndColorItemTable"];
}

#pragma mark - Associated Object Getters/Setters

- (NSView *)smq_varPrefsView
{
    return objc_getAssociatedObject(self, SMQVariableColorModifierViewIdentifier);
}

- (void)smq_setVarPrefsView:(NSView *)varPrefsView
{
    objc_setAssociatedObject(self, SMQVariableColorModifierViewIdentifier, varPrefsView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
