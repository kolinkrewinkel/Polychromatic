//
//  DVTSourceModelItem+SMQIdentification.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTSourceModelItem+SMQIdentification.h"

@implementation DVTSourceModelItem (SMQIdentification)

- (BOOL)smq_isComment
{
    return (self.nodeType == 1);
}

- (BOOL)smq_isIdentifier
{
    //      Standard Variables       Instances of Macros      Macro Definitions
    return (self.nodeType == 24) || (self.nodeType == 17) || (self.nodeType == 49);
}

- (BOOL)smq_isKeyword
{
    return (self.nodeType == 7) || (self.nodeType == 33);
}

- (BOOL)smq_isMethod
{
    return (self.nodeType == 42);
}

- (BOOL)smq_isPlain
{
    return (self.nodeType == 0);
}

- (BOOL)smq_isPreprocessor
{
    return (self.nodeType == 8) || (self.nodeType == 28);
}

- (BOOL)smq_isString
{
    return (self.nodeType == 4);
}

- (BOOL)smq_isSystemClass
{
    return (self.nodeType == 18);
}

- (BOOL)smq_isSystemFunction
{
    return (self.nodeType == 19);
}

- (BOOL)smq_isUserClass
{
    //      Class Definitions
    return (self.nodeType == 9) || (self.nodeType == 12);
}

@end
