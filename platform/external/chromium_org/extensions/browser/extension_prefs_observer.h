// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_PREFS_OBSERVER_H_
#define EXTENSIONS_BROWSER_EXTENSION_PREFS_OBSERVER_H_

#include <string>

#include "base/time/time.h"

namespace extensions {

class ExtensionPrefs;

class ExtensionPrefsObserver {
 public:
  
  virtual void OnExtensionDisableReasonsChanged(const std::string& extension_id,
                                                int disabled_reasons) {}

  
  virtual void OnExtensionRegistered(const std::string& extension_id,
                                     const base::Time& install_time,
                                     bool is_enabled) {}

  
  virtual void OnExtensionPrefsLoaded(const std::string& extension_id,
                                      const ExtensionPrefs* prefs) {}

  
  virtual void OnExtensionPrefsDeleted(const std::string& extension_id) {}

  
  virtual void OnExtensionStateChanged(const std::string& extension_id,
                                       bool state) {}
};

}  

#endif  
