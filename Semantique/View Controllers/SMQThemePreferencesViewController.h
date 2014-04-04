//
//  SMQThemePreferencesViewController.h
//  Semantique
//
//  Created by Kolin Krewinkel on 3/31/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface SMQThemePreferencesViewController : IDEViewController <NSTableViewDataSource, NSTableViewDelegate>

@property (nonatomic, strong) IBOutlet NSTableView *themesTableView;

@property (nonatomic, strong) IBOutlet NSScrollView *themeDetailsScrollView;
@property (nonatomic, strong) IBOutlet NSView *themeDetailsView;

#pragma mark - Sizing

- (CGFloat)preferredContentHeight;

@end
