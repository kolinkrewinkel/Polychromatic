//
//  DVTSourceModelItem+PLYIdentification.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTSourceModelItem+PLYIdentification.h"

@implementation DVTSourceModelItem (PLYIdentification)

- (BOOL)PLY_isComment
{
    return (self.nodeType == 1);
}

- (BOOL)PLY_isIdentifier
{
    //      Local Vars/Arguments     Ivars and Properties     Instances of Macros      Macro Definitions
    return (self.nodeType == 24) || (self.nodeType == 16) || (self.nodeType == 17) || (self.nodeType == 49);
}

- (BOOL)PLY_isKeyword
{
    return (self.nodeType == 7) || (self.nodeType == 33);
}

- (BOOL)PLY_isMethod
{
    return (self.nodeType == 42);
}

- (BOOL)PLY_isPlain
{
    return (self.nodeType == 0);
}

- (BOOL)PLY_isPreprocessor
{
    return (self.nodeType == 8) || (self.nodeType == 28);
}

- (BOOL)PLY_isString
{
    return (self.nodeType == 4);
}

- (BOOL)PLY_isSystemClass
{
    return (self.nodeType == 18);
}

- (BOOL)PLY_isSystemFunction
{
    return (self.nodeType == 19);
}

- (BOOL)PLY_isUserClass
{
    //      Class Definitions
    return (self.nodeType == 9) || (self.nodeType == 12);
}

- (BOOL)PLY_isUserFunction
{
    return (self.nodeType == 13);
}

@end
