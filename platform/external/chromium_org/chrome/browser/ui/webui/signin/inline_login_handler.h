// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_SIGNIN_INLINE_LOGIN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_SIGNIN_INLINE_LOGIN_HANDLER_H_

#include "content/public/browser/web_ui_message_handler.h"

class InlineLoginHandler : public content::WebUIMessageHandler {
 public:
  InlineLoginHandler();
  virtual ~InlineLoginHandler();

  
  virtual void RegisterMessages() OVERRIDE;

 protected:
  
  
  enum AuthMode {
    kDefaultAuthMode = 0,
    kOfflineAuthMode = 1,
    kDesktopAuthMode = 2
  };

 private:
  
  
  void HandleInitializeMessage(const base::ListValue* args);
  
  
  void HandleCompleteLoginMessage(const base::ListValue* args);

  
  void HandleSwitchToFullTabMessage(const base::ListValue* args);

  virtual void SetExtraInitParams(base::DictionaryValue& params) {}
  virtual void CompleteLogin(const base::ListValue* args) = 0;

  DISALLOW_COPY_AND_ASSIGN(InlineLoginHandler);
};

#endif  
