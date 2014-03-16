//
//  Semantique.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/9/14.
//    Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "Semantique.h"
#import "SMQSwizzling.h"
#import "DVTTextStorage+SMQHighlightingHook.h"
#import "SMQVariableManager.h"

@interface Semantique()

@property (nonatomic, strong) NSBundle *bundle;

@end

@implementation Semantique

+ (void)pluginDidLoad:(NSBundle *)plugin
{
    NSString *currentApplicationName = [[NSBundle mainBundle] infoDictionary][@"CFBundleName"];
    if ([currentApplicationName isEqual:@"Xcode"]) {
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

- (id)initWithBundle:(NSBundle *)plugin
{
    if (self = [super init]) {
        // reference to plugin's bundle, for resource acccess
        self.bundle = plugin;

        NSLog(@"Plugin loaded.");

        [SMQVariableManager sharedManager];
    }

    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
