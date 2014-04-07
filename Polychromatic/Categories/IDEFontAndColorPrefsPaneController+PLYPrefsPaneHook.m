//
//  IDEFontAndColorPrefsPaneController+PLYPrefsPaneHook.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/3/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEFontAndColorPrefsPaneController+PLYPrefsPaneHook.h"
#import "PLYSwizzling.h"
#import "PLYView.h"
#import "DVTFontAndColorTheme+PLYDataInjection.h"

static IMP originalViewLoadImp;
static IMP originalTabChangeImp;
static IMP originalFontPickerImp;

static char *PLYVariableColorModifierViewIdentifier = "PLYVariableColorModifierViewIdentifier";

@implementation IDEFontAndColorPrefsPaneController (PLYPrefsPaneHook)

#pragma mark - Swizzling

+ (void)load
{
    originalViewLoadImp = PLYPoseSwizzle([IDEFontAndColorPrefsPaneController class], @selector(loadView), self, @selector(PLY_loadView), YES);
    originalTabChangeImp = PLYPoseSwizzle([IDEFontAndColorPrefsPaneController class], @selector(_handleTabChanged), self, @selector(PLY_handleTabChanged), YES);
    originalFontPickerImp = PLYPoseSwizzle(self, @selector(_updateFontPickerAndColorWell), self, @selector(PLY_updateFontPickerAndColorWell), YES);
}

#pragma mark - View Methods

- (void)PLY_loadView
{
    // Load the original view.
    originalViewLoadImp(self, @selector(loadView));

    [self configureTabChooserView];
    [self setupVariablesPane];
}

- (void)configureTabChooserView
{
    // This is the view that acts as a tab/replacement view.
    DVTTabChooserView *tabChooser = [self PLY_tabChooserView];

    // Customize the choices in two stages:
    // First, add the variables object (for changing saturation and brightness and whatnot)
    // Change the original "Source Editor" one to be more descriptive.

    NSMutableArray *choices = [[NSMutableArray alloc] initWithArray:tabChooser.choices];
    [choices addObject:[[DVTChoice alloc] initWithTitle:@"Variables" toolTip:@"Variables" image:nil representedObject:nil]];

    DVTChoice *sourceCodeEditorChoice = choices[0];
    [sourceCodeEditorChoice setValue:@"Types" forKey:@"title"];

    DVTChoice *consoleChoice = choices[1];
    [consoleChoice setValue:@"LLDB" forKey:@"title"];

    tabChooser.choices = choices;
}

- (void)PLY_updateFontPickerAndColorWell
{
    originalFontPickerImp(self, @selector(_updateFontPickerAndColorWell));

    [self saturationSlider].floatValue = [[self theme] PLY_saturation];
    [self PLY_setSaturation:[[self theme] PLY_saturation]];

    [self brightnessSlider].floatValue = [[self theme] PLY_brightness];
    [self PLY_setBrightness:[[self theme] PLY_brightness]];

    if ([self PLY_varPrefsView].superview)
    {
        [self adjustColorWellSamples];
    }
}

- (void)setupVariablesPane
{
    PLYView *variablePrefsView = [[PLYView alloc] initWithFrame:CGRectMake(0.f, 0.f, [self PLY_fontAndColorItemTable].frame.size.width, 285.f)];
    [variablePrefsView setAutoresizingMask:NSViewHeightSizable];

    NSTextField *saturationLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 30.f, 80.f, 20.f)];
    [saturationLabel setEditable:NO];
    [saturationLabel setBezeled:NO];
    [saturationLabel setSelectable:NO];
    saturationLabel.stringValue = @"Saturation:";
    saturationLabel.wantsLayer = YES;
    [variablePrefsView addSubview:saturationLabel];

    NSSlider *saturationSlider = [[NSSlider alloc] initWithFrame:NSMakeRect(115.f, 27.f, variablePrefsView.frame.size.width - (115.f * 2.f), 30.f)];
    [saturationSlider setAction:@selector(saturationChanged:)];
    [saturationSlider setTarget:self];
    saturationSlider.numberOfTickMarks = 2;
    saturationSlider.maxValue = 1;
    [variablePrefsView addSubview:saturationSlider];
    [self PLY_setSaturationSlider:saturationSlider];

    NSTextField *brightnessLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 70.f, 80.f, 20.f)];
    [brightnessLabel setEditable:NO];
    [brightnessLabel setBezeled:NO];
    [brightnessLabel setSelectable:NO];
    brightnessLabel.stringValue = @"Brightness:";
    brightnessLabel.wantsLayer = YES;
    [variablePrefsView addSubview:brightnessLabel];

    NSSlider *brightnessSlider = [[NSSlider alloc] initWithFrame:NSMakeRect(115.f, 67.f, variablePrefsView.frame.size.width - (115.f * 2.f), 30.f)];
    [brightnessSlider setAction:@selector(brightnessChanged:)];
    [brightnessSlider setTarget:self];
    brightnessSlider.numberOfTickMarks = 2;
    brightnessSlider.maxValue = 1;
    [variablePrefsView addSubview:brightnessSlider];
    [self PLY_setBrightnessSlider:brightnessSlider];

    NSTextField *descriptionLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 115.f, 400.f, 160.f)];
    [descriptionLabel setEditable:NO];
    [descriptionLabel setBezeled:NO];
    [descriptionLabel setSelectable:NO];
    descriptionLabel.textColor = [NSColor darkGrayColor];
    descriptionLabel.stringValue = @"Local variables, properties, and ivars, as well as statics and arguments are colored.\n\nThey are assigned a  color by adding them to a sorted set. Essentially, they are given a transient position on the spectrum, and the saturation and brightness levels are pre-defined to maintain a sense of consistency.\n\nBy doing this, a clash of neons versus pastels does not occur while the hue itself can shift.";
    [variablePrefsView addSubview:descriptionLabel];

    [self PLY_setVarPrefsView:variablePrefsView];

    [self _updateFontPickerAndColorWell];
}

- (void)PLY_handleTabChanged
{
    if ([[self PLY_tabChooserView].choices indexOfObject:[self PLY_tabChooserView].selectedChoice] < 2)
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
    NSTableView *fontsTableView = [self PLY_fontAndColorItemTable];

    if (hidden && !fontsTableView.superview)
    {
        for (NSColorWell *colorWell in [self colorWells])
        {
            [self restoreColorWell:colorWell];
        }

        NSScrollView *scrollView = (NSScrollView *)[self PLY_varPrefsView].superview.superview;
        scrollView.documentView = fontsTableView;
    }
    else if (!hidden && fontsTableView.superview)
    {
        NSScrollView *scrollView = (NSScrollView *)fontsTableView.superview.superview;
        scrollView.documentView = [self PLY_varPrefsView];

        for (NSColorWell *colorWell in [self colorWells])
        {
            [self preserveColorWell:colorWell];
        }

        [self adjustColorWellSamples];
    }
}

- (void)addSubviewsOfView:(NSView *)view withClass:(Class)class inArray:(NSMutableArray *)array excludingView:(NSView *)excludingView
{
    if (view == excludingView)
    {
        return;
    }

    for (NSView *subview in view.subviews)
    {
        if ([subview isKindOfClass:class])
        {
            [array addObject:subview];
        }

        [self addSubviewsOfView:subview withClass:class inArray:array excludingView:excludingView];
    }
}

- (NSArray *)colorWells
{
    NSMutableArray *colorWells = [[NSMutableArray alloc] init];
    [self addSubviewsOfView:self.view withClass:[NSColorWell class] inArray:colorWells excludingView:[self PLY_varPrefsView].superview.superview.superview];

    return colorWells;
}

- (void)adjustColorWellSamples
{
    NSArray *colorWells = [self colorWells];

    NSUInteger index = 0;
    for (NSColorWell *colorWell in colorWells)
    {
        CGFloat hue = (CGFloat)index/colorWells.count;
        [colorWell setColor:[NSColor colorWithCalibratedHue:hue saturation:self.PLY_Saturation brightness:self.PLY_Brightness alpha:1.f]];

        index++;

        NSView *superview = colorWell.superview;
        NSTextField *label = [superview.subviews lastObject];
        label.stringValue = [NSString stringWithFormat:@"Sample %lu", index];
    }
}

- (void)preserveColorWell:(NSColorWell *)colorWell
{
    NSView *superview = colorWell.superview;
    NSTextField *label = [superview.subviews lastObject];

    objc_setAssociatedObject(colorWell, "PLY_prevColor", colorWell.color, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(colorWell, "PLY_prevTitle", label.stringValue, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (void)restoreColorWell:(NSColorWell *)colorWell
{
    NSView *superview = colorWell.superview;
    NSTextField *label = [superview.subviews lastObject];

    colorWell.color = objc_getAssociatedObject(colorWell, "PLY_prevColor");
    label.stringValue = objc_getAssociatedObject(colorWell, "PLY_prevTitle");

    objc_setAssociatedObject(colorWell, "PLY_prevColor", nil, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(colorWell, "PLY_prevTitle", nil, OBJC_ASSOCIATION_ASSIGN);
}

- (void)saturationChanged:(NSSlider *)slider
{
    [self PLY_setSaturation:slider.floatValue];

    [[self theme] PLY_setSaturation:slider.floatValue];
    [self theme].contentNeedsSaving = YES;
    
    [self adjustColorWellSamples];
}

- (void)brightnessChanged:(NSSlider *)slider
{
    [self PLY_setBrightness:slider.floatValue];

    [[self theme] PLY_setBrightness:slider.floatValue];
    [self theme].contentNeedsSaving = YES;

    [self adjustColorWellSamples];
}

#pragma mark - Convenience

- (DVTTabChooserView *)PLY_tabChooserView
{
    return [self valueForKey:@"_tabChooserView"];
}

- (DVTFontAndColorTheme *)theme
{
    return [[self valueForKey:@"_currentThemeObjectController"] content];
}

- (NSTableView *)PLY_fontAndColorItemTable
{
    return [self valueForKey:@"_fontAndColorItemTable"];
}

#pragma mark - Associated Object Getters/Setters

- (PLYView *)PLY_varPrefsView
{
    return objc_getAssociatedObject(self, PLYVariableColorModifierViewIdentifier);
}

- (void)PLY_setVarPrefsView:(PLYView *)varPrefsView
{
    objc_setAssociatedObject(self, PLYVariableColorModifierViewIdentifier, varPrefsView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)PLY_Saturation
{
    return [objc_getAssociatedObject(self, "PLY_Saturation") floatValue];
}

- (void)PLY_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, "PLY_Saturation", @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)PLY_Brightness
{
    return [objc_getAssociatedObject(self, "PLY_Brightness") floatValue];
}

- (void)PLY_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, "PLY_Brightness", @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSSlider *)saturationSlider
{
    return objc_getAssociatedObject(self, "PLY_saturationSlider");
}

- (void)PLY_setSaturationSlider:(NSSlider *)slider
{
    objc_setAssociatedObject(self, "PLY_saturationSlider", slider, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSSlider *)brightnessSlider
{
    return objc_getAssociatedObject(self, "PLY_brightnessSlider");
}

- (void)PLY_setBrightnessSlider:(NSSlider *)slider
{
    objc_setAssociatedObject(self, "PLY_brightnessSlider", slider, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
