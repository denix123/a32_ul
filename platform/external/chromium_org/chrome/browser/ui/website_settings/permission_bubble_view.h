// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_VIEW_H_
#define CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_VIEW_H_

#include <vector>

class PermissionBubbleRequest;
class PermissionBubbleManager;

class PermissionBubbleView {
 public:
  
  
  class Delegate {
   public:
    virtual ~Delegate() {}

    virtual void ToggleAccept(int index, bool new_value) = 0;
    virtual void SetCustomizationMode() = 0;
    virtual void Accept() = 0;
    virtual void Deny() = 0;
    virtual void Closing() = 0;
    virtual void SetView(PermissionBubbleView* view) = 0;
  };

  virtual ~PermissionBubbleView() {}

  
  virtual void SetDelegate(Delegate* delegate) = 0;

  
  
  
  
  
  
  virtual void Show(
      const std::vector<PermissionBubbleRequest*>& requests,
      const std::vector<bool>& accept_state,
      bool customization_mode) = 0;

  
  
  
  virtual bool CanAcceptRequestUpdate() = 0;

  
  virtual void Hide() = 0;

  
  virtual bool IsVisible() = 0;
};

#endif  
