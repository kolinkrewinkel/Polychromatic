//
//  DVTFontAndColorTheme+PLYDataInjection.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTFontAndColorTheme (PLYDataInjection)

- (void)PLY_setSaturation:(CGFloat)saturation;
- (CGFloat)PLY_saturation;

- (void)PLY_setBrightness:(CGFloat)brightness;
- (CGFloat)PLY_brightness;

@end
