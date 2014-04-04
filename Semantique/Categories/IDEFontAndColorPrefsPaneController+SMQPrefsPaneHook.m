//
//  IDEFontAndColorPrefsPaneController+SMQPrefsPaneHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 4/3/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEFontAndColorPrefsPaneController+SMQPrefsPaneHook.h"
#import "SMQSwizzling.h"
#import "SMQView.h"

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

    [self configureTabChooserView];
    [self setupVariablesPane];
}

- (void)configureTabChooserView
{
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

- (void)setupVariablesPane
{
    SMQView *variablePrefsView = [[SMQView alloc] initWithFrame:[self smq_fontAndColorItemTable].frame];
    variablePrefsView.alphaValue = 0.f;
    [variablePrefsView setAutoresizingMask:NSViewHeightSizable];

    NSTextField *saturationLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(20.f, 160.f, 80.f, 20.f)];
    [saturationLabel setEditable:NO];
    [saturationLabel setBezeled:NO];
    [saturationLabel setSelectable:NO];
    saturationLabel.stringValue = @"Saturation:";
    saturationLabel.drawsBackground = NO;
    [variablePrefsView addSubview:saturationLabel];

    NSSlider *saturationSlider = [[NSSlider alloc] initWithFrame:NSMakeRect(95.f, 157.f, 180.f, 30.f)];
    saturationSlider.numberOfTickMarks = 5;
    saturationSlider.maxValue = 1;
    [variablePrefsView addSubview:saturationSlider];

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
    NSTableView *fontsTableView = [self smq_fontAndColorItemTable];

    if (hidden && !fontsTableView.superview)
    {
        [[self smq_varPrefsView].superview addSubview:fontsTableView];
    }
    else if (!hidden && fontsTableView.superview)
    {
        [fontsTableView removeFromSuperview];
    }

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

- (SMQView *)smq_varPrefsView
{
    return objc_getAssociatedObject(self, SMQVariableColorModifierViewIdentifier);
}

- (void)smq_setVarPrefsView:(SMQView *)varPrefsView
{
    objc_setAssociatedObject(self, SMQVariableColorModifierViewIdentifier, varPrefsView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
