//
//  PLYSwizzling.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <objc/runtime.h>

IMP PLYPoseSwizzle(Class originalClass, SEL originalSelector, Class posingClass, SEL replacementSelector, BOOL instanceMethod);

