//
//  DVTSourceModelItem+SMQIdentification.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTSourceModelItem (SMQIdentification)

- (BOOL)smq_isComment;
- (BOOL)smq_isIdentifier;
- (BOOL)smq_isKeyword;
- (BOOL)smq_isMethod;
- (BOOL)smq_isPlain;
- (BOOL)smq_isPreprocessor;
- (BOOL)smq_isString;
- (BOOL)smq_isSystemClass;
- (BOOL)smq_isSystemFunction;
- (BOOL)smq_isUserClass;
- (BOOL)smq_isUserFunction;

@end
