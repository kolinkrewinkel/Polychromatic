//
//  DVTSourceModelItem+PLYIdentification.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTSourceModelItem (PLYIdentification)

- (BOOL)PLY_isComment;
- (BOOL)PLY_isIdentifier;
- (BOOL)PLY_isKeyword;
- (BOOL)PLY_isMethod;
- (BOOL)PLY_isPlain;
- (BOOL)PLY_isPreprocessor;
- (BOOL)PLY_isString;
- (BOOL)PLY_isSystemClass;
- (BOOL)PLY_isSystemFunction;
- (BOOL)PLY_isUserClass;
- (BOOL)PLY_isUserFunction;

@end
