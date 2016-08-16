// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_WEB_CONTENTS_OBSERVER_H_
#define EXTENSIONS_BROWSER_EXTENSION_WEB_CONTENTS_OBSERVER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {
class BrowserContext;
class RenderViewHost;
class WebContents;
}

namespace extensions {
class Extension;

class ExtensionWebContentsObserver : public content::WebContentsObserver {
 protected:
  explicit ExtensionWebContentsObserver(content::WebContents* web_contents);
  virtual ~ExtensionWebContentsObserver();

  content::BrowserContext* browser_context() { return browser_context_; }

  

  
  virtual void RenderViewCreated(content::RenderViewHost* render_view_host)
      OVERRIDE;

  
  
  const Extension* GetExtension(content::RenderViewHost* render_view_host);

  
  void NotifyRenderViewType(content::RenderViewHost* render_view_host);

  
  
  static std::string GetExtensionId(content::RenderViewHost* render_view_host);

 private:
  
  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionWebContentsObserver);
};

}  

#endif  
