//
//  DVTFontAndColorTheme+SMQDataInjection.m
//  Semantique
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTFontAndColorTheme+SMQDataInjection.h"
#import "SMQSwizzling.h"

static IMP originalDataRepImp;
static IMP originalDataLoadImp;

@implementation DVTFontAndColorTheme (SMQDataInjection)

+ (void)load
{
    originalDataRepImp = SMQPoseSwizzle(self, @selector(dataRepresentationWithError:), self, @selector(smq_dataRepresentationWithError:), YES);
    originalDataLoadImp = SMQPoseSwizzle(self, @selector(_loadFontsAndColors), self, @selector(smq_loadFontsAndColors), YES);
}

- (BOOL)smq_loadFontsAndColors
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

        [self smq_setBrightness:[dict[@"SMQVarBrightness"] floatValue]];
        [self smq_setSaturation:[dict[@"SMQVarSaturation"] floatValue]];
    }

    return result;
}

- (id)smq_dataRepresentationWithError:(NSError **)arg1
{
    NSData *data = originalDataRepImp(self, @selector(dataRepresentationWithError:), arg1);

    if (data)
    {
        NSPropertyListFormat format = 0;
        NSString *error = nil;

        NSMutableDictionary *dict = [NSPropertyListSerialization propertyListWithData:data options:NSPropertyListMutableContainersAndLeaves format:&format error:arg1];

        CGFloat saturation = [self smq_saturation];
        CGFloat brightness = [self smq_brightness];

        if (saturation == 0.f)
        {
            saturation = 0.5f;
        }

        if (brightness == 0.f)
        {
            brightness = 0.5f;
        }

        dict[@"SMQVarSaturation"] = @(saturation);
        dict[@"SMQVarBrightness"] = @(brightness);

        data = [NSPropertyListSerialization dataFromPropertyList:dict format:format errorDescription:&error];
    }

    return data;
}

- (void)smq_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, "smq_saturation", @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)smq_saturation
{
    return [objc_getAssociatedObject(self, "smq_saturation") floatValue];
}

- (void)smq_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, "smq_brightness", @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (CGFloat)smq_brightness
{
    return [objc_getAssociatedObject(self, "smq_brightness") floatValue];
}

@end
