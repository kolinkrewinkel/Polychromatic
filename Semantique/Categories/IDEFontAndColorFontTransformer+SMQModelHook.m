//
//  IDEFontAndColorFontTransformer+SMQModelHook.m
//  Semantique
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEFontAndColorFontTransformer+SMQModelHook.h"
#import "SMQSwizzling.h"

static IMP originalValueTransformImp;
static IMP originalReverseValueTransformImp;

@implementation IDEFontAndColorFontTransformer (SMQModelHook)

#pragma mark - Swizzling

//+ (void)load
//{
//    originalValueTransformImp = SMQPoseSwizzle(self, @selector(transformedValue:), self, @selector(smq_transformedValue:), YES);
//    originalReverseValueTransformImp = SMQPoseSwizzle(self, @selector(reverseTransformedValue:), self, @selector(smq_reverseTransformedValue:), YES);
//}

#pragma mark - Replacement Methods

- (id)smq_transformedValue:(id)value1
{
    NSLog(@"Transform: %@", [value1 class]);

    return originalValueTransformImp(self, @selector(transformedValue:), value1);
}

- (id)smq_reverseTransformedValue:(id)value1
{
    NSLog(@"Reverse: %@", [value1 class]);

    return originalReverseValueTransformImp(self, @selector(smq_reverseTransformedValue:), value1);
}


@end
