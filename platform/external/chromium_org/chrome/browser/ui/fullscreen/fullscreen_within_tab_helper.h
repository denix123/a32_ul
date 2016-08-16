// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_FULLSCREEN_FULLSCREEN_WITHIN_TAB_HELPER_H_
#define CHROME_BROWSER_UI_FULLSCREEN_FULLSCREEN_WITHIN_TAB_HELPER_H_

#include "content/public/browser/web_contents_user_data.h"

class FullscreenWithinTabHelper
    : public content::WebContentsUserData<FullscreenWithinTabHelper> {
 public:
  bool is_fullscreen_for_captured_tab() const {
    return is_fullscreen_for_captured_tab_;
  }

  void SetIsFullscreenForCapturedTab(bool is_fullscreen) {
    is_fullscreen_for_captured_tab_ = is_fullscreen;
  }

  
  
  static void RemoveForWebContents(content::WebContents* web_contents);

 private:
  friend class content::WebContentsUserData<FullscreenWithinTabHelper>;
  explicit FullscreenWithinTabHelper(content::WebContents* ignored);
  virtual ~FullscreenWithinTabHelper();

  bool is_fullscreen_for_captured_tab_;

  DISALLOW_COPY_AND_ASSIGN(FullscreenWithinTabHelper);
};

#endif  
