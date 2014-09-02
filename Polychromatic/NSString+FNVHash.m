//
//  NSString+FNVHash.m
//  Polychromatic
//
//  Created by Maximilian Christ on 02/09/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "NSString+FNVHash.h"

@implementation NSString (FNVHash)

- (uint64_t)ply_FNV1aHash
{
    // http://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    
    const uint8_t *bytes = (uint8_t *)self.UTF8String;
    
    uint64_t hash = 14695981039346656037ULL;
    for(uint8_t byte = *bytes; byte != '\0'; byte = *(++bytes))
    {
        hash ^= byte;
        hash *= 1099511628211ULL;
    }
    
    return hash;
}

@end
