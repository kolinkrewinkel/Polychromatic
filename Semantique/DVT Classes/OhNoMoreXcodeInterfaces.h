//
//  OhNoMoreXcodeInterfaces.h
//  BBUCodingInColorPlugin
//
//  Created by Boris Bügling on 02.02.14.
//  Copyright (c) 2014 Boris Bügling. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface DVTSourceNodeTypes : NSObject
{
}

+ (BOOL)nodeType:(short)arg1 conformsToNodeTypeNamed:(id)arg2;
+ (long long)nodeTypesCount;
+ (id)nodeTypeNameForId:(short)arg1;
+ (short)registerNodeTypeNamed:(id)arg1;
+ (void)initialize;

@end

@interface DVTSourceCodeSymbolKind : NSObject <NSCopying>
{
    NSString *_identifier;
    NSString *_localizedDescription;
    NSArray *_conformedToSymbolKindIdentifiers;
    NSArray *_conformedToSymbolKinds;
    NSArray *_allConformingSymbolKinds;
    BOOL _navigationPrefersDefinition;
}

+ (id)sourceCodeSymbolKinds;
+ (id)sourceCodeSymbolKindForIdentifier:(id)arg1;
+ (id)_sourceCodeSymbolKindForExtension:(id)arg1;
+ (void)initialize;
+ (id)classMethodTemplateSymbolKind;
+ (id)instanceMethodTemplateSymbolKind;
+ (id)functionTemplateSymbolKind;
+ (id)classTemplateSymbolKind;
+ (id)namespaceSymbolKind;
+ (id)ibOutletCollectionPropertySymbolKind;
+ (id)ibOutletCollectionVariableSymbolKind;
+ (id)ibOutletCollectionSymbolKind;
+ (id)ibOutletPropertySymbolKind;
+ (id)ibOutletVariableSymbolKind;
+ (id)ibOutletSymbolKind;
+ (id)ibActionMethodSymbolKind;
+ (id)testMethodSymbolKind;
+ (id)globalVariableSymbolKind;
+ (id)localVariableSymbolKind;
+ (id)unionSymbolKind;
+ (id)typedefSymbolKind;
+ (id)structSymbolKind;
+ (id)protocolSymbolKind;
+ (id)propertySymbolKind;
+ (id)parameterSymbolKind;
+ (id)macroSymbolKind;
+ (id)classVariableSymbolKind;
+ (id)instanceVariableSymbolKind;
+ (id)instanceMethodSymbolKind;
+ (id)functionSymbolKind;
+ (id)fieldSymbolKind;
+ (id)enumConstantSymbolKind;
+ (id)enumSymbolKind;
+ (id)classSymbolKind;
+ (id)classMethodSymbolKind;
+ (id)categorySymbolKind;
+ (id)builtinTypeSymbolKind;
+ (id)memberContainerSymbolKind;
+ (id)memberSymbolKind;
+ (id)callableSymbolKind;
+ (id)globalSymbolKind;
+ (id)containerSymbolKind;
@property(readonly) BOOL navigationPrefersDefinition; // @synthesize navigationPrefersDefinition=_navigationPrefersDefinition;
@property(readonly, copy) NSString *localizedDescription; // @synthesize localizedDescription=_localizedDescription;
@property(readonly, copy) NSString *identifier; // @synthesize identifier=_identifier;
- (BOOL)conformsToSymbolKind:(id)arg1;
@property(readonly, getter=isContainer) BOOL container;
@property(readonly, copy) NSArray *allConformingSymbolKinds;
@property(readonly, copy) NSArray *conformedToSymbolKinds;
- (id)copyWithZone:(struct _NSZone *)arg1;
- (id)description;
- (id)initWithSourceCodeSymbolKindExtension:(id)arg1;

@end

@interface DVTSourceModelItem : NSObject
{
    int _rc;
    struct _NSRange _relativeLocation;
    long long _langId;
    long long _token;
    DVTSourceModelItem *_parent;
    NSMutableArray *_children;
    unsigned int _nodeType:15;
    unsigned int _isOpaque:1;
    unsigned int _dirty:1;
    unsigned int _isBlock:1;
    unsigned int _ignoreToken:1;
    unsigned int _inheritsNodeType:1;
    unsigned int _isIdentifier:1;
    unsigned int _needsAdjustNodeType:1;
    unsigned int _isSimpleToken:1;
    unsigned int _isVolatile:1;
    unsigned int _needToDirtyRightEdges:1;
}

+ (id)sourceModelItemWithRange:(struct _NSRange)arg1 language:(long long)arg2 token:(long long)arg3 nodeType:(short)arg4;
@property struct _NSRange relativeLocation; // @synthesize relativeLocation=_relativeLocation;
@property(retain, nonatomic) NSMutableArray *children; // @synthesize children=_children;
@property(nonatomic) DVTSourceModelItem *parent; // @synthesize parent=_parent;
@property long long token; // @synthesize token=_token;
@property long long langId; // @synthesize langId=_langId;
- (void)enumerateIdentifierItemsInRelativeRange:(struct _NSRange)arg1 usingBlock:(id)arg2;
- (void)clearAdjustedNodeTypes;
- (long long)compare:(id)arg1;
- (id)followingItem;
- (id)precedingItem;
- (id)_lastLeafItem;
- (id)_firstLeafItem;
- (id)nextItem;
- (id)previousItem;
- (BOOL)isAncestorOf:(id)arg1;
- (id)childAdjoiningLocation:(unsigned long long)arg1;
- (id)childEnclosingLocation:(unsigned long long)arg1;
- (id)_childEnclosingLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildAtLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildAfterLocation:(unsigned long long)arg1;
- (unsigned long long)indexOfChildBeforeLocation:(unsigned long long)arg1;
- (unsigned long long)numberOfChildren;
- (void)addChildrenFromArray:(id)arg1 inRange:(struct _NSRange)arg2;
- (void)addChildren:(id)arg1;
- (void)addChild:(id)arg1;
- (void)assignAllParents:(id)arg1;
- (void)assignParents:(id)arg1;
- (BOOL)isVolatile;
- (void)setVolatile:(BOOL)arg1;
@property BOOL needsAdjustNodeType;
- (BOOL)needToDirtyRightEdges;
- (void)setNeedToDirtyRightEdges:(BOOL)arg1;
- (BOOL)isSimpleToken;
- (void)setIsSimpleToken:(BOOL)arg1;
- (BOOL)inheritsNodeType;
- (void)setInheritsNodeType:(BOOL)arg1;
- (BOOL)ignoreToken;
- (void)setIgnoreToken:(BOOL)arg1;
- (BOOL)dirty;
- (void)setDirty:(BOOL)arg1;
- (BOOL)isIdentifier;
- (short)rawNodeType;
- (BOOL)isOpaque;
- (void)setIsOpaque:(BOOL)arg1;
- (short)nodeType;
- (void)setNodeType:(short)arg1;
- (struct _NSRange)innerRange;
- (void)offsetBy:(long long)arg1;
- (void)setRange:(struct _NSRange)arg1;
- (struct _NSRange)range;
- (id)enclosingBlock;
- (long long)blockDepth;
- (void)setIsBlock:(BOOL)arg1;
- (BOOL)isBlock;
- (void)dirtyRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (void)dirtyRelativeRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (void)validate;
- (id)dumpContext;
- (id)contextArray;
- (id)simpleDescription;
- (id)diffableDescription;
- (id)description;
- (id)innerDescription:(id)arg1 showSelf:(BOOL)arg2;
- (id)initWithRange:(struct _NSRange)arg1 language:(long long)arg2 token:(long long)arg3 nodeType:(short)arg4;
- (BOOL)_isDeallocating;
- (BOOL)_tryRetain;
- (unsigned long long)retainCount;
- (oneway void)release;
- (id)retain;

@end

#pragma mark -

@interface DVTSourceModel : NSObject
{
    struct _NSRange _dirtyRange;
    long long _batchDelta;
    DVTSourceModelItem *_sourceItems;
    BOOL _isDoingBatchEdit;
}

+ (id)editorResponsivenessPerformanceLogAspect;
+ (void)initialize;
@property BOOL isDoingBatchEdit; // @synthesize isDoingBatchEdit=_isDoingBatchEdit;
@property long long batchDelta; // @synthesize batchDelta=_batchDelta;
@property struct _NSRange dirtyRange; // @synthesize dirtyRange=_dirtyRange;
@property(retain) DVTSourceModelItem *sourceItems; // @synthesize sourceItems=_sourceItems;
- (id)objCMethodNameForItem:(id)arg1 nameRanges:(id *)arg2;
- (BOOL)isItemDictionaryLiteral:(id)arg1;
- (BOOL)isItemObjectLiteral:(id)arg1;
- (BOOL)isItemForStatement:(id)arg1;
- (BOOL)isItemSemanticBlock:(id)arg1;
- (BOOL)isItemBracketExpression:(id)arg1;
- (BOOL)isItemAngleExpression:(id)arg1;
- (BOOL)isItemParenExpression:(id)arg1;
- (BOOL)isPostfixExpressionAtLocation:(unsigned long long)arg1;
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
- (id)completionPlaceholderItemAtLocation:(unsigned long long)arg1;
- (id)identOrKeywordItemAtLocation:(unsigned long long)arg1;
- (id)objCDeclaratorItemAtLocation:(unsigned long long)arg1;
- (id)numberConstantAtLocation:(unsigned long long)arg1;
- (id)characterConstantAtLocation:(unsigned long long)arg1;
- (id)stringConstantAtLocation:(unsigned long long)arg1;
- (id)moduleImportStatementAtLocation:(unsigned long long)arg1;
- (id)includeStatementAtLocation:(unsigned long long)arg1;
- (id)preprocessorStatementAtLocation:(unsigned long long)arg1;
- (id)docCommentAtLocation:(unsigned long long)arg1;
- (id)commentAtLocation:(unsigned long long)arg1;
- (id)placeholderItemsFromItem:(id)arg1;
- (id)identifierItemsFromItem:(id)arg1;
- (id)commentBlockItems;
- (id)functionsAndMethodItems;
- (id)classItems;
- (void)addBlockItemsInTypeList:(long long *)arg1 fromItem:(id)arg2 toArray:(id)arg3;
- (void)addIdentifierItemsFromItem:(id)arg1 toArray:(id)arg2;
- (void)addItemsInTypeList:(long long *)arg1 fromItem:(id)arg2 toArray:(id)arg3;
- (id)functionOrMethodDefinitionAtLocation:(unsigned long long)arg1;
- (id)functionOrMethodAtLocation:(unsigned long long)arg1;
- (id)interfaceDeclarationAtLocation:(unsigned long long)arg1;
- (id)typeDeclarationAtLocation:(unsigned long long)arg1;
- (id)classAtLocation:(unsigned long long)arg1;
- (id)itemNameAtLocation:(unsigned long long)arg1 inTypeList:(long long *)arg2 nameRanges:(id *)arg3 scopeRange:(struct _NSRange *)arg4;
- (id)nameOfItem:(id)arg1 nameRanges:(id *)arg2 scopeRange:(struct _NSRange *)arg3;
- (void)enumerateIdentifierItemsInRange:(struct _NSRange)arg1 usingBlock:(id)arg2;
- (id)itemAtLocation:(unsigned long long)arg1 ofType:(id)arg2;
- (id)itemAtLocation:(unsigned long long)arg1 inTypeList:(long long *)arg2;
- (long long *)typeListForSpecNames:(id)arg1;
- (id)builtUpNameForItem:(id)arg1 nameRanges:(id *)arg2;
- (id)_builtUpNameForItem:(id)arg1 mutableNameRanges:(id)arg2;
- (id)_builtUpNameForSubTree:(id)arg1 mutableNameRanges:(id)arg2;
- (id)objectLiteralItemAtLocation:(unsigned long long)arg1;
- (id)parenItemAtLocation:(unsigned long long)arg1;
- (id)parenLikeItemAtLocation:(unsigned long long)arg1;
- (id)foldableBlockItemForLocation:(unsigned long long)arg1;
- (id)foldableBlockItemForLineAtLocation:(unsigned long long)arg1;
- (id)blockItemAtLocation:(unsigned long long)arg1;
- (long long)indentForItem:(id)arg1;
- (id)adjoiningItemAtLocation:(unsigned long long)arg1;
- (id)enclosingItemAtLocation:(unsigned long long)arg1;
- (id)_topLevelSourceItem;
- (void)parse;
- (void)doingBatchEdit:(BOOL)arg1;
- (void)dirtyRange:(struct _NSRange)arg1 changeInLength:(long long)arg2;
- (id)initWithSourceBufferProvider:(id)arg1;

@end

#pragma mark -

@interface DVTSourceTextView : NSTextView

-(void)_commonInitDVTSourceTextView;

@end

#pragma mark -

@protocol DVTSourceLanguageSourceModelService <NSObject>
- (struct _NSRange)rangeForBlockContainingRange:(struct _NSRange)arg1;
- (NSString *)stringForItem:(DVTSourceModelItem *)arg1;
- (DVTSourceModelItem *)commonSourceModelItemAtRange:(struct _NSRange)arg1;
- (DVTSourceModelItem *)sourceModelItemAtCharacterIndex:(unsigned long long)arg1;
- (DVTSourceModelItem *)sourceModelItemAtCharacterIndex:(unsigned long long)arg1 affinity:(unsigned long long)arg2;
- (DVTSourceModel *)sourceModelWithoutParsing;
- (DVTSourceModel *)sourceModel;
@end

@interface DVTTextStorage : NSTextStorage

@property DVTSourceModel* sourceModel;
@property(readonly) id sourceModelService; // DVTSourceTextStorage

@property(readonly) unsigned long long currentChangeIndex;

-(NSColor*)colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
-(void)fixSyntaxColoringInRange:(NSRange)range;
-(short)nodeTypeAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
// FIXME: Workaround for NSObject+YOLO buggyness
-(NSColor*)yl_colorAtCharacterIndex:(unsigned long long)charIndex effectiveRange:(NSRangePointer)range context:(id)context;
- (id<DVTSourceLanguageSourceModelService>)sourceModelItemAtCharacterIndex:(unsigned long long)arg1; //DVTSourceTextStorage in Xcode 5, DVTSourceLanguageSourceModelService protocol in Xcode 5.1

@end

