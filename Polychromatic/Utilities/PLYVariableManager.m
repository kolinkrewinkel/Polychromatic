//
//  PLYVariableManager.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <CommonCrypto/CommonDigest.h>

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
    /*NSMutableOrderedSet *variables = [self variableSetForWorkspace:workspace];

    if (!variables && workspace.filePath.pathString)
    {
        variables = [[NSMutableOrderedSet alloc] init];
        [self.workspaces setObject:variables forKey:workspace.filePath.pathString];
    }

    if (![variables containsObject:variable])
    {
        [variables addObject:variable];
        [variables sortUsingDescriptors:@[[[NSSortDescriptor alloc] initWithKey:@"self" ascending:YES selector:@selector(localizedCaseInsensitiveCompare:)]]];
    }*/
    
    NSData *data = [variable dataUsingEncoding:NSUTF8StringEncoding];

    CC_MD5_CTX ctx;
    CC_MD5_Init(&ctx);
    CC_MD5_Update(&ctx, data.bytes, (CC_LONG)data.length);
    unsigned char digest[16];
    CC_MD5_Final(digest, &ctx);
    
    uint32_t value = *((uint32_t *)digest);
    
    CGFloat hueValue = ((CGFloat)value) / (CGFloat)UINT32_MAX;

    return [NSColor colorWithCalibratedHue:hueValue saturation:[[DVTFontAndColorTheme currentTheme] ply_saturation] brightness:[[DVTFontAndColorTheme currentTheme] ply_brightness] alpha:1.f];
}

- (void)indexDidIndexWorkspaceNotification:(NSNotification *)notification
{
    IDEIndex *index = notification.object;
    IDEWorkspace *workspace = [index valueForKey:@"_workspace"];

    [[self variableSetForWorkspace:workspace] removeAllObjects];
}

@end