//
//  OhNoMoreXcodeInterfaces.h
//  BBUCodingInColorPlugin
//
//  Created by Boris Bügling on 02.02.14.
//  Copyright (c) 2014 Boris Bügling. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface DVTSourceModelItem : NSObject

@property NSArray* children;
@property short nodeType;
@property NSRange range;

-(BOOL)isIdentifier;

@end

#pragma mark -

@interface DVTSourceModel : NSObject

@property DVTSourceModelItem* sourceItems;

@end

#pragma mark -

@interface DVTSourceTextView : NSTextView

-(void)_commonInitDVTSourceTextView;

@end

#pragma mark -

@interface DVTTextStorage : NSTextStorage

@property DVTSourceModel* sourceModel;

-(NSColor*)colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
-(void)fixSyntaxColoringInRange:(NSRange)range;
-(short)nodeTypeAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
// FIXME: Workaround for NSObject+YOLO buggyness
-(NSColor*)yl_colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;

@end
