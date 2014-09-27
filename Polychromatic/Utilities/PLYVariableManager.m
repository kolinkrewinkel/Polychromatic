//
//  PLYVariableManager.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "PLYVariableManager.h"
#import "DVTInterfaces.h"

#import "DVTFontAndColorTheme+PLYDataInjection.h"

static NSString *const IDEIndexDidIndexWorkspaceNotification = @"IDEIndexDidIndexWorkspaceNotification";

@interface PLYVariableManager ()

@property (nonatomic, strong) NSMutableDictionary *workspaces;

@end

@implementation PLYVariableManager

#pragma mark - Singleton

+ (instancetype)sharedManager
{
    static dispatch_once_t onceToken;
    static id sharedManager;
    dispatch_once(&onceToken, ^{
        sharedManager = [[self alloc] init];
    });

    return sharedManager;
}

#pragma mark - Initialization

- (id)init
{
    if ((self = [super init]))
    {
        self.workspaces = [[NSMutableDictionary alloc] init];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(indexDidIndexWorkspaceNotification:) name:IDEIndexDidIndexWorkspaceNotification object:nil];
    }

    return self;
}

#pragma mark - Variable Management

- (NSMutableOrderedSet *)variableSetForWorkspace:(IDEWorkspace *)workspace
{
    return self.workspaces[workspace.filePath.pathString];
}

- (NSColor *)colorForVariable:(NSString *)variable inWorkspace:(IDEWorkspace *)workspace
{
    // Not sorting variables might result in the same color,
    // but it ensures that the same variable will always have the same color.
    // This makes it easier to remember variables
    CGFloat hueValue = ([variable ply_FNV1Hash] & 0xff) / (CGFloat)255.0;
    
    return [NSColor colorWithCalibratedHue:hueValue saturation:[[DVTFontAndColorTheme currentTheme] ply_saturation] brightness:[[DVTFontAndColorTheme currentTheme] ply_brightness] alpha:1.f];
}

- (void)indexDidIndexWorkspaceNotification:(NSNotification *)notification
{
    IDEIndex *index = notification.object;
    IDEWorkspace *workspace = [index valueForKey:@"_workspace"];

    [[self variableSetForWorkspace:workspace] removeAllObjects];
}

@end