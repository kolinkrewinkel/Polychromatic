//
//  DVTSourceModelItem+PLYIdentification.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTSourceModelItem (PLYIdentification)

- (BOOL)ply_isComment;
- (BOOL)ply_isIdentifier;
- (BOOL)ply_isKeyword;
- (BOOL)ply_isMethod;
- (BOOL)ply_isPlain;
- (BOOL)ply_isPreprocessor;
- (BOOL)ply_isString;
- (BOOL)ply_isSystemClass;
- (BOOL)ply_isSystemFunction;
- (BOOL)ply_isUserClass;
- (BOOL)ply_isUserFunction;
- (BOOL)ply_inheritsFromNodeOfType:(short)nodeType;

@end
