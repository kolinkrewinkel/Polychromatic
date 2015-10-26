//
//  PLYFirstRunManager.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 10/26/15.
//  Copyright © 2015 Kolin Krewinkel. All rights reserved.
//

extern NSString *kPLYHasCompletedFirstRunKey;

@interface PLYFirstRunManager : NSObject

/**
 * Only shows the first run flow if it hasn't been shown before.
 */
- (void)showFirstRunFlowIfNeeded;

/**
 * For re-installation purposes, you can re-run the flow (from the menu item, mainly).
 */
- (void)showFirstRunFlow;

@end
