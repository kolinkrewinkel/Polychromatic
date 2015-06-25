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

#pragma mark - Variable Management

- (NSColor *)colorForVariable:(NSString *)variable
{
    NSUInteger numberOfDifferentColors = 4096;
    NSUInteger shortHashValue = [self ply_FNV1aHash:variable] % numberOfDifferentColors;
    CGFloat hueValue = (CGFloat)shortHashValue/(CGFloat)numberOfDifferentColors;

    return [NSColor colorWithCalibratedHue:hueValue saturation:[[DVTFontAndColorTheme currentTheme] ply_saturation] brightness:[[DVTFontAndColorTheme currentTheme] ply_brightness] alpha:1.f];
}

- (uint64_t)ply_FNV1aHash:(NSString *)stringToHash
{
    // http://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    const uint8_t *bytes = (uint8_t *)stringToHash.UTF8String;
    uint64_t hash = 14695981039346656037ULL;
    for(uint8_t byte = *bytes; byte != '\0'; byte = *(++bytes))
    {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
     return hash;
}

@end