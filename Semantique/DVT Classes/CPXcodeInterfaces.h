//
//  CPXcodeInterfaces.h
//  CodePilot
//
//  Created by Zbigniew Sobiecki on 3/24/10.
//  Copyright 2010 Macoscope. All rights reserved.
//
//  Take from CodePilot: https://github.com/macoscope/CodePilot
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

@interface DVTAutoLayoutView : NSView
@end

@interface DVTReplacementView : DVTAutoLayoutView
@end

@interface IDEPreferencesController : NSWindowController <NSToolbarDelegate>
- (void)setPaneReplacementView:(DVTReplacementView *)replacementView;
- (DVTReplacementView *)paneReplacementView;
@end

@interface DVTExtension : NSObject
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
