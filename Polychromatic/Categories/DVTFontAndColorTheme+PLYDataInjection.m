//
//  DVTFontAndColorTheme+PLYDataInjection.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTFontAndColorTheme+PLYDataInjection.h"
#import "PLYSwizzling.h"

static IMP originalDataRepImp;
static IMP originalDataLoadImp;

@implementation DVTFontAndColorTheme (PLYDataInjection)

+ (void)load
{
    originalDataRepImp = PLYPoseSwizzle(self, @selector(dataRepresentationWithError:), self, @selector(PLY_dataRepresentationWithError:), YES);
    originalDataLoadImp = PLYPoseSwizzle(self, @selector(_loadFontsAndColors), self, @selector(PLY_loadFontsAndColors), YES);
}

- (BOOL)PLY_loadFontsAndColors
{
    BOOL result = (BOOL)originalDataLoadImp(self, @selector(_loadFontsAndColors));

    // Unfortunately, this has to be loaded twice.
    NSData *data = nil;

    if (self.isBuiltIn)
    {
        data = [NSData dataWithContentsOfFile:[[self valueForKey:@"_dataURL"] absoluteString]];
    }
    else
    {
        data = [NSData dataWithContentsOfFile:[NSString stringWithFormat:@"%@/Library/Developer/Xcode/UserData/FontAndColorThemes/%@", NSHomeDirectory(), self.name]];
    }

    if (data)
    {
        NSPropertyListFormat format = 0;
        NSError *error = nil;
        NSMutableDictionary *dict = [NSPropertyListSerialization propertyListWithData:data options:NSPropertyListMutableContainersAndLeaves format:&format error:&error];

        [self PLY_setBrightness:[dict[@"PLYVarBrightness"] floatValue]];
        [self PLY_setSaturation:[dict[@"PLYVarSaturation"] floatValue]];
    }

    return result;
}

- (id)PLY_dataRepresentationWithError:(NSError **)arg1
{
    NSData *data = originalDataRepImp(self, @selector(dataRepresentationWithError:), arg1);

    if (data)
    {
        NSPropertyListFormat format = 0;
        NSString *error = nil;

        NSMutableDictionary *dict = [NSPropertyListSerialization propertyListWithData:data options:NSPropertyListMutableContainersAndLeaves format:&format error:arg1];

        CGFloat saturation = [self PLY_saturation];
        CGFloat brightness = [self PLY_brightness];

        if (saturation == 0.f)
        {
            saturation = 0.5f;
        }

        if (brightness == 0.f)
        {
            brightness = 0.5f;
        }

        dict[@"PLYVarSaturation"] = @(saturation);
        dict[@"PLYVarBrightness"] = @(brightness);

        data = [NSPropertyListSerialization dataFromPropertyList:dict format:format errorDescription:&error];
    }

    return data;
}

- (void)PLY_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, "PLY_saturation", @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)PLY_saturation
{
    return [objc_getAssociatedObject(self, "PLY_saturation") floatValue];
}

- (void)PLY_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, "PLY_brightness", @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)PLY_brightness
{
    return [objc_getAssociatedObject(self, "PLY_brightness") floatValue];
}

@end
