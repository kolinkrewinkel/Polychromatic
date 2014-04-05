//
//  DVTFontAndColorTheme+SMQDataInjection.h
//  Semantique
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTFontAndColorTheme (SMQDataInjection)

- (void)smq_setSaturation:(CGFloat)saturation;
- (CGFloat)smq_saturation;

- (void)smq_setBrightness:(CGFloat)brightness;
- (CGFloat)smq_brightness;

@end
