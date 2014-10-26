//
//  NSString+FNVHash.h
//  Polychromatic
//
//  Created by Maximilian Christ on 02/09/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNVHash)

- (uint64_t)ply_FNV1Hash;

- (uint64_t)ply_FNV1aHash;

@end
