//
//  DVTInterfaces.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/30/14.
//  Copyright 2014 Apple Inc. All rights reserved.
//
//  Sourced from class-dump. Some borrowed from CodePilot for quick compilation.
//

#import <Cocoa/Cocoa.h>

@interface DVTSourceCodeSymbolKind : NSObject
+ (id)containerSymbolKind;
+ (id)globalSymbolKind;
+ (id)callableSymbolKind;
+ (id)memberSymbolKind;
+ (id)memberContainerSymbolKind;
+ (id)categorySymbolKind;
+ (id)classMethodSymbolKind;
+ (id)classSymbolKind;
+ (id)enumSymbolKind;
+ (id)enumConstantSymbolKind;
+ (id)fieldSymbolKind;
+ (id)functionSymbolKind;
+ (id)instanceMethodSymbolKind;
+ (id)instanceVariableSymbolKind;
+ (id)classVariableSymbolKind;
+ (id)macroSymbolKind;
+ (id)parameterSymbolKind;
+ (id)propertySymbolKind;
+ (id)protocolSymbolKind;
+ (id)structSymbolKind;
+ (id)typedefSymbolKind;
+ (id)unionSymbolKind;
+ (id)localVariableSymbolKind;
+ (id)globalVariableSymbolKind;
+ (id)ibActionMethodSymbolKind;
+ (id)ibOutletSymbolKind;
+ (id)ibOutletVariableSymbolKind;
+ (id)ibOutletPropertySymbolKind;
+ (id)ibOutletCollectionSymbolKind;
+ (id)ibOutletCollectionVariableSymbolKind;
+ (id)ibOutletCollectionPropertySymbolKind;
+ (id)namespaceSymbolKind;
+ (id)classTemplateSymbolKind;
+ (id)functionTemplateSymbolKind;
+ (id)instanceMethodTemplateSymbolKind;
+ (id)classMethodTemplateSymbolKind;
+ (void)initialize;
+ (id)sourceCodeSymbolKinds;
- (id)icon;
- (id)description;
- (id)conformedToSymbolKinds;
- (id)allConformingSymbolKinds;
- (char)isContainer;
- (id)identifier;
- (id)localizedDescription;
@end

@interface IDEDocumentController : NSObject
+ (id)sharedDocumentController;
- (NSArray *)workspaceDocuments;
@end

@class DVTDocumentLocation, DVTFileDataType;
@interface DVTFilePath : NSObject
- (NSURL *)fileURL;
- (NSString *)pathString;
- (NSString *)fileName;
+ (DVTFilePath *)filePathForPathString:(NSString *)path;
- (DVTFilePath *)file;
- (NSImage *)navigableItem_image;

- (DVTDocumentLocation *)navigableItem_contentDocumentLocation;
- (DVTFileDataType *)navigableItem_documentType;
- (DVTFilePath *)parentFilePath;
- (DVTFilePath *)volumeFilePath;
@end

@interface IDEIndex : NSObject
{
}

+ (BOOL)languageSupportsSymbolColoring:(id)arg1;
+ (id)resolutionForName:(id)arg1 kind:(id)arg2 containerName:(id)arg3;
+ (id)pathToClang;
+ (id)_dataSourceExtensionForFile:(id)arg1 withLanguage:(id)arg2;
+ (void)syncPerformBlockOnMainThread:(dispatch_block_t)arg1;
+ (void)initialize;
+ (BOOL)includeAutoImportResults;
+ (BOOL)indexFollowsActiveScheme;
+ (id)schedulingLogAspect;
+ (id)clangInvocationLogAspect;
+ (id)symbolAdditionLogAspect;
+ (id)deferredMetricLogAspect;
+ (id)metricLogAspect;
+ (id)logAspect;
@property(readonly, nonatomic) DVTFilePath *databaseFile; // @synthesize databaseFile=_databaseFile;
//@property(readonly, nonatomic) IDEIndexDatabase *database; // @synthesize database=_workspaceDatabase;
- (id)targetIdentifiersForFile:(id)arg1;
- (id)mainFilesForFile:(id)arg1;
- (id)sdkForFile:(id)arg1;
- (id)timestampForFile:(id)arg1;
- (void)_buildOperationDidStop:(id)arg1;
- (void)_buildSettingsDidChange:(id)arg1;
- (void)_activeRunDestinationDidChange:(id)arg1;
- (void)_activeRunContextDidChange:(id)arg1;
- (void)_clearAllCachedBuildSettings;
- (void)_computePreferredTargets;
- (BOOL)isPreferredTarget:(id)arg1 priority:(char *)arg2;
- (BOOL)isPreferredTarget:(id)arg1;
- (id)databaseQueryProvider;
- (id)queryProviderForLocation:(id)arg1 highPriority:(BOOL)arg2;
- (void)dontDeferJobForFile:(id)arg1 indexable:(id)arg2;
- (void)registerHotFile:(id)arg1;
- (id)queryProviderForFile:(id)arg1 highPriority:(BOOL)arg2;
- (id)resolutionForName:(id)arg1 kind:(id)arg2 containerName:(id)arg3;
- (id)indexableForCopiedHeader:(id)arg1;
- (id)originalPathsForPaths:(id)arg1;
- (id)effectivePathForHeader:(id)arg1;
- (void)_initCopiedHeaders;
- (void)indexModuleIfNeeded:(id)arg1;
- (void)_cleanupOldPCHs;
- (void)didCancelIndexingPCHFile:(id)arg1;
- (BOOL)createPCHFile:(id)arg1 arguments:(id)arg2 hashCriteria:(id)arg3 target:(id)arg4 session:(id)arg5 willIndex:(BOOL)arg6 translationUnit:(id *)arg7;
- (void)database:(id)arg1 reportAutoQueryProgress:(double)arg2;
- (void)clearPCHFailuresForDatabase:(id)arg1;
- (void)databaseDidReportError:(id)arg1;
- (void)databaseDidLoad:(id)arg1;
- (void)databaseDidOpen:(id)arg1;
- (id)databaseProvidersAndVersions:(id)arg1;
- (void)database:(id)arg1 didForgetFiles:(id)arg2;
- (void)database:(id)arg1 didEndImportSession:(id)arg2;
- (void)databaseDidSave:(id)arg1;
- (void)databaseDidIndexHotFile:(id)arg1;
- (void)_respondToFileChangeNotification:(id)arg1;
@property(readonly, nonatomic) DVTFilePath *workspaceFile;
@property(readonly, nonatomic) NSString *workspaceName;
- (id)dataSourceExtensionForFile:(id)arg1 settings:(id)arg2;
- (id)_dataSourceExtensionForFile:(id)arg1 withSettings:(id)arg2;
- (id)settingsForFile:(id)arg1 indexable:(id)arg2;
- (id)_waitForSettingsForFile:(id)arg1 object:(id)arg2;
- (id)_waitForSettingsFromObject:(id)arg1;
- (id)workspaceHeadersForIndexable:(id)arg1;
- (void)gatherProductHeadersForIndexable:(id)arg1;
- (long long)purgeCount;
- (void)purgeFileCaches;
- (void)close;
- (void)editorWillSaveFile:(id)arg1;
- (void)expediteIndexing;
- (void)_stopIndexing;
- (void)setThrottleFactor:(double)arg1;
- (void)resumeIndexing;
- (void)suspendIndexing;
@property(readonly, nonatomic) BOOL shouldAllowRefactoring;
@property(readonly, nonatomic) BOOL isQuiescent;
- (void)doWhenFilesReady:(dispatch_block_t)arg1;
- (void)willRegisterMoreFiles:(BOOL)arg1;
- (void)unregisterFile:(id)arg1;
- (void)registerFile:(id)arg1;
- (id)indexableForIdentifier:(id)arg1;
- (void)unregisterObject:(id)arg1;
- (void)registerObject:(id)arg1;
- (void)postNotificationName:(id)arg1;
- (void)postNotificationName:(id)arg1 userInfo:(id)arg2;
- (id)description;
- (void)setIndexState:(id)arg1;
- (id)indexState;
@property(readonly) DVTFilePath *workspaceBuildProductsDirPath;
@property(readonly) DVTFilePath *headerMapFilePath;
- (void)observeValueForKeyPath:(id)arg1 ofObject:(id)arg2 change:(id)arg3 context:(void *)arg4;
- (BOOL)isCurrentForWorkspace:(id)arg1;
- (void)beginTextIndexing;
- (id)initWithWorkspace:(id)arg1;
- (id)initWithFolder:(id)arg1;
- (id)initWithFolder:(id)arg1 forWorkspace:(id)arg2;
- (void)_cleanupOldIndexFoldersForWorkspace:(id)arg1;
- (double)_atime:(struct stat *)arg1;
- (BOOL)_stat:(struct stat *)arg1 filePath:(id)arg2;
- (id)_databaseFileURLForFolder:(id)arg1;
- (id)_databaseFolderForWorkspace:(id)arg1;
- (BOOL)_reopenDatabaseWithRemoval:(BOOL)arg1;
- (BOOL)_createDatabaseFolder;
- (void)_setupObservers;
- (id)allAutoImportItemsMatchingKind:(id)arg1 symbolLanguage:(id)arg2;
- (id)allAutoImportItemsMatchingKind:(id)arg1;
- (id)filesWithSymbolOccurrencesMatchingName:(id)arg1 kind:(id)arg2;
- (id)classesWithReferencesToSymbols:(id)arg1;
- (id)allClassesWithMembers:(id)arg1;
- (id)classesWithMembers:(id)arg1;
- (id)allMethodsMatchingMethod:(id)arg1 forReceiver:(id)arg2;
- (id)membersMatchingName:(id)arg1 kinds:(id)arg2 forInterfaces:(id)arg3;
- (id)membersMatchingKinds:(id)arg1 forInterfaces:(id)arg2;
- (id)symbolsForResolutions:(id)arg1;
- (id)parsedCodeCommentAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)codeDiagnosticsAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)codeCompletionsAtLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2 completionContext:(id *)arg3;
- (id)allParentsOfSymbols:(id)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelSymbolsInFile:(id)arg1;
- (unsigned long long)countOfSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2;
- (id)allSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2 cancelWhen:(dispatch_block_t)arg3;
- (id)allSymbolsMatchingKind:(id)arg1 workspaceOnly:(BOOL)arg2;
- (id)allSymbolsMatchingKind:(id)arg1;
- (id)testMethodsForClasses:(id)arg1;
- (id)allSubClassesForClasses:(id)arg1;
- (id)allSymbolsMatchingNames:(id)arg1 kind:(id)arg2;
- (id)allSymbolsMatchingName:(id)arg1 kind:(id)arg2;
- (id)allProtocolsMatchingName:(id)arg1;
- (id)allClassesMatchingName:(id)arg1;
- (id)impliedHeadersForModuleImportLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)importedFileAtDocumentLocation:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)importedFilesAtDocument:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)collectionElementTypeSymbolForSymbol:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)typeSymbolForSymbol:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)messageReceiverInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)referencesToSymbolMatchingName:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)referencesToSymbol:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)symbolsUsedInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)symbolsOccurrencesInContext:(id)arg1 withCurrentFileContentDictionary:(id)arg2;
- (id)symbolsMatchingName:(id)arg1 inContext:(id)arg2 withCurrentFileContentDictionary:(id)arg3;
- (id)symbolsMatchingName:(id)arg1 inContext:(id)arg2;
- (id)symbolsContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5 cancelWhen:(dispatch_block_t)arg6;
- (id)symbolsContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5;
- (id)topLevelProtocolsWorkspaceOnly:(BOOL)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelProtocolsWorkspaceOnly:(BOOL)arg1;
- (id)topLevelProtocols;
- (id)topLevelClassesWorkspaceOnly:(BOOL)arg1 cancelWhen:(dispatch_block_t)arg2;
- (id)topLevelClassesWorkspaceOnly:(BOOL)arg1;
- (id)topLevelClasses;
- (id)filesContaining:(id)arg1 anchorStart:(BOOL)arg2 anchorEnd:(BOOL)arg3 subsequence:(BOOL)arg4 ignoreCase:(BOOL)arg5 cancelWhen:(dispatch_block_t)arg6;
- (id)filesIncludedByFile:(id)arg1;
- (id)filesIncludingFile:(id)arg1;
- (id)mainFileForSelectionFilePath:(id)arg1 buildSettings:(id *)arg2;
- (id)objCOrCCompilationUnitIndexablesForMainFile:(id)arg1 indexableObjects:(id)arg2;
- (BOOL)isFileObjCCompilationUnitOrHeader:(id)arg1 error:(id *)arg2;
- (id)_localizedPhraseForDependentObjCCompilationUnit:(id)arg1 errorLanguages:(id)arg2 sharedLanguageIdentifier:(id)arg3 sharedIndexableObject:(id)arg4;
- (id)_localizedDescriptionForObjCCompilationUnit:(id)arg1 errorLanguages:(id)arg2;
- (BOOL)_errorLanguages:(id *)arg1 forFilePath:(id)arg2 indexableObjects:(id)arg3;

@end

@class IDEIndexDatabase;
@interface IDEIndexDatabaseQueryProvider : NSObject
- (id)topLevelSymbolsInFile:(NSString *)filePath forIndex:(IDEIndex *)index;
- (id)filesContaining:(NSString *)a anchorStart:(NSString *)b anchorEnd:(NSString *)c subsequence:(NSString *)d ignoreCase:(BOOL)ignoreCase forIndex:(IDEIndex *)wwefwew;
- (IDEIndexDatabase *)database;
@end

@interface IDEIndexDBConnection : NSObject
- (void)close;
- (void)finalize;
- (id)dbConnection;
@end

@interface IDEIndexDatabase : NSObject
- (IDEIndexDatabase *)initWithFileURL:(NSURL *)fileURL;
- (IDEIndexDatabaseQueryProvider *)queryProvider;
- (void)open;
- (void)openReadonly;
- (void)openInDiagnosticMode;
- (void)close;
- (id)mainFilesForTarget:(NSString *)targetNameOrWTF;
- (IDEIndexDBConnection *)newConnection;
- (NSURL *)fileURL;
@end

@interface DVTModelObject : NSObject
@end

@interface IDEContainerItem : DVTModelObject
@end

@interface IDEGroup : IDEContainerItem
- (NSArray *)subitems;
- (NSImage *)navigableItem_image;
@end

@interface IDEContainer : DVTModelObject
- (DVTFilePath *)filePath;
- (IDEGroup *)rootGroup;
- (void)debugPrintInnerStructure;
- (void)debugPrintStructure;
@end

@interface IDEXMLPackageContainer : IDEContainer
@end

@interface IDEWorkspace : IDEXMLPackageContainer
- (IDEIndex *)index;
- (NSString *)name;
- (NSSet *)referencedContainers;
@end

@interface IDEWorkspaceDocument : NSObject
- (IDEWorkspace *)workspace;
- (NSArray *)recentEditorDocumentURLs;
- (id)sdefSupport_fileReferences;
@end

@interface IDEWorkspaceWindow : NSWindow
- (IDEWorkspaceDocument *)document;
@end

@interface IDEWorkspaceWindow (MissingMethods)
+ (IDEWorkspaceWindow *)mc_lastActiveWorkspaceWindow;
@end

@interface IDEFileReference : NSObject
- (IDEContainer *)referencedContainer;
@end

@interface PBXObject : NSObject
@end

@interface PBXContainer : PBXObject
- (NSString *)name;
@end

@interface PBXContainerItem : PBXObject
@end

@class PBXGroup;
@interface PBXReference : PBXContainerItem
- (BOOL)isGroup;
- (NSString *)name;
- (NSString *)absolutePath;
- (PBXGroup *)group;
- (PBXContainer *)container;
@end

@interface PBXGroup : PBXReference
- (NSArray *)children;
@end

@interface Xcode3Group : IDEGroup
- (PBXGroup *)group;
@end

@interface Xcode3Project : IDEContainer
- (Xcode3Group *)rootGroup;
@end

@interface DVTApplication : NSApplication
@end

@interface IDEApplication : DVTApplication
+ (IDEApplication *)sharedApplication;
@end

@interface IDEApplicationController : NSObject
+ (IDEApplicationController *)sharedAppController;
- (BOOL)application:(IDEApplication *)application openFile:(NSString *)filePath;
@end

@interface XCSpecification : NSObject
@end

@interface PBXFileType : XCSpecification
- (BOOL)isBundle;
- (BOOL)isApplication;
- (BOOL)isLibrary;
- (BOOL)isFramework;
- (BOOL)isProjectWrapper;
- (BOOL)isTargetWrapper;
- (BOOL)isExecutable;
@end

@interface PBXFileReference : PBXReference
- (NSString *)resolvedAbsolutePath;
- (id)fileType;
- (NSArray *)children;
@end

@interface IDEIndexSymbolOccurrence : NSObject
- (id)file;
- (id)location;
- (long long)lineNumber;
@end

@interface IDEIndexCollection : NSObject
- (NSArray *)allObjects;
@end

@interface IDEIndexSymbolOccurrenceCollection : IDEIndexCollection <NSFastEnumeration>
@end

@interface IDEIndexSymbol : NSObject
- (NSString *)name;
- (DVTSourceCodeSymbolKind *)symbolKind;
- (NSString *)displayText;
- (NSString *)completionText;
- (NSString *)displayType;
- (NSString *)descriptionText;
- (NSImage *)icon;

- (IDEIndexSymbolOccurrence *)modelOccurrence;
- (IDEIndexSymbolOccurrenceCollection *)occurrences;
- (IDEIndexSymbolOccurrenceCollection *)declarations;
- (IDEIndexSymbolOccurrenceCollection *)definitions;

- (NSArray *)containerSymbols;
- (id)containerSymbol;

- (unsigned long long)hash;
@end

@interface IDEIndexContainerSymbol : IDEIndexSymbol
- (NSArray *)children;
@end

@interface IDEIndexClassSymbol : IDEIndexContainerSymbol
- (NSArray *)categories;
@end

@interface IDEIndexProtocolSymbol : IDEIndexContainerSymbol
@end

@interface IDEIndexCategorySymbol : IDEIndexContainerSymbol
- (NSArray *)classMethods;
- (NSArray *)instanceMethods;
- (NSArray *)properties;
@end

@interface IDENavigableItem : NSObject
+ (IDENavigableItem *)navigableItemWithRepresentedObject:(id)object;
@end

@interface IDEFileNavigableItem : IDENavigableItem
+ (IDEFileNavigableItem *)navigableItemWithRepresentedObject:(id)object;
@end

@interface IDEFileReferenceNavigableItem : IDEFileNavigableItem
+ (IDEFileReferenceNavigableItem *)navigableItemWithRepresentedObject:(id)object;
@end

@interface DVTDocumentLocation : NSObject
- (DVTDocumentLocation *)initWithDocumentURL:(NSURL *)documentURL timestamp:(NSNumber *)timestamp;
- (NSURL *)documentURL;
@end

@interface DVTTextDocumentLocation : DVTDocumentLocation
- (DVTTextDocumentLocation *)initWithDocumentURL:(NSURL *)documentURL timestamp:(NSNumber *)timestamp lineRange:(NSRange)lineRange;
- (NSRange)characterRange;
- (NSURL *)documentURL;
@end

@interface DVTViewController : NSViewController
@end
@interface IDEViewController : DVTViewController
@end

@interface IDEEditorOpenSpecifier : NSObject
- (IDEEditorOpenSpecifier *)initWithNavigableItem:(IDENavigableItem *)navigableItem error:(NSError *)error;
+ (IDEEditorOpenSpecifier *)structureEditorOpenSpecifierForDocumentLocation:(DVTDocumentLocation *)documentLocation inWorkspace:(IDEWorkspace *)workspace error:(NSError *)error;
@end

@interface IDEEditorHistoryItem : NSObject
- (NSString *)historyMenuItemTitle;
- (NSURL *)documentURL;
@end

@interface DVTSourceExpression : NSObject
- (NSString *)textSelectionString;
@end

@interface IDEEditorHistoryStack : NSObject
- (NSArray *)previousHistoryItems;
- (NSArray *)nextHistoryItems;
- (IDEEditorHistoryItem *)currentEditorHistoryItem;
@end

@class IDEEditor;
@interface IDEEditorContext : IDEViewController
- (BOOL)openEditorOpenSpecifier:(IDEEditorOpenSpecifier *)openSpecifier;
- (IDEEditorHistoryStack *)currentHistoryStack;
- (IDEEditor *)editor;
@end

@interface IDEEditorArea : IDEViewController
- (IDEEditorContext *)primaryEditorContext;
- (IDEEditorContext *)lastActiveEditorContext;
@end

@interface IDEWorkspaceWindowController : NSWindowController
+ (NSArray *)workspaceWindowControllers;
+ (IDEWorkspaceWindowController *)workspaceWindowControllerForWindow:(IDEWorkspaceWindow *)window;
- (IDEEditorArea *)editorArea;
@end

@interface IDEKeyBinding : NSObject
- (NSString *)title;
- (NSString *)group;
- (NSArray *)actions;
- (NSArray *)keyboardShortcuts;
+ (IDEKeyBinding *)keyBindingWithTitle:(NSString *)title group:(NSString *)group actions:(NSArray *)actions keyboardShortcuts:(NSArray *)keyboardShortcuts;
+ (IDEKeyBinding *)keyBindingWithTitle:(NSString *)title parentTitle:(NSString *)parentTitle group:(NSString *)group actions:(NSArray *)actions keyboardShortcuts:(NSArray *)keyboardShortcuts;
@end

@interface IDEMenuKeyBinding : IDEKeyBinding
- (NSString *)commandIdentifier;
+ (IDEMenuKeyBinding *)keyBindingWithTitle:(NSString *)title group:(NSString *)group actions:(NSArray *)actions keyboardShortcuts:(NSArray *)keyboardShortcuts;
+ (IDEMenuKeyBinding *)keyBindingWithTitle:(NSString *)title parentTitle:(NSString *)parentTitle group:(NSString *)group actions:(NSArray *)actions keyboardShortcuts:(NSArray *)keyboardShortcuts;
- (void)setCommandIdentifier:(NSString *)commandIdentifier;
@end

@class IDEKeyBindingPreferenceSetManager;
@class IDEMenuKeyBindingSet;
@interface IDEKeyBindingPreferenceSet : NSObject
+ (IDEKeyBindingPreferenceSetManager *)preferenceSetsManager;
- (IDEMenuKeyBindingSet *)menuKeyBindingSet;
@end

@interface IDEKeyBindingPreferenceSetManager : NSObject
- (IDEKeyBindingPreferenceSet *)currentPreferenceSet;
@end

@interface IDEKeyBindingSet : NSObject
- (void)addKeyBinding:(IDEKeyBinding *)keyBinding;
- (void)insertObject:(IDEKeyBinding *)keyBinding inKeyBindingsAtIndex:(NSUInteger)index;
- (void)updateDictionary;
@end

@interface IDEKeyboardShortcut : NSObject
+ (id)keyboardShortcutFromStringRepresentation:(NSString *)stringRep;
- (NSString *)stringRepresentation;
- (NSString *)keyEquivalent;
- (IDEKeyboardShortcut *)keyboardShortcutFromStringRepresentation:(NSString *)stringRep;
- (unsigned long long)modifierMask;
@end

@interface IDEMenuKeyBindingSet : IDEKeyBindingSet
- (NSArray *)keyBindings;
@end

@interface DVTLayoutView_ML : NSView
{
    NSMutableDictionary *invalidationTokens;
    BOOL _layoutNeeded;
    BOOL _implementsLayoutCompletionCallback;
    NSCountedSet *_frameChangeObservations;
    NSCountedSet *_boundsChangeObservations;
    BOOL _implementsDrawRect;
    BOOL _needsSecondLayoutPass;
}

+ (void)_layoutWindow:(id)arg1;
+ (void)_recursivelyLayoutSubviewsOfView:(id)arg1 populatingSetWithLaidOutViews:(id)arg2;
+ (void)_doRecursivelyLayoutSubviewsOfView:(id)arg1 populatingSetWithLaidOutViews:(id)arg2 completionCallBackHandlers:(id)arg3 currentLayoutPass:(long long)arg4 needsSecondPass:(char *)arg5;
+ (void)scheduleWindowForLayout:(id)arg1;
+ (id)alreadyLaidOutViewsForCurrentDisplayPassOfWindow:(id)arg1;
+ (void)clearAlreadyLaidOutViewsForCurrentDisplayPassOfWindow:(id)arg1;
@property BOOL needsSecondLayoutPass; // @synthesize needsSecondLayoutPass=_needsSecondLayoutPass;
@property(getter=isLayoutNeeded) BOOL layoutNeeded; // @synthesize layoutNeeded=_layoutNeeded;
- (BOOL)wantsDefaultClipping;
- (void)stopInvalidatingLayoutWithChangesToKeyPath:(id)arg1 ofObject:(id)arg2;
- (void)invalidateLayoutWithChangesToKeyPath:(id)arg1 ofObject:(id)arg2;
- (void)_autoLayoutViewViewFrameDidChange:(id)arg1;
- (void)_autoLayoutViewViewBoundsDidChange:(id)arg1;
- (void)stopInvalidatingLayoutWithBoundsChangesToView:(id)arg1;
- (void)stopInvalidatingLayoutWithFrameChangesToView:(id)arg1;
- (void)invalidateLayoutWithBoundsChangesToView:(id)arg1;
- (void)invalidateLayoutWithFrameChangesToView:(id)arg1;
- (void)tearDownObservationForObservedObject:(id)arg1 notificationName:(id)arg2 table:(id)arg3;
- (void)setupObservationForObservedObject:(id)arg1 selector:(SEL)arg2 notificationName:(id)arg3 table:(id *)arg4;
- (void)setFrameSize:(struct CGSize)arg1;
- (void)didCompleteLayout;
- (void)layoutBottomUp;
- (void)layoutTopDown;
- (void)layoutIfNeeded;
- (void)didLayoutSubview:(id)arg1;
- (id)subviewsOrderedForLayout;
- (void)viewWillDraw;
- (void)_reallyLayoutIfNeededBottomUp;
- (void)_reallyLayoutIfNeededTopDown;
- (void)invalidateLayout;
- (void)viewDidMoveToWindow;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)_DVTLayoutView_MLSharedInit;
- (void)dealloc;

@end

@class DVTExtension, DVTStackBacktrace, DVTViewController, NSMapTable, NSString;

@interface DVTReplacementView : DVTLayoutView_ML
{
    Class _controllerClass;
    NSString *_controllerExtensionIdentifier;
    DVTExtension *_controllerExtension;
    DVTViewController *_installedViewController;
    id _forwardedBindingInfo;
//    id <DVTReplacementViewDelegate> _delegate;
    int _horizontalContentViewResizingMode;
    int _verticalContentViewResizingMode;
    struct {
        unsigned int _needToReloadSubview:1;
        unsigned int _shouldNotifyInstalledViewControllerObservers:1;
        unsigned int _delegate_willInstallViewController:1;
        unsigned int _delegate_didInstallViewController:1;
        unsigned int _delegate_willCloseViewController:1;
        unsigned int _delegate_willDisplayInRect:1;
        unsigned int _reserved:26;
    } _DVTReplacementViewFlags;
    BOOL _isGrouped;
    NSMapTable *_subviewFrameChangeTokens;
    void *_keepSelfAliveUntilCancellationRef;
}

+ (void)initialize;
@property BOOL isGrouped; // @synthesize isGrouped=_isGrouped;
@property(nonatomic) Class controllerClass; // @synthesize controllerClass=_controllerClass;
@property(nonatomic) int verticalContentViewResizingMode; // @synthesize verticalContentViewResizingMode=_verticalContentViewResizingMode;
@property(nonatomic) int horizontalContentViewResizingMode; // @synthesize horizontalContentViewResizingMode=_horizontalContentViewResizingMode;
- (void)discardEditing;
- (BOOL)commitEditingForAction:(int)arg1 errors:(id)arg2;
- (void)updateBoundControllerExtensionIdentifier;
- (void)updateBoundControllerClass;
@property(copy) NSString *controllerExtensionIdentifier;
- (void)_clearCurrentController;
- (void)_tearDownBinding:(id)arg1;
- (void)_forwardBinding:(id)arg1 toObject:(id)arg2 withKeyPath:(id)arg3 options:(id)arg4;
- (void)_tearDownBindings;
- (void)_forwardBindings;
- (void)layoutBottomUp;
- (void)layoutTopDown;
@property(retain) DVTViewController *installedViewController;
- (void)_tearDownViewController;
- (void)_setupViewController;
- (void)_configureExtension;
- (id)infoForBinding:(id)arg1;
- (void)unbind:(id)arg1;
- (void)bind:(id)arg1 toObject:(id)arg2 withKeyPath:(id)arg3 options:(id)arg4;
- (id)_forwardedBindingInfo;
- (void)_clearInfoForBinding:(id)arg1;
- (void)_recordInfoForBinding:(id)arg1 toObject:(id)arg2 keyPath:(id)arg3 options:(id)arg4;
- (void)primitiveInvalidate;
- (void)_recursiveDisplayAllDirtyWithLockFocus:(BOOL)arg1 visRect:(struct CGRect)arg2;
- (id)exposedBindings;
- (void)_invalidateLayoutBecauseOfSubviewFrameChange:(id)arg1;
- (void)willRemoveSubview:(id)arg1;
- (void)didAddSubview:(id)arg1;
- (id)initWithFrame:(struct CGRect)arg1;
- (void)awakeFromNib;
- (void)encodeWithCoder:(id)arg1;
- (id)initWithCoder:(id)arg1;
- (void)_commonInit;
//@property(retain, nonatomic) id <DVTReplacementViewDelegate> delegate;
- (id)accessibilityAttributeValue:(id)arg1;
- (BOOL)accessibilityIsIgnored;

// Remaining properties
@property(nonatomic, retain) DVTStackBacktrace *creationBacktrace;
@property(readonly) DVTStackBacktrace *invalidationBacktrace;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end

@class DVTDelayedInvocation, DVTExtension, DVTReplacementView, DVTStateRepository, DVTStateToken, IDEViewController, NSString;

@interface IDEPreferencesController : NSWindowController <NSToolbarDelegate, NSWindowRestoration>
{
    DVTReplacementView *_paneReplacementView;
    DVTExtension *_currentExtension;
    DVTStateRepository *_stateRepository;
    DVTDelayedInvocation *_stateSavingInvocation;
    DVTStateToken *_stateToken;
}

+ (void)configureStateSavingObjectPersistenceByName:(id)arg1;
+ (void)restoreWindowWithIdentifier:(id)arg1 state:(id)arg2 completionHandler:(id)arg3;
+ (id)defaultPreferencesController;
@property(readonly) DVTDelayedInvocation *stateSavingInvocation; // @synthesize stateSavingInvocation=_stateSavingInvocation;
@property(retain) DVTStateToken *stateToken; // @synthesize stateToken=_stateToken;
@property(readonly) DVTStateRepository *stateRepository; // @synthesize stateRepository=_stateRepository;
@property(retain) DVTExtension *currentExtension; // @synthesize currentExtension=_currentExtension;
@property(retain) DVTReplacementView *paneReplacementView; // @synthesize paneReplacementView=_paneReplacementView;
- (BOOL)_loadStateData:(id *)arg1;
- (BOOL)_saveStateData:(id *)arg1;
- (id)_stateRepositoryFilePath;
- (void)commitStateToDictionary:(id)arg1;
- (void)revertStateWithDictionary:(id)arg1;
- (void)replacementView:(id)arg1 willCloseViewController:(id)arg2;
- (void)replacementView:(id)arg1 didInstallViewController:(id)arg2;
- (void)replacementView:(id)arg1 willInstallViewController:(id)arg2;
- (void)stateRepositoryDidChange:(id)arg1;
- (void)selectPreviousTab:(id)arg1;
- (void)selectNextTab:(id)arg1;
- (void)_selectToolbarItem:(id)arg1;
- (void)showPreferencesPanel:(id)arg1;
- (id)toolbarSelectableItemIdentifiers:(id)arg1;
- (id)toolbarDefaultItemIdentifiers:(id)arg1;
- (id)toolbarAllowedItemIdentifiers:(id)arg1;
- (id)toolbar:(id)arg1 itemForItemIdentifier:(id)arg2 willBeInsertedIntoToolbar:(BOOL)arg3;
- (void)windowWillClose:(id)arg1;
- (void)selectPreferencePaneWithIdentifier:(id)arg1;
@property(readonly) IDEViewController *currentPreferencePaneViewController;
@property(readonly) NSString *downloadsPrefPaneIdentifier;
- (void)windowDidLoad;
- (id)initWithWindow:(id)arg1;
- (void)_cachePreferencePaneExtensions;

@end

@interface DVTPlugInManager : NSObject
{
//    DVTDispatchLock *_plugInManagerLock;
    NSFileManager *_fileManager;
    NSString *_hostAppName;
    NSString *_hostAppContainingPath;
    NSMutableArray *_searchPaths;
    NSArray *_extraSearchPaths;
    NSMutableSet *_pathExtensions;
    NSMutableSet *_exposedCapabilities;
    NSMutableSet *_defaultPlugInCapabilities;
    NSMutableSet *_requiredPlugInIdentifiers;
    NSString *_plugInCachePath;
    NSDictionary *_plugInCache;
    BOOL _shouldClearPlugInCaches;
    id _plugInLocator;
    NSMutableDictionary *_plugInsByIdentifier;
    NSMutableDictionary *_extensionPointsByIdentifier;
    NSMutableDictionary *_extensionsByIdentifier;
    NSMutableDictionary *_invalidExtensionsByIdentifier;
    NSMutableSet *_warnedExtensionPointFailures;
    NSMutableSet *_nonApplePlugInSanitizedStatuses;
}

+ (void)_setDefaultPlugInManager:(id)arg1;
+ (id)defaultPlugInManager;
+ (void)initialize;
@property(retain) id plugInLocator; // @synthesize plugInLocator=_plugInLocator;
@property BOOL shouldClearPlugInCaches; // @synthesize shouldClearPlugInCaches=_shouldClearPlugInCaches;
- (id)_invalidExtensionWithIdentifier:(id)arg1;
- (id)_plugInCachePath;
- (id)_applicationCachesPath;
- (id)_toolsVersionName;
- (void)_createPlugInObjectsFromCache;
- (BOOL)_savePlugInCacheWithScanRecords:(id)arg1 error:(id *)arg2;
- (BOOL)_removePlugInCacheAndReturnError:(id *)arg1;
- (BOOL)_removePlugInCacheAtPath:(id)arg1 error:(id *)arg2;
- (id)_plugInCacheSaveFailedErrorWithUnderlyingError:(id)arg1;
- (BOOL)_loadPlugInCache:(id *)arg1;
- (BOOL)_cacheCoversPlugInsWithScanRecords:(id)arg1;
- (id)_modificationDateOfFileAtPath:(id)arg1;
@property(readonly) BOOL usePlugInCache;
- (void)_preLoadPlugIns;
- (BOOL)_checkPresenceOfRequiredPlugIns:(id)arg1 error:(id *)arg2;
- (BOOL)_checkMarketingVersionOfApplePlugIns:(id)arg1 error:(id *)arg2;
- (BOOL)shouldPerformConsistencyCheck;
- (void)_registerPlugInsFromScanRecords:(id)arg1;
- (void)_pruneUnusablePlugInsAndScanRecords:(id)arg1;
- (void)_recordSanitizedPluginStatus:(id)arg1 errorMessage:(id)arg2;
- (void)_addSanitizedNonApplePlugInStatusForBundle:(id)arg1 reason:(id)arg2;
@property(readonly) NSSet *sanitizedNonApplePlugInStatuses;
- (void)_createPlugInObjectsFromScanRecords:(id)arg1;
- (void)_applyActivationRulesToScanRecords:(id)arg1;
- (id)_scanForPlugInsInDirectories:(id)arg1 skippingDuplicatesOfPlugIns:(id)arg2;
- (BOOL)_scanForPlugIns:(id *)arg1;
@property(readonly) NSUUID *plugInHostUUID;
@property BOOL hasScannedForPlugIns; // @dynamic hasScannedForPlugIns;
- (id)_scanRecordForBundle:(id)arg1 atPath:(id)arg2;
- (BOOL)_isInitialScan;
- (id)_defaultPathExtensions;
@property(readonly) NSArray *defaultSearchPaths;
- (id)_defaultApplicationSupportSubdirectory;
@property(readonly) NSArray *extraSearchPaths;
- (id)_extensionsForExtensionPoint:(id)arg1 matchingPredicate:(id)arg2;
- (id)sharedExtensionsForExtensionPoint:(id)arg1 matchingPredicate:(id)arg2;
- (id)sharedExtensionWithIdentifier:(id)arg1;
- (id)extensionWithIdentifier:(id)arg1;
- (id)extensionPointWithIdentifier:(id)arg1;
- (id)plugInWithIdentifier:(id)arg1;
- (BOOL)scanForPlugIns:(id *)arg1;
- (id)init;
- (id)_hostAppName;
- (id)_hostAppContainingPath;

// Remaining properties
@property(copy) NSSet *defaultPlugInCapabilities; // @dynamic defaultPlugInCapabilities;
@property(copy) NSSet *exposedCapabilities; // @dynamic exposedCapabilities;
@property(readonly) NSMutableSet *mutableDefaultPlugInCapabilities; // @dynamic mutableDefaultPlugInCapabilities;
@property(readonly) NSMutableSet *mutableExposedCapabilities; // @dynamic mutableExposedCapabilities;
@property(readonly) NSMutableSet *mutablePathExtensions; // @dynamic mutablePathExtensions;
@property(readonly) NSMutableSet *mutableRequiredPlugInIdentifiers; // @dynamic mutableRequiredPlugInIdentifiers;
@property(readonly) NSMutableArray *mutableSearchPaths; // @dynamic mutableSearchPaths;
@property(copy) NSSet *pathExtensions; // @dynamic pathExtensions;
@property(copy) NSSet *requiredPlugInIdentifiers; // @dynamic requiredPlugInIdentifiers;
@property(copy) NSArray *searchPaths; // @dynamic searchPaths;

@end

@class DVTDispatchLock, DVTExtensionPoint, DVTPlugIn, DVTPlugInManager, NSBundle, NSDictionary, NSMutableDictionary, NSString, NSXMLElement;

@interface DVTExtension : NSObject
{

}

+ (void)initialize;
@property(readonly) DVTExtension *basedOnExtension; // @synthesize basedOnExtension=_basedOnExtension;
@property(readonly) DVTExtensionPoint *extensionPoint; // @synthesize extensionPoint=_extensionPoint;
@property(readonly) DVTPlugIn *plugIn; // @synthesize plugIn=_plugIn;
@property(readonly) NSDictionary *extensionData; // @synthesize extensionData=_extensionData;
@property(readonly) DVTPlugInManager *plugInManager; // @synthesize plugInManager=_plugInManager;
@property(readonly) NSString *name; // @synthesize name=_name;
@property(readonly) NSString *version; // @synthesize version=_version;
@property(readonly) NSString *identifier; // @synthesize identifier=_identifier;
- (id)_localizedStringForString:(id)arg1;
- (BOOL)_fireExtensionFault:(id *)arg1;
- (void)_adjustClassReferencesInParameterData:(id)arg1 usingSchema:(id)arg2;
- (void)_adjustElementClassAttributes:(id)arg1 forKey:(id)arg2 inParameterData:(id)arg3;
- (void)_adjustClassAttribute:(id)arg1 forKey:(id)arg2 inParameterData:(id)arg3;
- (BOOL)_adjustElement:(id)arg1 forKey:(id)arg2 inParameterData:(id)arg3;
- (BOOL)_adjustAttribute:(id)arg1 forKey:(id)arg2 inParameterData:(id)arg3;
- (BOOL)_adjustParameterData:(id)arg1 usingSchema:(id)arg2;
- (BOOL)hasValueForKey:(id)arg1;
- (BOOL)_hasValueForKey:(id)arg1 inParameterData:(id)arg2 usingSchema:(id)arg3;
- (id)valueForKey:(id)arg1 error:(id *)arg2;
- (id)valueForKey:(id)arg1;
- (id)_valueForKey:(id)arg1 inParameterData:(id)arg2 usingSchema:(id)arg3 error:(id *)arg4;
@property(readonly) NSXMLElement *extensionElement;
@property(readonly, getter=isValid) BOOL valid;
@property(readonly) NSBundle *bundle;
- (id)description;
- (void)encodeIntoPropertyList:(id)arg1;
- (void)awakeWithPropertyList:(id)arg1;
- (id)initWithPropertyList:(id)arg1 owner:(id)arg2;
- (id)initWithExtensionData:(id)arg1 plugIn:(id)arg2;

@end

@interface IDEEditor : IDEViewController
- (NSArray *)currentSelectedDocumentLocations;
- (DVTSourceExpression *)selectedExpression;
@end

@interface DVTSourceLandmarkItem : NSObject
- (NSString *)name;
@end

@interface IDEDocSymbolUtilities : NSObject
- (NSDictionary *)queryInfoFromIndexSymbol:(IDEIndexSymbol *)symbol;
- (id)typeForSymbol:(IDEIndexSymbol *)symbol;
- (void)queryInfoFromIndexSymbol:(IDEIndexSymbol *)symbol handlerBlock:(void(^)(id foo))block;
@end

@interface IDEQuickHelpQueries : NSObject
@end

extern NSString *IDEEditorDocumentDidChangeNotification;

@interface IDESourceCodeDocument <NSObject>
- (id)knownFileReferences;
@end

@interface Xcode3FileReference <NSObject>
- (id)resolvedFilePath;
@end

@interface DVTSourceNodeTypes : NSObject
{
}

+ (BOOL)nodeType:(short)arg1 conformsToNodeTypeNamed:(id)arg2;
+ (long long)nodeTypesCount;
+ (id)nodeTypeNameForId:(short)arg1;
+ (short)registerNodeTypeNamed:(id)arg1;
+ (void)initialize;

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

@class DVTCustomDataSpecifier, DVTPointerArray, DVTStackBacktrace, NSColor, NSFont, NSImage, NSString, NSURL;

@interface DVTFontAndColorTheme : NSObject
{
    NSString *_name;
    NSImage *_image;
    NSURL *_dataURL;
    DVTCustomDataSpecifier *_customDataSpecifier;
    NSColor *_sourceTextBackgroundColor;
    NSColor *_sourceTextSidebarBackgroundColor;
    NSColor *_sourceTextSidebarEdgeColor;
    NSColor *_sourceTextSidebarNumbersColor;
    NSColor *_sourceTextFoldbarBackgroundColor;
    NSColor *_sourceTextSelectionColor;
    NSColor *_sourceTextSecondarySelectionColor;
    NSColor *_sourceTextInsertionPointColor;
    NSColor *_sourceTextInvisiblesColor;
    NSColor *_sourceTextBlockDimBackgroundColor;
    NSColor *_sourceTextTokenizedBorderColor;
    NSColor *_sourceTextTokenizedBackgroundColor;
    NSColor *_sourceTextTokenizedBorderSelectedColor;
    NSColor *_sourceTextTokenizedBackgroundSelectedColor;
    NSColor *_consoleTextBackgroundColor;
    NSColor *_consoleTextSelectionColor;
    NSColor *_consoleTextSecondarySelectionColor;
    NSColor *_consoleTextInsertionPointColor;
    NSColor *_consoleDebuggerPromptTextColor;
    NSColor *_consoleDebuggerInputTextColor;
    NSColor *_consoleDebuggerOutputTextColor;
    NSColor *_consoleExecutableInputTextColor;
    NSColor *_consoleExecutableOutputTextColor;
    NSFont *_consoleDebuggerPromptTextFont;
    NSFont *_consoleDebuggerInputTextFont;
    NSFont *_consoleDebuggerOutputTextFont;
    NSFont *_consoleExecutableInputTextFont;
    NSFont *_consoleExecutableOutputTextFont;
    NSColor *_debuggerInstructionPointerColor;
    NSColor *_sourcePlainTextColor;
    NSFont *_sourcePlainTextFont;
    DVTPointerArray *_syntaxColorsByNodeType;
    DVTPointerArray *_syntaxFontsByNodeType;
    NSColor *_sourceTextCompletionPreviewColor;
    BOOL _builtIn;
    BOOL _loadedData;
    BOOL _contentNeedsSaving;
    BOOL _hasMultipleSourceTextFonts;
}

+ (id)_defaultSourceCodeFont;
+ (id)keyPathsForValuesAffectingConsoleTextSecondarySelectionColor;
+ (id)keyPathsForValuesAffectingSourceTextSecondarySelectionColor;
+ (id)titleForNewPreferenceSetFromTemplate;
+ (id)preferenceSetsListHeader;
+ (id)preferenceSetsFileExtension;
+ (id)defaultKeyForExcludedBuiltInPreferenceSets;
+ (id)defaultKeyForCurrentPreferenceSet;
+ (id)builtInPreferenceSetsDirectoryURL;
+ (id)systemPreferenceSet;
+ (id)preferenceSetGroupingName;
+ (id)_nodeTypesIncludedInPreferences;
+ (id)_stringRepresentationOfFont:(id)arg1;
+ (id)_fontWithName:(id)arg1 size:(double)arg2;
+ (id)currentTheme;
+ (id)preferenceSetsManager;
+ (void)initialize;
@property(readonly) BOOL loadedData; // @synthesize loadedData=_loadedData;
@property(readonly) DVTPointerArray *syntaxFontsByNodeType; // @synthesize syntaxFontsByNodeType=_syntaxFontsByNodeType;
@property(readonly) DVTPointerArray *syntaxColorsByNodeType; // @synthesize syntaxColorsByNodeType=_syntaxColorsByNodeType;
@property(nonatomic) BOOL hasMultipleSourceTextFonts; // @synthesize hasMultipleSourceTextFonts=_hasMultipleSourceTextFonts;
@property BOOL contentNeedsSaving; // @synthesize contentNeedsSaving=_contentNeedsSaving;
@property(retain) DVTCustomDataSpecifier *customDataSpecifier; // @synthesize customDataSpecifier=_customDataSpecifier;
@property(readonly, getter=isBuiltIn) BOOL builtIn; // @synthesize builtIn=_builtIn;
@property(retain) NSImage *image; // @synthesize image=_image;
@property(copy) NSString *name; // @synthesize name=_name;
- (void)setFont:(id)arg1 forNodeTypes:(id)arg2;
- (void)setColor:(id)arg1 forNodeTypes:(id)arg2;
- (void)_setColorOrFont:(id)arg1 forNodeTypes:(id)arg2;
- (id)fontForNodeType:(short)arg1;
- (id)colorForNodeType:(short)arg1;
@property(readonly) NSFont *sourcePlainTextFont;
@property(readonly) NSColor *sourcePlainTextColor;
- (void)setDebuggerInstructionPointerColor:(id)arg1;
- (void)setConsoleExecutableOutputTextFont:(id)arg1;
- (void)setConsoleExecutableInputTextFont:(id)arg1;
- (void)setConsoleDebuggerOutputTextFont:(id)arg1;
- (void)setConsoleDebuggerInputTextFont:(id)arg1;
- (void)setConsoleDebuggerPromptTextFont:(id)arg1;
- (void)setConsoleExecutableOutputTextColor:(id)arg1;
- (void)setConsoleExecutableInputTextColor:(id)arg1;
- (void)setConsoleDebuggerOutputTextColor:(id)arg1;
- (void)setConsoleDebuggerInputTextColor:(id)arg1;
- (void)setConsoleDebuggerPromptTextColor:(id)arg1;
- (void)primitiveSetConsoleDebuggerPromptTextColor:(id)arg1;
- (void)setConsoleTextInsertionPointColor:(id)arg1;
- (void)setConsoleTextSelectionColor:(id)arg1;
- (void)setConsoleTextBackgroundColor:(id)arg1;
- (void)setSourceTextInvisiblesColor:(id)arg1;
- (void)setSourceTextInsertionPointColor:(id)arg1;
- (void)setSourceTextSelectionColor:(id)arg1;
- (void)setSourceTextBackgroundColor:(id)arg1;
- (void)_setColorOrFont:(id)arg1 forKey:(id)arg2 colorOrFontivar:(id *)arg3;
@property(readonly) NSColor *debuggerInstructionPointerColor;
@property(readonly) NSFont *consoleExecutableOutputTextFont;
@property(readonly) NSFont *consoleExecutableInputTextFont;
@property(readonly) NSFont *consoleDebuggerOutputTextFont;
@property(readonly) NSFont *consoleDebuggerInputTextFont;
@property(readonly) NSFont *consoleDebuggerPromptTextFont;
@property(readonly) NSColor *consoleExecutableOutputTextColor;
@property(readonly) NSColor *consoleExecutableInputTextColor;
@property(readonly) NSColor *consoleDebuggerOutputTextColor;
@property(readonly) NSColor *consoleDebuggerInputTextColor;
@property(readonly) NSColor *consoleDebuggerPromptTextColor;
@property(readonly) NSColor *consoleTextInsertionPointColor;
@property(readonly) NSColor *consoleTextSecondarySelectionColor;
@property(readonly) NSColor *consoleTextSelectionColor;
@property(readonly) NSColor *consoleTextBackgroundColor;
@property(readonly) NSColor *sourceTextTokenizedBackgroundSelectedColor;
@property(readonly) NSColor *sourceTextTokenizedBorderSelectedColor;
@property(readonly) NSColor *sourceTextTokenizedBackgroundColor;
@property(readonly) NSColor *sourceTextTokenizedBorderColor;
@property(readonly) NSColor *sourceTextLinkColor;
@property(readonly) NSColor *sourceTextCompletionPreviewColor;
@property(readonly) NSColor *sourceTextBlockDimBackgroundColor;
@property(readonly) NSColor *sourceTextInvisiblesColor;
@property(readonly) NSColor *sourceTextInsertionPointColor;
@property(readonly) NSColor *sourceTextSecondarySelectionColor;
@property(readonly) NSColor *sourceTextSelectionColor;
@property(readonly) NSColor *sourceTextFoldbarBackgroundColor;
@property(readonly) NSColor *sourceTextSidebarNumbersColor;
@property(readonly) NSColor *sourceTextSidebarEdgeColor;
@property(readonly) NSColor *sourceTextSidebarBackgroundColor;
@property(readonly) NSColor *sourceTextBackgroundColor;
- (id)description;
@property(readonly) NSString *localizedName;
- (void)_updateHasMultipleSourceTextFonts;
- (void)_updateDerivedColors;
- (BOOL)_loadFontsAndColors;
- (id)dataRepresentationWithError:(id *)arg1;
- (void)primitiveInvalidate;
- (id)initWithCustomDataSpecifier:(id)arg1 basePreferenceSet:(id)arg2;
- (id)initWithName:(id)arg1 dataURL:(id)arg2;
- (id)_initWithName:(id)arg1 syntaxColorsByNodeType:(id)arg2 syntaxFontsByNodeType:(id)arg3;
- (void)_themeCommonInit;
- (id)init;

// Remaining properties
@property(retain) DVTStackBacktrace *creationBacktrace;
@property(readonly) DVTStackBacktrace *invalidationBacktrace;
@property(readonly, nonatomic, getter=isValid) BOOL valid;

@end
