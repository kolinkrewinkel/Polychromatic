//
//  PLYSwizzling.c
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "PLYSwizzling.h"

IMP PLYPoseSwizzle(Class originalClass, SEL originalSelector, Class posingClass, SEL replacementSelector, BOOL instanceMethod)
{
    Method origMethod;
    Method newMethod;

    if (instanceMethod)
    {
        origMethod = class_getInstanceMethod(originalClass, originalSelector);
        newMethod = class_getInstanceMethod(posingClass, replacementSelector);
    }
    else
    {
        origMethod = class_getClassMethod(originalClass, originalSelector);
        newMethod = class_getClassMethod(posingClass, replacementSelector);

        originalClass = object_getClass((id)originalClass);
        posingClass = object_getClass((id)posingClass);
    }

    IMP originalImp = method_getImplementation(origMethod);

    if (class_addMethod(originalClass, originalSelector, method_getImplementation(newMethod), method_getTypeEncoding(newMethod)))
    {
        return class_replaceMethod(originalClass, replacementSelector, method_getImplementation(origMethod), method_getTypeEncoding(origMethod));
    }
    else
    {
        method_exchangeImplementations(origMethod, newMethod);
    }

    return originalImp;
}
