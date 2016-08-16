// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_ENGINES_DEFAULT_SEARCH_PREF_MIGRATION_H_
#define CHROME_BROWSER_SEARCH_ENGINES_DEFAULT_SEARCH_PREF_MIGRATION_H_

class PrefService;

void ConfigureDefaultSearchPrefMigrationToDictionaryValue(
    PrefService* pref_service);

#endif  
