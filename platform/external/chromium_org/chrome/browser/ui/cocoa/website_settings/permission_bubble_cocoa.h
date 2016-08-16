// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PERMISSION_BUBBLE_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_PERMISSION_BUBBLE_COCOA_H_

#include "base/mac/scoped_nsobject.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/website_settings/permission_bubble_view.h"
#include "content/public/browser/web_contents.h"

#ifdef __OBJC__
@class PermissionBubbleController;
#else
class PermissionBubbleController;
#endif

class PermissionBubbleCocoa : public PermissionBubbleView {
 public:
  explicit PermissionBubbleCocoa(NSWindow* parent_window);
  virtual ~PermissionBubbleCocoa();

  
  virtual void Show(const std::vector<PermissionBubbleRequest*>& requests,
                    const std::vector<bool>& accept_state,
                    bool customization_mode) OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual bool IsVisible() OVERRIDE;
  virtual void SetDelegate(Delegate* delegate) OVERRIDE;
  virtual bool CanAcceptRequestUpdate() OVERRIDE;

  
  void OnBubbleClosing();

  
  
  NSPoint GetAnchorPoint();

  
  NSWindow* window();

private:
  NSWindow* parent_window_;  
  Delegate* delegate_;  

  
  PermissionBubbleController* bubbleController_;

  DISALLOW_COPY_AND_ASSIGN(PermissionBubbleCocoa);
};

#endif  
