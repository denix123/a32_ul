// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_DECLARATIVE_CONTENT_CONTENT_RULES_REGISTRY_H__
#define EXTENSIONS_BROWSER_API_DECLARATIVE_CONTENT_CONTENT_RULES_REGISTRY_H__

#include <string>

#include "content/public/browser/browser_thread.h"
#include "extensions/browser/api/declarative/rules_registry.h"

namespace content {
class BrowserContext;
class WebContents;
struct FrameNavigateParams;
struct LoadCommittedDetails;
}

namespace extensions {

class ContentRulesRegistry : public RulesRegistry {
 public:
  ContentRulesRegistry(content::BrowserContext* browser_context,
                       const std::string& event_name,
                       content::BrowserThread::ID owner_thread,
                       RulesCacheDelegate* cache_delegate,
                       const WebViewKey& webview_key)
      : RulesRegistry(browser_context,
                      event_name,
                      owner_thread,
                      cache_delegate,
                      webview_key) {}

  
  
  virtual void Apply(
      content::WebContents* contents,
      const std::vector<std::string>& matching_css_selectors) = 0;

  
  virtual void DidNavigateMainFrame(
      content::WebContents* tab,
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) = 0;

 protected:
  virtual ~ContentRulesRegistry() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(ContentRulesRegistry);
};

}  

#endif  
