// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PROFILES_PROFILE_CHOOSER_CONTROLLER_H_
#define CHROME_BROWSER_UI_COCOA_PROFILES_PROFILE_CHOOSER_CONTROLLER_H_

#import <Cocoa/Cocoa.h>
#include <map>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/profiles/profile_metrics.h"
#include "chrome/browser/signin/signin_header_helper.h"
#include "chrome/browser/ui/profile_chooser_constants.h"
#import "chrome/browser/ui/cocoa/base_bubble_controller.h"

class AvatarMenu;
class ActiveProfileObserverBridge;
class Browser;
class ProfileOAuth2TokenService;

namespace content {
class WebContents;
}

@interface ProfileChooserController : BaseBubbleController<NSTextViewDelegate> {
 @private
  
  scoped_ptr<AvatarMenu> avatarMenu_;

  
  
  scoped_ptr<ActiveProfileObserverBridge> observer_;

  
  Browser* browser_;

  
  
  
  std::string accountIdToRemove_;

  
  profiles::BubbleViewMode viewMode_;

  
  profiles::TutorialMode tutorialMode_;

  
  
  
  std::map<int, std::string> currentProfileAccounts_;

  
  scoped_ptr<content::WebContents> webContents_;

  
  BOOL isGuestSession_;

  
  signin::GAIAServiceType serviceType_;
}

- (id)initWithBrowser:(Browser*)browser
           anchoredAt:(NSPoint)point
             viewMode:(profiles::BubbleViewMode)viewMode
         tutorialMode:(profiles::TutorialMode)tutorialMode
          serviceType:(signin::GAIAServiceType)GAIAServiceType;

- (void)initMenuContentsWithView:(profiles::BubbleViewMode)viewToDisplay;

- (profiles::BubbleViewMode)viewMode;

- (void)setTutorialMode:(profiles::TutorialMode)tutorialMode;

- (IBAction)switchToProfile:(id)sender;

- (IBAction)showUserManager:(id)sender;

- (IBAction)exitGuest:(id)sender;

- (IBAction)showAccountManagement:(id)sender;

- (IBAction)hideAccountManagement:(id)sender;

- (IBAction)lockProfile:(id)sender;

- (IBAction)showInlineSigninPage:(id)sender;

- (IBAction)addAccount:(id)sender;

- (IBAction)showAccountRemovalView:(id)sender;

- (IBAction)showAccountReauthenticationView:(id)sender;

- (IBAction)removeAccount:(id)sender;

- (void)cleanUpEmbeddedViewContents;

- (void)postActionPerformed:(ProfileMetrics::ProfileDesktopMenu)action;
@end


@interface ProfileChooserController (ExposedForTesting)
- (id)initWithBrowser:(Browser*)browser
           anchoredAt:(NSPoint)point
             viewMode:(profiles::BubbleViewMode)viewMode
         tutorialMode:(profiles::TutorialMode)tutorialMode
          serviceType:(signin::GAIAServiceType)GAIAServiceType;
@end

#endif  
