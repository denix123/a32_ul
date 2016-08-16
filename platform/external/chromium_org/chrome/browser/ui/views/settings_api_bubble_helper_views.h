// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_SETTINGS_API_BUBBLE_HELPER_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_SETTINGS_API_BUBBLE_HELPER_VIEWS_H_

struct AutocompleteMatch;
class Browser;
class Profile;

namespace content {
class WebContents;
}

namespace extensions {

void MaybeShowExtensionControlledHomeNotification(Browser* browser);

void MaybeShowExtensionControlledSearchNotification(
    Profile* profile,
    content::WebContents* web_contents,
    const AutocompleteMatch& match);

void MaybeShowExtensionControlledNewTabPage(
    Browser* browser,
    content::WebContents* web_contents);

}  

#endif  
