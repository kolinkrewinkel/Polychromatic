//
//  DVTTextStorage+PLYHighlightingHook.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTTextStorage (PLYHighlightingHook)

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(id)context;

@end

@interface PLYMockSwift : NSObject

+ (BOOL)canGenerateContentsForURL:(id)arg1;

- (BOOL)shouldAutoCompleteAtLocation:(unsigned long long)arg1 autoCompleteCharacterSet:(id)arg2 proposedAutoComplete:(BOOL)arg3;
- (void)findIndexSymbolAtLocation:(id)arg1 completionBlock:(id)arg2;
- (void)quickHelpDataContextForLocation:(id)arg1 completionBlock:(id)arg2;
- (long long)commentCoverageInLineRange:(struct _NSRange)arg1;
- (id)indentLineRange:(struct _NSRange)arg1 effectiveLineRange:(struct _NSRange *)arg2;
- (struct _NSRange)methodOrFunctionRangeAtIndex:(unsigned long long)arg1;
- (id)landmarkItemTypeNameForReference:(void *)arg1;
- (id)landmarkItemNameForReference:(void *)arg1 nameRange:(struct _NSRange *)arg2;
- (void)generateLandmarkItemsForParent:(id)arg1 matchingType:(id)arg2 altParent:(void)arg3 matchingAltType:(id)arg4;
- (struct _NSRange)textCompletionSession:(id)arg1 replacementRangeForSuggestedRange:(struct _NSRange)arg2;
- (id)scopeLanguageSpecificationIdentifiersAtLocation:(unsigned long long)arg1;
- (id)functionAndMethodRanges;
- (id)commentBlockRanges;
- (BOOL)isInTokenizableCodeAtLocation:(unsigned long long)arg1;
- (BOOL)isInPlainCodeAtLocation:(unsigned long long)arg1;
- (BOOL)isInKeywordAtLocation:(unsigned long long)arg1;
- (BOOL)isIncompletionPlaceholderAtLocation:(unsigned long long)arg1;
- (BOOL)isInNumberConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInCharacterConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInIdentifierAtLocation:(unsigned long long)arg1;
- (BOOL)isInStringConstantAtLocation:(unsigned long long)arg1;
- (BOOL)isInIncludeStatementAtLocation:(unsigned long long)arg1;
- (BOOL)isInPreprocessorStatementAtLocation:(unsigned long long)arg1;
- (BOOL)isInDocCommentAtLocation:(unsigned long long)arg1;
- (BOOL)isInCommentAtLocation:(unsigned long long)arg1;
- (long long)foldableBlockDepthForLineAtLocation:(unsigned long long)arg1;
- (struct _NSRange)foldableBlockInnerRangeForLineAtLocation:(unsigned long long)arg1;
- (struct _NSRange)foldableBlockRangeForLineAtLocation:(unsigned long long)arg1;
- (id)foldableBlockInnerRangesInRange:(struct _NSRange)arg1;
- (id)foldableBlockRangesAtLocation:(unsigned long long)arg1;
- (struct _NSRange)foldableBlockRangeAtLocation:(unsigned long long)arg1;
- (unsigned long long)indentOfBlockAtLocation:(unsigned long long)arg1;
- (struct _NSRange)functionRangeAtIndex:(unsigned long long)arg1 isDefinitionOrCall:(char *)arg2;
- (struct _NSRange)methodDefinitionRangeAtIndex:(unsigned long long)arg1;
- (struct _NSRange)rangeOfWordAtIndex:(unsigned long long)arg1 allowNonWords:(BOOL)arg2;
- (void)tokenizableRangesWithRange:(struct _NSRange)arg1 completionBlock:(id)arg2;
- (BOOL)shouldShowTemporaryLinkForCharacterAtIndex:(unsigned long long)arg1 proposedRange:(struct _NSRange)arg2 effectiveRanges:(id *)arg3;
- (id)symbolNameAtCharacterIndex:(unsigned long long)arg1 nameRanges:(id *)arg2;
- (struct _NSRange)_functionCallOrDeclarationBaseName:(const struct SwiftSyntaxStructure *)arg1;
- (struct _NSRange)characterRangeForUSR:(id)arg1;
- (long long)syntaxTypeAtCharacterIndex:(unsigned long long)arg1 effectiveRange:(struct _NSRange *)arg2 context:(id)arg3;
- (long long)_swiftSyntaxTypeAtCharacterIndex:(unsigned long long)arg1 effectiveRange:(struct _NSRange *)arg2;
- (void)_applySemanticAnnotation:(long long)arg1 byteLength:(long long)arg2 kind:(struct sourcekitd_uid_s *)arg3 isSystem:(_Bool)arg4 affectedRange:(struct _NSRange *)arg5;
- (void)_readSemanticAnnotationTokens:(struct CDStruct_3b0d17db)arg1 affectedRange:(NSRange *)arg2;
- (void)_readDiagnostics:(struct CDStruct_3b0d17db)arg1;
- (void)_mergeSyntaxAndSemaMap:(struct CDStruct_3b0d17db)arg1 affectedRange:(struct _NSRange *)arg2;
- (void)_closeDocument;
- (void)_openDocument;
- (BOOL)hasSourceKitBuffer;
- (void)replaceCharactersInRange:(struct _NSRange)arg1 withString:(id)arg2 replacedString:(id)arg3 affectedRange:(struct _NSRange *)arg4;
- (void)updateLineRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (void)contextDidChange:(id)arg1;
- (void)primitiveInvalidate;
- (void)_applyChangesFromSourceLanguageServiceContext:(id)arg1;
- (id)initWithLanguage:(id)arg1 delegate:(id)arg2;
- (id)generatedContentCounterpartURL;

@end