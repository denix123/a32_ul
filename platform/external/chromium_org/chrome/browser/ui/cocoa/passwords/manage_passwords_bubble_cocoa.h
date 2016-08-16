// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_COCOA_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#import "chrome/browser/ui/passwords/manage_passwords_bubble.h"

namespace content {
class WebContents;
}

namespace chrome {
void ShowManagePasswordsBubble(content::WebContents* webContents);
}

@class ManagePasswordsBubbleController;
@class ManagePasswordsBubbleCocoaNotificationBridge;
class ManagePasswordsIcon;

class ManagePasswordsBubbleCocoa : public ManagePasswordsBubble {
 public:
  
  
  static void ShowBubble(content::WebContents* webContents,
                         DisplayReason displayReason,
                         ManagePasswordsIcon* icon);

  
  void Close();

  
  void SetIcon(ManagePasswordsIcon* icon) { icon_ = icon; }

  
  static ManagePasswordsBubbleCocoa* instance() { return bubble_; }

 private:
  friend class ManagePasswordsBubbleCocoaTest;
  friend class ManagePasswordsBubbleTest;
  friend void chrome::ShowManagePasswordsBubble(
      content::WebContents* webContents);

  
  ManagePasswordsBubbleCocoa(content::WebContents* webContents,
                             DisplayReason displayReason,
                             ManagePasswordsIcon* icon);
  virtual ~ManagePasswordsBubbleCocoa();
  void Show();

  
  void OnClose();

  
  ManagePasswordsIcon* icon_;

  
  
  bool closing_;

  
  
  ManagePasswordsBubbleController* controller_;

  
  content::WebContents* webContents_;

  
  base::scoped_nsobject<ManagePasswordsBubbleCocoaNotificationBridge> bridge_;

  
  static ManagePasswordsBubbleCocoa* bubble_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsBubbleCocoa);
};

#endif  
