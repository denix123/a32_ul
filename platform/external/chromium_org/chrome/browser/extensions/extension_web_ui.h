// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_WEB_UI_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_WEB_UI_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/common/extensions/manifest_url_handler.h"
#include "components/favicon_base/favicon_callback.h"
#include "content/public/browser/web_ui_controller.h"

class Profile;

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class BookmarkManagerPrivateDragEventRouter;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class ExtensionWebUI : public content::WebUIController {
 public:
  static const char kExtensionURLOverrides[];

  ExtensionWebUI(content::WebUI* web_ui, const GURL& url);

  virtual ~ExtensionWebUI();

  virtual extensions::BookmarkManagerPrivateDragEventRouter*
      bookmark_manager_private_drag_event_router();

  
  static bool HandleChromeURLOverride(GURL* url,
                                      content::BrowserContext* browser_context);
  static bool HandleChromeURLOverrideReverse(
      GURL* url, content::BrowserContext* browser_context);

  
  
  
  static void RegisterChromeURLOverrides(Profile* profile,
      const extensions::URLOverrides::URLOverrideMap& overrides);
  static void UnregisterChromeURLOverrides(Profile* profile,
      const extensions::URLOverrides::URLOverrideMap& overrides);
  static void UnregisterChromeURLOverride(const std::string& page,
                                          Profile* profile,
                                          const base::Value* override);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  static void GetFaviconForURL(
      Profile* profile,
      const GURL& page_url,
      const favicon_base::FaviconResultsCallback& callback);

 private:
  
  
  static void UnregisterAndReplaceOverride(const std::string& page,
                                           Profile* profile,
                                           base::ListValue* list,
                                           const base::Value* override);

  
  
  scoped_ptr<extensions::BookmarkManagerPrivateDragEventRouter>
      bookmark_manager_private_drag_event_router_;

  
  GURL url_;
};

#endif  
