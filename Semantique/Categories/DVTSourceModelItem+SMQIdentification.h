//
//  DVTSourceModelItem+SMQIdentification.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "OhNoMoreXcodeInterfaces.h"

@interface DVTSourceModelItem (SMQIdentification)

- (BOOL)smq_isString;
- (BOOL)smq_isIdentifier;

@end
