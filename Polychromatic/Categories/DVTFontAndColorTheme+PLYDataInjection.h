//
//  DVTFontAndColorTheme+PLYDataInjection.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTFontAndColorTheme (PLYDataInjection)

- (void)ply_setEnabled:(BOOL)enabled;
- (BOOL)ply_enabled;

- (void)ply_setSaturation:(CGFloat)saturation;
- (CGFloat)ply_saturation;

- (void)ply_setBrightness:(CGFloat)brightness;
- (CGFloat)ply_brightness;

@end
