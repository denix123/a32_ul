// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILE_RESETTER_RESETTABLE_SETTINGS_SNAPSHOT_H_
#define CHROME_BROWSER_PROFILE_RESETTER_RESETTABLE_SETTINGS_SNAPSHOT_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string_split.h"
#include "chrome/browser/prefs/session_startup_pref.h"
#include "chrome/browser/profile_resetter/profile_resetter.h"

namespace base {
class ListValue;
}

class ResettableSettingsSnapshot {
 public:
  
  
  typedef base::StringPairs ExtensionList;
  
  enum Field {
    STARTUP_MODE = 1 << 0,
    HOMEPAGE = 1 << 1,
    DSE_URL = 1 << 2,
    EXTENSIONS = 1 << 3,
    SHORTCUTS = 1 << 4,

    ALL_FIELDS = STARTUP_MODE | HOMEPAGE | DSE_URL | EXTENSIONS | SHORTCUTS,
  };

  explicit ResettableSettingsSnapshot(Profile* profile);
  ~ResettableSettingsSnapshot();

  
  const std::vector<GURL>& startup_urls() const { return startup_.urls; }

  SessionStartupPref::Type startup_type() const { return startup_.type; }

  const std::string& homepage() const { return homepage_; }

  bool homepage_is_ntp() const { return homepage_is_ntp_; }

  bool show_home_button() const { return show_home_button_; }

  const std::string& dse_url() const { return dse_url_; }

  const ExtensionList& enabled_extensions() const {
    return enabled_extensions_;
  }

  const std::vector<ShortcutCommand>& shortcuts() const {
    return shortcuts_;
  }

  bool shortcuts_determined() const {
    return shortcuts_determined_;
  }

  
  
  void Subtract(const ResettableSettingsSnapshot& snapshot);

  
  
  
  
  
  int FindDifferentFields(const ResettableSettingsSnapshot& snapshot) const;

  
  
  void RequestShortcuts(const base::Closure& callback);

 private:
  
  void SetShortcutsAndReport(
      const base::Closure& callback,
      const std::vector<ShortcutCommand>& shortcuts);

  
  SessionStartupPref startup_;

  std::string homepage_;
  bool homepage_is_ntp_;
  bool show_home_button_;

  
  std::string dse_url_;

  
  ExtensionList enabled_extensions_;

  
  
  std::vector<ShortcutCommand> shortcuts_;

  
  bool shortcuts_determined_;

  
  scoped_refptr<SharedCancellationFlag> cancellation_flag_;

  base::WeakPtrFactory<ResettableSettingsSnapshot> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ResettableSettingsSnapshot);
};

enum SnapshotCaller {
  PROFILE_RESET_WEBUI = 0,
  PROFILE_RESET_PROMPT,
};

std::string SerializeSettingsReport(const ResettableSettingsSnapshot& snapshot,
                                    int field_mask);

void SendSettingsFeedback(const std::string& report,
                          Profile* profile,
                          SnapshotCaller caller);

scoped_ptr<base::ListValue> GetReadableFeedbackForSnapshot(
    Profile* profile,
    const ResettableSettingsSnapshot& snapshot);

#endif  
