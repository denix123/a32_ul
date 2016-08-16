// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BROWSER_VIEW_PREFS_H_
#define CHROME_BROWSER_UI_BROWSER_VIEW_PREFS_H_

class PrefRegistrySimple;
class PrefService;

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chrome {

void RegisterBrowserViewLocalPrefs(PrefRegistrySimple* registry);

void RegisterBrowserViewProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry);

void MigrateBrowserTabStripPrefs(PrefService* pref);

}  

#endif  
