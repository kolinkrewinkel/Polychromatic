//
//  Semantique.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/9/14.
//    Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "Semantique.h"
#import "SMQSwizzling.h"

static Semantique *sharedPlugin;

@interface Semantique()

@property (nonatomic, strong) NSBundle *bundle;
@end

@implementation Semantique

+ (void)pluginDidLoad:(NSBundle *)plugin
{
    static id sharedPlugin = nil;
    static dispatch_once_t onceToken;
    NSString *currentApplicationName = [[NSBundle mainBundle] infoDictionary][@"CFBundleName"];
    if ([currentApplicationName isEqual:@"Xcode"]) {
        dispatch_once(&onceToken, ^{
            sharedPlugin = [[self alloc] initWithBundle:plugin];
        });
    }
}

- (id)initWithBundle:(NSBundle *)plugin
{
    if (self = [super init]) {
        // reference to plugin's bundle, for resource acccess
        self.bundle = plugin;

        NSLog(@"Plugin loaded.");
    }

    return self;
}

// Sample Action, for menu item:
- (void)doMenuAction
{
    NSAlert *alert = [NSAlert alertWithMessageText:@"Hello, World" defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""];
    [alert runModal];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
