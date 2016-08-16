// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_TAB_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_TAB_UTIL_H_

#include <string>

#include "base/callback.h"
#include "ui/base/window_open_disposition.h"

class Browser;
class ChromeExtensionFunctionDetails;
class ChromeUIThreadExtensionFunction;
class ExtensionFunction;
class GURL;
class Profile;
class TabStripModel;

namespace base {
class DictionaryValue;
class ListValue;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace gfx {
class Rect;
}

namespace extensions {

class Extension;
class WindowController;

namespace api {
namespace tabs {
struct Tab;
}
}

class ExtensionTabUtil {
 public:
  struct OpenTabParams {
    OpenTabParams();
    ~OpenTabParams();

    bool create_browser_if_needed;
    scoped_ptr<int> window_id;
    scoped_ptr<int> opener_tab_id;
    scoped_ptr<std::string> url;
    scoped_ptr<bool> active;
    scoped_ptr<bool> pinned;
    scoped_ptr<int> index;
  };

  
  
  
  static base::DictionaryValue* OpenTab(
      ChromeUIThreadExtensionFunction* function,
      const OpenTabParams& params,
      std::string* error);

  static int GetWindowId(const Browser* browser);
  static int GetWindowIdOfTabStripModel(const TabStripModel* tab_strip_model);
  static int GetTabId(const content::WebContents* web_contents);
  static std::string GetTabStatusText(bool is_loading);
  static int GetWindowIdOfTab(const content::WebContents* web_contents);
  static base::ListValue* CreateTabList(const Browser* browser,
                                        const Extension* extension);

  
  
  
  static Browser* GetBrowserFromWindowID(
      ChromeUIThreadExtensionFunction* function,
      int window_id,
      std::string* error_message);

  static Browser* GetBrowserFromWindowID(
      const ChromeExtensionFunctionDetails& details,
      int window_id,
      std::string* error_message);

  
  
  
  
  static base::DictionaryValue* CreateTabValue(
      content::WebContents* web_contents,
      const Extension* extension) {
    return CreateTabValue(web_contents, NULL, -1, extension);
  }
  static base::DictionaryValue* CreateTabValue(
      content::WebContents* web_contents,
      TabStripModel* tab_strip,
      int tab_index,
      const Extension* extension);

  
  
  static base::DictionaryValue* CreateTabValue(
      content::WebContents* web_contents) {
    return CreateTabValue(web_contents, NULL, -1);
  }
  static base::DictionaryValue* CreateTabValue(
      content::WebContents* web_contents,
      TabStripModel* tab_strip,
      int tab_index);

  
  
  
  static void ScrubTabValueForExtension(content::WebContents* contents,
                                        const Extension* extension,
                                        base::DictionaryValue* tab_info);

  
  
  static void ScrubTabForExtension(const Extension* extension,
                                   api::tabs::Tab* tab);

  
  static bool GetTabStripModel(const content::WebContents* web_contents,
                               TabStripModel** tab_strip_model,
                               int* tab_index);
  static bool GetDefaultTab(Browser* browser,
                            content::WebContents** contents,
                            int* tab_id);
  
  
  static bool GetTabById(int tab_id,
                         content::BrowserContext* browser_context,
                         bool incognito_enabled,
                         Browser** browser,
                         TabStripModel** tab_strip,
                         content::WebContents** contents,
                         int* tab_index);

  
  
  
  
  
  
  
  
  static GURL ResolvePossiblyRelativeURL(const std::string& url_string,
                                         const Extension* extension);

  
  static bool IsCrashURL(const GURL& url);

  
  static void CreateTab(content::WebContents* web_contents,
                        const std::string& extension_id,
                        WindowOpenDisposition disposition,
                        const gfx::Rect& initial_pos,
                        bool user_gesture);

  
  static void ForEachTab(
      const base::Callback<void(content::WebContents*)>& callback);

  static WindowController* GetWindowControllerOfTab(
      const content::WebContents* web_contents);

  
  static void OpenOptionsPage(const Extension* extension, Browser* browser);
};

}  

#endif  
