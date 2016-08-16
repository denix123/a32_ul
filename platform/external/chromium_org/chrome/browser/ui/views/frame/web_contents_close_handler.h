// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_WEB_CONTENTS_CLOSE_HANDLER_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_WEB_CONTENTS_CLOSE_HANDLER_H_

#include "base/timer/timer.h"

class WebContentsCloseHandlerDelegate;
class WebContentsCloseHandlerTest;

class WebContentsCloseHandler {
 public:
  explicit WebContentsCloseHandler(WebContentsCloseHandlerDelegate* delegate);
  ~WebContentsCloseHandler();

  
  void TabInserted();

  
  void ActiveTabChanged();

  
  void WillCloseAllTabs();

  
  void CloseAllTabsCanceled();

 private:
  friend class WebContentsCloseHandlerTest;

  
  
  void OnStillHaventClosed();

  WebContentsCloseHandlerDelegate* delegate_;

  
  bool in_close_;

  
  
  bool tab_changed_after_clone_;

  base::OneShotTimer<WebContentsCloseHandler> timer_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsCloseHandler);
};

#endif  
