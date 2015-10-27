//
//  DVTFontAndColorTheme+PLYDataInjection.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTFontAndColorTheme+PLYDataInjection.h"
#import "PLYSwizzling.h"

static IMP originalDataRepImp = nil;
static IMP originalDataLoadImp = nil;

static NSString *kPlistBrightnessKey = @"PLYVarBrightness";
static NSString *kPlistSaturationKey = @"PLYVarSaturation";

static char *kAssociatedObjectBrightnessKey = "PLYVarBrightness";
static char *kAssociatedObjectSaturationKey = "PLYVarSaturation";

static NSString *kThemePath = @"Library/Developer/Xcode/UserData/FontAndColorThemes";

@implementation DVTFontAndColorTheme (PLYDataInjection)

+ (void)load
{
    originalDataRepImp = PLYPoseSwizzle(self,
                                        @selector(dataRepresentationWithError:),
                                        self,
                                        @selector(ply_dataRepresentationWithError:),
                                        YES);

    originalDataLoadImp = PLYPoseSwizzle(self,
                                         @selector(_loadFontsAndColors),
                                         self,
                                         @selector(ply_loadFontsAndColors),
                                         YES);
}

- (BOOL)ply_loadFontsAndColors
{
    BOOL result = (BOOL)originalDataLoadImp(self, @selector(_loadFontsAndColors));

    // Unfortunately, this has to be loaded twice.
    NSData *data = nil;

    if (self.isBuiltIn) {
        data = [NSData dataWithContentsOfFile:[[self valueForKey:@"_dataURL"] absoluteString]];
    } else {
        NSString *themePath = [NSString stringWithFormat:@"%@/%@/%@", NSHomeDirectory(), kThemePath, self.name];
        data = [NSData dataWithContentsOfFile:themePath];
    }

    if (data) {
        NSPropertyListFormat format = 0;
        NSDictionary *dict = [NSPropertyListSerialization propertyListWithData:data
                                                                       options:NSPropertyListImmutable
                                                                        format:&format
                                                                         error:nil];

        [self ply_setBrightness:[dict[kPlistBrightnessKey] floatValue]];
        [self ply_setSaturation:[dict[kPlistSaturationKey] floatValue]];
    }

    return result;
}

- (id)ply_dataRepresentationWithError:(NSError **)arg1
{
    NSData *data = originalDataRepImp(self, @selector(dataRepresentationWithError:), arg1);

    if (data) {
        NSPropertyListFormat format = 0;
        NSMutableDictionary *dict = [NSPropertyListSerialization propertyListWithData:data
                                                                              options:NSPropertyListMutableContainersAndLeaves
                                                                               format:&format
                                                                                error:arg1];

        CGFloat saturation = [self ply_saturation];
        CGFloat brightness = [self ply_brightness];

        if (saturation == 0.f) {
            saturation = 0.5f;
        }

        if (brightness == 0.f) {
            brightness = 0.5f;
        }

        dict[kPlistSaturationKey] = @(saturation);
        dict[kPlistBrightnessKey] = @(brightness);

        data = [NSPropertyListSerialization dataFromPropertyList:dict format:format errorDescription:nil];
    }

    return data;
}

- (void)ply_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, kAssociatedObjectSaturationKey, @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)ply_saturation
{
    return [objc_getAssociatedObject(self, kAssociatedObjectSaturationKey) floatValue];
}

- (void)ply_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, kAssociatedObjectBrightnessKey, @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)ply_brightness
{
    return [objc_getAssociatedObject(self, kAssociatedObjectBrightnessKey) floatValue];
}

@end
