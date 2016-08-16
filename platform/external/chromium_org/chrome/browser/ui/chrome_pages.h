// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_CHROME_PAGES_H_
#define CHROME_BROWSER_UI_CHROME_PAGES_H_

#include <string>

#include "chrome/browser/signin/signin_promo.h"
#include "chrome/browser/ui/host_desktop.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "url/gurl.h"

class Browser;

namespace content {
class WebContents;
}

namespace chrome {

enum HelpSource {
  
  HELP_SOURCE_KEYBOARD,

  
  HELP_SOURCE_MENU,

  
  HELP_SOURCE_WEBUI,
};


void ShowBookmarkManager(Browser* browser);
void ShowBookmarkManagerForNode(Browser* browser, int64 node_id);
void ShowHistory(Browser* browser);
void ShowDownloads(Browser* browser);
void ShowExtensions(Browser* browser,
                    const std::string& extension_to_highlight);
void ShowConflicts(Browser* browser);

void ShowFeedbackPage(Browser* browser,
                      const std::string& description_template,
                      const std::string& category_tag);

void ShowHelp(Browser* browser, HelpSource source);
void ShowHelpForProfile(Profile* profile,
                        HostDesktopType host_desktop_type,
                        HelpSource source);
void ShowPolicy(Browser* browser);
void ShowSlow(Browser* browser);

GURL GetSettingsUrl(const std::string& sub_page);

bool IsTrustedPopupWindowWithScheme(const Browser* browser,
                                    const std::string& scheme);

void ShowSettings(Browser* browser);
void ShowSettingsSubPage(Browser* browser, const std::string& sub_page);
void ShowSettingsSubPageForProfile(Profile* profile,
                                   const std::string& sub_page);
void ShowContentSettings(Browser* browser,
                         ContentSettingsType content_settings_type);
void ShowSettingsSubPageInTabbedBrowser(Browser* browser,
                                        const std::string& sub_page);
void ShowClearBrowsingDataDialog(Browser* browser);
void ShowPasswordManager(Browser* browser);
void ShowImportDialog(Browser* browser);
void ShowAboutChrome(Browser* browser);
void ShowSearchEngineSettings(Browser* browser);
void ShowBrowserSignin(Browser* browser, signin::Source source);

}  

#endif  
