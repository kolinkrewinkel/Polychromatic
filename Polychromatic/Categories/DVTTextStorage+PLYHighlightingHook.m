//
//  DVTTextStorage+PLYHighlightingHook.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2015 Kolin Krewinkel. All rights reserved.
//

#import "DVTTextStorage+PLYHighlightingHook.h"

#import "PolychromaticPlugin.h"
#import "PLYSwizzling.h"
#import "PLYVariableManager.h"
#import "DVTSourceModelItem+PLYIdentification.h"

static IMP originalColorAtIndexImp;

@implementation DVTTextStorage (PLYHighlightingHook)

#pragma mark - NSObject

+ (void)load
{
    originalColorAtIndexImp = PLYSwizzle([DVTTextStorage class],
                                         @selector(colorAtCharacterIndex:effectiveRange:context:),
                                         self,
                                         @selector(ply_colorAtCharacterIndex:effectiveRange:context:),
                                         YES);
}

#pragma mark - Color overriding

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index
                        effectiveRange:(NSRangePointer)effectiveRange
                               context:(NSDictionary *)context
{
    // Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward.
    // Once given a range, its broken down by the colorAt: method. It then operates on the remainder of the range,
    // effectively iterating from beginning to end using the effectiveRange of the next token and narrowing it down.
    NSColor *originalColor = originalColorAtIndexImp(self,
                                                     @selector(colorAtCharacterIndex:effectiveRange:context:),
                                                     index,
                                                     effectiveRange,
                                                     context);
    
    if (![[PolychromaticPlugin sharedPlugin] pluginEnabled]) {
        return originalColor;
    }

    NSRange newRange = *effectiveRange;

    if ([self ply_isSwiftDocument]) {
        return [self ply_colorForSwiftCodeRange:newRange context:context fallbackColor:originalColor];
    }
    
    return [self ply_colorForObjCCodeRange:newRange context:context fallbackColor:originalColor];
}

#pragma mark - Swift

- (BOOL)ply_isSwiftDocument
{
    // Check that the Swift language service class exists in the first place.
    static Class swiftLanguageServiceClass = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        swiftLanguageServiceClass = NSClassFromString(@"IDESourceLanguageServiceSwift");
    });

    // Check that the language service in use is the Swift one.
    return swiftLanguageServiceClass != nil && [self.languageService isKindOfClass:swiftLanguageServiceClass];
}

- (NSColor *)ply_colorForSwiftCodeRange:(NSRange)range context:(id)context fallbackColor:(NSColor *)fallbackColor
{
    NSRange swiftEffectiveRange;
    long long nodeType = [self nodeTypeAtCharacterIndex:range.location
                                         effectiveRange:&swiftEffectiveRange
                                                context:context];
    
    if (nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier.variable"]
        || nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier.constant"]
        || nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier"]) {
        PLYMockSwift *fauxSwiftService = (PLYMockSwift *)self.languageService;
        
        NSRange funcDefinitionRange = [fauxSwiftService methodDefinitionRangeAtIndex:range.location];
        if (funcDefinitionRange.location == NSIntegerMax) {
            NSArray *nameRanges;
            NSString *name = [self symbolNameAtCharacterIndex:range.location nameRanges:&nameRanges];

            return [[PLYVariableManager sharedManager] colorForVariable:name];
        }
    }
    
    return fallbackColor;
}

#pragma mark - Objective-C/Generic Code

- (NSColor *)ply_colorForObjCCodeRange:(NSRange)range context:(id)context fallbackColor:(NSColor *)fallbackColor
{
    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:range.location];
    
    // It's possible for us to simply use the source model, but we want to express fine control based on the node.
    BOOL isIdentifier = [item ply_isIdentifier];
    if (!isIdentifier) {
        return fallbackColor;
    }
    
    BOOL parentIsMethod = [item.parent ply_isMethod];
    BOOL inheritsFromPropertyDeclaration = [item ply_inheritsFromNodeOfType:32];
    
    // This is relatively backwards: for some reason, explicitly defined setters and getters in @property are *not*
    // considered methods/children of methods, whereas the property names themselves are. To combat this, the
    // following two obscure BOOLs are used to disable the getters/setters and enable the coloring of the property
    // var names.
    
    // Disallows getter/setter-attributes from being colored, as their parents are not methods but they inherit from
    // property declarations.
    BOOL parentIsNotMethodAndDoesNotInheritFromPropertyDeclaration = !parentIsMethod && !inheritsFromPropertyDeclaration;
    
    // Ensures property var names are colored as they are considered methods and are within property declarations.
    BOOL parentIsMethodAndInheritsFromPropertyDeclaration = (parentIsMethod && inheritsFromPropertyDeclaration);
    
    if (parentIsNotMethodAndDoesNotInheritFromPropertyDeclaration || parentIsMethodAndInheritsFromPropertyDeclaration) {
        NSString *string = [self.sourceModelService stringForItem:item];
        
        if (string) {
            return [[PLYVariableManager sharedManager] colorForVariable:string];
        }
    }
    
    return fallbackColor;
}

@end
