// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_URL_FILTER_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_URL_FILTER_H_

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "base/threading/non_thread_safe.h"
#include "base/values.h"
#include "chrome/browser/supervised_user/supervised_user_site_list.h"
#include "chrome/browser/supervised_user/supervised_users.h"

class GURL;
class SupervisedUserBlacklist;

class SupervisedUserURLFilter
    : public base::RefCountedThreadSafe<SupervisedUserURLFilter>,
      public base::NonThreadSafe {
 public:
  enum FilteringBehavior {
    ALLOW,
    WARN,
    BLOCK,
    HISTOGRAM_BOUNDING_VALUE
  };

  class Observer {
   public:
    virtual void OnSiteListUpdated() = 0;
  };

  struct Contents;

  SupervisedUserURLFilter();

  static FilteringBehavior BehaviorFromInt(int behavior_value);

  
  static GURL Normalize(const GURL& url);

  
  
  
  static bool HasFilteredScheme(const GURL& url);

  
  
  
  
  
  
  
  
  
  
  
  
  static bool HostMatchesPattern(const std::string& host,
                                 const std::string& pattern);

  void GetSites(const GURL& url,
                std::vector<SupervisedUserSiteList::Site*>* sites) const;

  
  
  FilteringBehavior GetFilteringBehaviorForURL(const GURL& url) const;

  
  void SetDefaultFilteringBehavior(FilteringBehavior behavior);

  
  
  void LoadWhitelists(ScopedVector<SupervisedUserSiteList> site_lists);

  
  void SetBlacklist(SupervisedUserBlacklist* blacklist);

  
  
  void SetFromPatterns(const std::vector<std::string>& patterns);

  
  void SetManualHosts(const std::map<std::string, bool>* host_map);

  
  void SetManualURLs(const std::map<GURL, bool>* url_map);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  friend class base::RefCountedThreadSafe<SupervisedUserURLFilter>;
  ~SupervisedUserURLFilter();

  void SetContents(scoped_ptr<Contents> url_matcher);

  ObserverList<Observer> observers_;

  FilteringBehavior default_behavior_;
  scoped_ptr<Contents> contents_;

  
  
  std::map<GURL, bool> url_map_;

  
  
  std::map<std::string, bool> host_map_;

  
  SupervisedUserBlacklist* blacklist_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserURLFilter);
};

#endif  
