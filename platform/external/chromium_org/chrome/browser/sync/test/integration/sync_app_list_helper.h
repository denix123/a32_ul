// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_SYNC_APP_LIST_HELPER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_SYNC_APP_LIST_HELPER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "sync/api/string_ordinal.h"

class Profile;
class SyncTest;

namespace app_list {
class AppListItem;
}

class SyncAppListHelper {
 public:
  
  static SyncAppListHelper* GetInstance();

  
  
  void SetupIfNecessary(SyncTest* test);

  
  
  bool AllProfilesHaveSameAppListAsVerifier();

  
  void MoveApp(Profile* profile, size_t from, size_t to);

  
  void MoveAppToFolder(Profile* profile,
                       size_t index,
                       const std::string& folder_id);

  
  void MoveAppFromFolder(Profile* profile,
                         size_t index_in_folder,
                         const std::string& folder_id);

  
  void CopyOrdinalsToVerifier(Profile* profile1, const std::string& id);

  
  void PrintAppList(Profile* profile);

 private:
  friend struct DefaultSingletonTraits<SyncAppListHelper>;

  SyncAppListHelper();
  ~SyncAppListHelper();

  
  
  bool AppListMatchesVerifier(Profile* profile);

  
  
  void PrintItem(Profile* profile,
                 app_list::AppListItem* item,
                 const std::string& label);

  SyncTest* test_;
  bool setup_completed_;

  DISALLOW_COPY_AND_ASSIGN(SyncAppListHelper);
};

#endif  
