//
//  SMQSwizzling.c
//  Semantique
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "SMQSwizzling.h"

void SMQPoseSwizzle(Class originalClass, SEL originalSelector, Class posingClass, SEL replacementSelector)
{
    Method origMethod = class_getInstanceMethod(originalClass, originalSelector);
    Method newMethod = class_getInstanceMethod(posingClass, replacementSelector);

    if (class_addMethod(originalClass, originalSelector, method_getImplementation(newMethod), method_getTypeEncoding(newMethod)))
    {
        class_replaceMethod(originalClass, replacementSelector, method_getImplementation(origMethod), method_getTypeEncoding(origMethod));
    }
    else
    {
        method_exchangeImplementations(origMethod, newMethod);
    }
}
