// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_DRIVE_DRIVE_APP_MAPPING_H_
#define CHROME_BROWSER_APPS_DRIVE_DRIVE_APP_MAPPING_H_

#include <set>
#include <string>

#include "base/macros.h"

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefService;

class DriveAppMapping {
 public:
  explicit DriveAppMapping(PrefService* prefs);
  ~DriveAppMapping();

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  void Add(const std::string& drive_app_id,
           const std::string& chrome_app_id,
           bool generated);
  void Remove(const std::string& drive_app_id);

  std::string GetChromeApp(const std::string& drive_app_id) const;
  std::string GetDriveApp(const std::string& chrome_app_id) const;
  bool IsChromeAppGenerated(const std::string& chrome_app_id) const;

  std::set<std::string> GetDriveAppIds() const;

 private:
  PrefService* prefs_;

  DISALLOW_COPY_AND_ASSIGN(DriveAppMapping);
};

#endif  
