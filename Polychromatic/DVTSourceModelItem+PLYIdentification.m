//
//  DVTSourceModelItem+PLYIdentification.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTSourceModelItem+PLYIdentification.h"

@implementation DVTSourceModelItem (PLYIdentification)

- (BOOL)ply_isComment
{
    return (self.nodeType == 1);
}

- (BOOL)ply_isIdentifier
{
    //      Local Vars/Arguments     Ivars and Properties     Instances of Macros      Macro Definitions
    return (self.nodeType == 24) || (self.nodeType == 16) || (self.nodeType == 17) || (self.nodeType == 49);
}

- (BOOL)ply_isKeyword
{
    return (self.nodeType == 7) || (self.nodeType == 33);
}

- (BOOL)ply_isMethod
{
    return (self.nodeType == 42);
}

- (BOOL)ply_isPlain
{
    return (self.nodeType == 0);
}

- (BOOL)ply_isPreprocessor
{
    return (self.nodeType == 8) || (self.nodeType == 28);
}

- (BOOL)ply_isString
{
    return (self.nodeType == 4);
}

- (BOOL)ply_isSystemClass
{
    return (self.nodeType == 18);
}

- (BOOL)ply_isSystemFunction
{
    return (self.nodeType == 19);
}

- (BOOL)ply_isUserClass
{
    //      Class Definitions
    return (self.nodeType == 9) || (self.nodeType == 12);
}

- (BOOL)ply_isUserFunction
{
    return (self.nodeType == 13);
}

@end
