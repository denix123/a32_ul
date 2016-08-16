// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_APP_WEB_CONTENTS_HELPER_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_APP_WEB_CONTENTS_HELPER_H_

#include "content/public/common/console_message_level.h"
#include "content/public/common/media_stream_request.h"

namespace blink {
class WebGestureEvent;
}

namespace content {
class BrowserContext;
struct OpenURLParams;
class WebContents;
}

namespace extensions {

class AppDelegate;
class Extension;

class AppWebContentsHelper {
 public:
  AppWebContentsHelper(content::BrowserContext* browser_context,
                       const std::string& extension_id,
                       content::WebContents* web_contents,
                       AppDelegate* app_delegate);

  
  static bool ShouldSuppressGestureEvent(const blink::WebGestureEvent& event);

  
  content::WebContents* OpenURLFromTab(
      const content::OpenURLParams& params) const;

  
  void RequestToLockMouse() const;

  
  
  void RequestMediaAccessPermission(
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback) const;

  
  
  bool CheckMediaAccessPermission(const GURL& security_origin,
                                  content::MediaStreamType type) const;

 private:
  const Extension* GetExtension() const;

  
  void AddMessageToDevToolsConsole(content::ConsoleMessageLevel level,
                                   const std::string& message) const;

  
  
  content::BrowserContext* browser_context_;

  const std::string extension_id_;

  content::WebContents* web_contents_;

  AppDelegate* app_delegate_;

  DISALLOW_COPY_AND_ASSIGN(AppWebContentsHelper);
};

}  

#endif  
