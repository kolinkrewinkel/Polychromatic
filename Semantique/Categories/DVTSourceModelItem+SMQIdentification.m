//
//  DVTSourceModelItem+SMQIdentification.m
//  Semantique
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTSourceModelItem+SMQIdentification.h"

@implementation DVTSourceModelItem (SMQIdentification)

- (BOOL)smq_isString
{
    return self.nodeType == 4;
}

@end
