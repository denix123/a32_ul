// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_BROWSER_UI_PREFS_MIGRATOR_H_
#define CHROME_BROWSER_PREFS_BROWSER_UI_PREFS_MIGRATOR_H_

#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_store.h"
#include "base/prefs/writeable_pref_store.h"


class BrowserUIPrefsMigrator : public PrefStore::Observer {
 public:
  explicit BrowserUIPrefsMigrator(WriteablePrefStore* pref_store);

  
  virtual void OnPrefValueChanged(const std::string& key) OVERRIDE {}
  virtual void OnInitializationCompleted(bool succeeded) OVERRIDE;

 private:
  friend struct base::DefaultDeleter<BrowserUIPrefsMigrator>;

  virtual ~BrowserUIPrefsMigrator();

  WriteablePrefStore* pref_store_;

  DISALLOW_COPY_AND_ASSIGN(BrowserUIPrefsMigrator);
};

#endif  
