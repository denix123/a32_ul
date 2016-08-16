// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_HOST_DELEGATE_H_
#define EXTENSIONS_BROWSER_EXTENSION_HOST_DELEGATE_H_

#include <string>

#include "content/public/common/media_stream_request.h"
#include "ui/base/window_open_disposition.h"

namespace content {
class JavaScriptDialogManager;
class WebContents;
}

namespace gfx {
class Rect;
}

namespace extensions {
class Extension;
class ExtensionHost;

class ExtensionHostDelegate {
 public:
  virtual ~ExtensionHostDelegate() {}

  
  
  virtual void OnExtensionHostCreated(content::WebContents* web_contents) = 0;

  
  virtual void OnRenderViewCreatedForBackgroundPage(ExtensionHost* host) = 0;

  
  
  virtual content::JavaScriptDialogManager* GetJavaScriptDialogManager() = 0;

  
  
  virtual void CreateTab(content::WebContents* web_contents,
                         const std::string& extension_id,
                         WindowOpenDisposition disposition,
                         const gfx::Rect& initial_pos,
                         bool user_gesture) = 0;

  
  
  virtual void ProcessMediaAccessRequest(
      content::WebContents* web_contents,
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback,
      const Extension* extension) = 0;

  
  
  
  virtual bool CheckMediaAccessPermission(content::WebContents* web_contents,
                                          const GURL& security_origin,
                                          content::MediaStreamType type,
                                          const Extension* extension) = 0;
};

}  

#endif  
