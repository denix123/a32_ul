// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_SEARCH_MIXER_H_
#define CHROME_BROWSER_UI_APP_LIST_SEARCH_MIXER_H_

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_vector.h"
#include "chrome/browser/ui/app_list/search/history_types.h"
#include "ui/app_list/app_list_model.h"

namespace app_list {

namespace test {
FORWARD_DECLARE_TEST(MixerTest, Publish);
}

class ChromeSearchResult;
class SearchProvider;

class Mixer {
 public:
  
  
  enum GroupId {
    MAIN_GROUP = 0,
    OMNIBOX_GROUP = 1,
    WEBSTORE_GROUP = 2,
    PEOPLE_GROUP = 3,
  };

  explicit Mixer(AppListModel::SearchResults* ui_results);
  ~Mixer();

  
  void Init();

  
  void AddProviderToGroup(GroupId group, SearchProvider* provider);

  
  void MixAndPublish(const KnownResults& known_results);

 private:
  FRIEND_TEST_ALL_PREFIXES(test::MixerTest, Publish);

  
  struct SortData {
    SortData();
    SortData(ChromeSearchResult* result, double score);

    bool operator<(const SortData& other) const;

    ChromeSearchResult* result;  
    double score;
  };
  typedef std::vector<Mixer::SortData> SortedResults;

  class Group;
  typedef ScopedVector<Group> Groups;

  
  
  
  static void Publish(const SortedResults& results,
                      AppListModel::SearchResults* ui_results);

  
  static void RemoveDuplicates(SortedResults* results);

  void FetchResults(const KnownResults& known_results);

  AppListModel::SearchResults* ui_results_;  
  Groups groups_;

  DISALLOW_COPY_AND_ASSIGN(Mixer);
};

}  

#endif  
