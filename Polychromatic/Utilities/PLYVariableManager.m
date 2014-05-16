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
static NSInteger const IDEDefaultNumberOfColors = 10;

@interface PLYVariableManager (){
	NSInteger numberOfColors;
}

@property (nonatomic, strong) NSMutableDictionary *workspaces;
@property (nonatomic, strong) NSMutableArray* colorSpace;

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
		[self fillColorSpace];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(indexDidIndexWorkspaceNotification:) name:IDEIndexDidIndexWorkspaceNotification object:nil];
    }

    return self;
}

#pragma mark - Variable Management

- (void)fillColorSpace {
	self.colorSpace = [NSMutableArray new];
	
	for (int i = 0; i < numberOfColors; i++) {
		CGFloat hueValue = (CGFloat)i/numberOfColors;
		
		NSColor* color = [NSColor colorWithCalibratedHue:hueValue
											  saturation:[[DVTFontAndColorTheme currentTheme] ply_saturation]
											  brightness:[[DVTFontAndColorTheme currentTheme] ply_brightness]
												   alpha:1.f];
		[self.colorSpace addObject:color];
	}
}

- (NSMutableOrderedSet *)variableSetForWorkspace:(IDEWorkspace *)workspace
{
    return self.workspaces[workspace.filePath.pathString];
}

- (NSColor *)colorForVariable:(NSString *)variable inWorkspace:(IDEWorkspace *)workspace
{
    NSMutableOrderedSet *variables = [self variableSetForWorkspace:workspace];

    if (!variables && workspace.filePath.pathString)
    {
        variables = [[NSMutableOrderedSet alloc] init];
        [self.workspaces setObject:variables forKey:workspace.filePath.pathString];
    }

    if (![variables containsObject:variable])
    {
        [variables addObject:variable];
		// Why are you resorting? this only causes colors to possibly change dramatically
		// Preferably removing this cause less hue shifting with adding of new variables
		// but we prefer if variables never change color, for now we will block allocate
		// color space so that color changes happen much less often and cause much less
		// distraction.
		//[variables sortUsingDescriptors:@[[[NSSortDescriptor alloc] initWithKey:@"self" ascending:YES selector:@selector(localizedCaseInsensitiveCompare:)]]];
    }

    NSUInteger index = [variables indexOfObject:variable];
	
	// Only reassign colors if our current colorSpace if full, grow and shrink colorspace
    if (variables.count > numberOfColors) {
		numberOfColors += IDEDefaultNumberOfColors;
		[self fillColorSpace];
	} else if (numberOfColors - IDEDefaultNumberOfColors > variables.count) {
		numberOfColors -= IDEDefaultNumberOfColors;
		[self fillColorSpace];
	}

    return self.colorSpace[index];
}

- (void)indexDidIndexWorkspaceNotification:(NSNotification *)notification
{
    IDEIndex *index = notification.object;
    IDEWorkspace *workspace = [index valueForKey:@"_workspace"];

    [[self variableSetForWorkspace:workspace] removeAllObjects];
}

@end