// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_SETTINGS_WINDOW_MANAGER_H_
#define CHROME_BROWSER_UI_SETTINGS_WINDOW_MANAGER_H_

#include <map>
#include <string>

#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "components/sessions/session_id.h"

class Browser;
class GURL;
class Profile;

namespace chrome {

class SettingsWindowManagerObserver;


class SettingsWindowManager {
 public:
  static SettingsWindowManager* GetInstance();

  void AddObserver(SettingsWindowManagerObserver* observer);
  void RemoveObserver(SettingsWindowManagerObserver* observer);

  
  
  void ShowChromePageForProfile(Profile* profile, const GURL& gurl);

  
  
  Browser* FindBrowserForProfile(Profile* profile);

  
  bool IsSettingsBrowser(Browser* browser) const;

 private:
  friend struct DefaultSingletonTraits<SettingsWindowManager>;
  typedef std::map<Profile*, SessionID::id_type> ProfileSessionMap;

  SettingsWindowManager();
  ~SettingsWindowManager();

  ObserverList<SettingsWindowManagerObserver> observers_;
  ProfileSessionMap settings_session_map_;

  DISALLOW_COPY_AND_ASSIGN(SettingsWindowManager);
};

}  

#endif  
