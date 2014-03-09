//
//  SMQSwizzling.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import <objc/runtime.h>

void SMQPoseSwizzle(Class originalClass, SEL originalSelector, Class posingClass, SEL replacementSelector);

