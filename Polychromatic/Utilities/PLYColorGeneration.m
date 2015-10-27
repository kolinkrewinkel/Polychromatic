//
//  PLYVariableManager.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2015 Kolin Krewinkel. All rights reserved.
//

#import <CommonCrypto/CommonDigest.h>

#import "DVTFontAndColorTheme+PLYDataInjection.h"
#import "DVTInterfaces.h"

#import "PLYColorGeneration.h"

static uint64_t FNV1aHash(NSString *stringToHash)
{
    // http://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    const uint8_t *bytes = (uint8_t *)stringToHash.UTF8String;
    uint64_t hash = 14695981039346656037ULL;
    for (uint8_t byte = *bytes; byte != '\0'; byte = *(++bytes)) {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    
    return hash;
}

NSColor *PLYGenerateColor(NSString *identifier)
{
    NSUInteger numberOfDifferentColors = 4096;
    NSUInteger shortHashValue = FNV1aHash(identifier) % numberOfDifferentColors;
    CGFloat hueValue = (CGFloat)shortHashValue/(CGFloat)numberOfDifferentColors;
    
    return [NSColor colorWithCalibratedHue:hueValue
                                saturation:[[DVTFontAndColorTheme currentTheme] ply_saturation]
                                brightness:[[DVTFontAndColorTheme currentTheme] ply_brightness]
                                     alpha:1.f];
}
