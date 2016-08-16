// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCES_MIGRATION_H_
#define CHROME_BROWSER_PREFS_TRACKED_TRACKED_PREFERENCES_MIGRATION_H_

#include <set>
#include <string>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/prefs/pref_hash_store.h"

class HashStoreContents;
class InterceptablePrefFilter;
class PrefHashStore;

void SetupTrackedPreferencesMigration(
    const std::set<std::string>& unprotected_pref_names,
    const std::set<std::string>& protected_pref_names,
    const base::Callback<void(const std::string& key)>&
        unprotected_store_cleaner,
    const base::Callback<void(const std::string& key)>& protected_store_cleaner,
    const base::Callback<void(const base::Closure&)>&
        register_on_successful_unprotected_store_write_callback,
    const base::Callback<void(const base::Closure&)>&
        register_on_successful_protected_store_write_callback,
    scoped_ptr<PrefHashStore> unprotected_pref_hash_store,
    scoped_ptr<PrefHashStore> protected_pref_hash_store,
    scoped_ptr<HashStoreContents> legacy_pref_hash_store,
    InterceptablePrefFilter* unprotected_pref_filter,
    InterceptablePrefFilter* protected_pref_filter);

#endif  
