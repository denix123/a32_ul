// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_PROFILES_USER_MANAGER_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_PROFILES_USER_MANAGER_VIEW_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/profile_window.h"
#include "ui/views/window/dialog_delegate.h"

class AutoKeepAlive;

namespace views {
class WebView;
}

class UserManagerView : public views::DialogDelegateView {
 public:
  
  UserManagerView();

  
  
  static void OnGuestProfileCreated(scoped_ptr<UserManagerView> instance,
                                    const base::FilePath& profile_path_to_focus,
                                    Profile* guest_profile,
                                    const std::string& url);

 private:
  virtual ~UserManagerView();

  friend struct base::DefaultDeleter<UserManagerView>;

  
  void Init(const base::FilePath& profile_path_to_focus,
            Profile* guest_profile,
            const GURL& url);

  
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

  
  virtual bool CanResize() const OVERRIDE;
  virtual bool CanMaximize() const OVERRIDE;
  virtual bool CanMinimize() const OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual int GetDialogButtons() const OVERRIDE;
  virtual void WindowClosing() OVERRIDE;
  virtual bool UseNewStyleForThisDialog() const OVERRIDE;

  views::WebView* web_view_;

  scoped_ptr<AutoKeepAlive> keep_alive_;

  DISALLOW_COPY_AND_ASSIGN(UserManagerView);
};

#endif  
