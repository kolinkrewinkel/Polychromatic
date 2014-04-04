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
    [sourceCodeEditorChoice setValue:@"Types" forKey:@"title"];

    DVTChoice *consoleChoice = choices[1];
    [consoleChoice setValue:@"LLDB" forKey:@"title"];

    tabChooser.choices = choices;
}

- (void)setupVariablesPane
{
    SMQView *variablePrefsView = [[SMQView alloc] initWithFrame:CGRectMake(0.f, 0.f, [self smq_fontAndColorItemTable].frame.size.width, 285.f)];
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

    NSTextField *descriptionLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 115.f, 400.f, 160.f)];
    [descriptionLabel setEditable:NO];
    [descriptionLabel setBezeled:NO];
    [descriptionLabel setSelectable:NO];
    descriptionLabel.textColor = [NSColor darkGrayColor];
    descriptionLabel.stringValue = @"Local variables, properties, and ivars, as well as statics and arguments are colored.\n\nThey are assigned a  color by adding them to a sorted set. Essentially, they are given a transient position on the spectrum, and the saturation and brightness levels are pre-defined to maintain a sense of consistency.\n\nBy doing this, a clash of neons versus pastels does not occur while the hue itself can shift.";
    [variablePrefsView addSubview:descriptionLabel];

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
        for (NSColorWell *colorWell in [self colorWells])
        {
            [self restoreColorWell:colorWell];
        }

        NSScrollView *scrollView = (NSScrollView *)[self smq_varPrefsView].superview.superview;
        scrollView.documentView = fontsTableView;
    }
    else if (!hidden && fontsTableView.superview)
    {
        NSScrollView *scrollView = (NSScrollView *)fontsTableView.superview.superview;
        scrollView.documentView = [self smq_varPrefsView];

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
    [self addSubviewsOfView:self.view withClass:[NSColorWell class] inArray:colorWells excludingView:[self smq_varPrefsView].superview.superview.superview];

    return colorWells;
}

- (void)adjustColorWellSamples
{
    NSArray *colorWells = [self colorWells];

    NSUInteger index = 0;
    for (NSColorWell *colorWell in colorWells)
    {
        CGFloat hue = (CGFloat)index/colorWells.count;
        [colorWell setColor:[NSColor colorWithCalibratedHue:hue saturation:self.smq_Saturation brightness:self.smq_Brightness alpha:1.f]];

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

    objc_setAssociatedObject(colorWell, "smq_prevColor", colorWell.color, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(colorWell, "smq_prevTitle", label.stringValue, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (void)restoreColorWell:(NSColorWell *)colorWell
{
    NSView *superview = colorWell.superview;
    NSTextField *label = [superview.subviews lastObject];

    colorWell.color = objc_getAssociatedObject(colorWell, "smq_prevColor");
    label.stringValue = objc_getAssociatedObject(colorWell, "smq_prevTitle");

    objc_setAssociatedObject(colorWell, "smq_prevColor", nil, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(colorWell, "smq_prevTitle", nil, OBJC_ASSOCIATION_ASSIGN);
}

- (void)saturationChanged:(NSSlider *)slider
{
    [self smq_setSaturation:slider.floatValue];

    [self adjustColorWellSamples];
}

- (void)brightnessChanged:(NSSlider *)slider
{
    [self smq_setBrightness:slider.floatValue];

    [self adjustColorWellSamples];
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

- (CGFloat)smq_Saturation
{
    return [objc_getAssociatedObject(self, "smq_Saturation") floatValue];
}

- (void)smq_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, "smq_Saturation", @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)smq_Brightness
{
    return [objc_getAssociatedObject(self, "smq_Brightness") floatValue];
}

- (void)smq_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, "smq_Brightness", @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
