// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BOOKMARKS_ENHANCED_BOOKMARKS_FEATURES_H_
#define CHROME_BROWSER_BOOKMARKS_ENHANCED_BOOKMARKS_FEATURES_H_

#include <string>

#include "extensions/common/extension.h"

namespace about_flags {
class FlagsStorage;
}  

class PrefService;
class Profile;

enum BookmarksExperimentState {
  BOOKMARKS_EXPERIMENT_NONE,
  BOOKMARKS_EXPERIMENT_ENABLED,
  BOOKMARKS_EXPERIMENT_ENABLED_USER_OPT_OUT,
  BOOKMARKS_EXPERIMENT_ENABLED_FROM_FINCH,
  BOOKMARKS_EXPERIMENT_OPT_OUT_FROM_FINCH,
  BOOKMARKS_EXPERIMENT_ENABLED_FROM_FINCH_USER_SIGNEDIN,
  BOOKMARKS_EXPERIMENT_ENABLED_FROM_SYNC_UNKNOWN,
  BOOKMARKS_EXPERIMENT_ENUM_SIZE
};

bool GetBookmarksExperimentExtensionID(const PrefService* user_prefs,
                                       std::string* extension_id);

void UpdateBookmarksExperimentState(
    PrefService* user_prefs,
    PrefService* local_state,
    bool user_signed_in,
    BookmarksExperimentState experiment_enabled_from_sync);

void InitBookmarksExperimentState(Profile* profile);

void ForceFinchBookmarkExperimentIfNeeded(
    PrefService* local_state,
    BookmarksExperimentState bookmarks_experiment_state);

bool IsEnhancedBookmarksExperimentEnabled(
    about_flags::FlagsStorage* flags_storage);

#if defined(OS_ANDROID)
bool IsEnhancedBookmarkImageFetchingEnabled(const PrefService* user_prefs);

bool IsEnhancedBookmarksEnabled(const PrefService* user_prefs);

#endif

bool IsEnableDomDistillerSet();

bool IsEnableSyncArticlesSet();

#endif  
