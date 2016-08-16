// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_BROWSER_URL_BLACKLIST_MANAGER_H_
#define COMPONENTS_POLICY_CORE_BROWSER_URL_BLACKLIST_MANAGER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "components/policy/policy_export.h"
#include "components/url_matcher/url_matcher.h"
#include "url/gurl.h"

class PrefService;

namespace base {
class ListValue;
class SequencedTaskRunner;
}

namespace net {
class URLRequest;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace policy {

class POLICY_EXPORT URLBlacklist {
 public:
  
  
  typedef std::string (*SegmentURLCallback)(const std::string&, url::Parsed*);

  explicit URLBlacklist(SegmentURLCallback segment_url);
  virtual ~URLBlacklist();

  
  void AddFilters(bool allow, const base::ListValue* filters);

  
  
  
  void Block(const base::ListValue* filters);

  
  
  void Allow(const base::ListValue* filters);

  
  bool IsURLBlocked(const GURL& url) const;

  
  size_t Size() const;

  
  
  
  
  
  
  
  
  
  
  
  static bool FilterToComponents(SegmentURLCallback segment_url,
                                 const std::string& filter,
                                 std::string* scheme,
                                 std::string* host,
                                 bool* match_subdomains,
                                 uint16* port,
                                 std::string* path,
                                 std::string* query);

  
  
  
  
  static scoped_refptr<url_matcher::URLMatcherConditionSet> CreateConditionSet(
      url_matcher::URLMatcher* url_matcher,
      url_matcher::URLMatcherConditionSet::ID id,
      const std::string& scheme,
      const std::string& host,
      bool match_subdomains,
      uint16 port,
      const std::string& path,
      const std::string& query,
      bool allow);

 private:
  struct FilterComponents;

  
  static bool FilterTakesPrecedence(const FilterComponents& lhs,
                                    const FilterComponents& rhs);

  SegmentURLCallback segment_url_;
  url_matcher::URLMatcherConditionSet::ID id_;
  std::map<url_matcher::URLMatcherConditionSet::ID, FilterComponents> filters_;
  scoped_ptr<url_matcher::URLMatcher> url_matcher_;

  DISALLOW_COPY_AND_ASSIGN(URLBlacklist);
};

class POLICY_EXPORT URLBlacklistManager {
 public:
  
  
  
  typedef base::Callback<bool(const GURL& url, bool* block, int* reason)>
      OverrideBlacklistCallback;

  
  
  
  
  
  URLBlacklistManager(
      PrefService* pref_service,
      const scoped_refptr<base::SequencedTaskRunner>& background_task_runner,
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner,
      URLBlacklist::SegmentURLCallback segment_url,
      OverrideBlacklistCallback override_blacklist);
  virtual ~URLBlacklistManager();

  
  void ShutdownOnUIThread();

  
  
  bool IsURLBlocked(const GURL& url) const;

  
  
  
  
  
  
  
  bool IsRequestBlocked(const net::URLRequest& request, int* reason) const;

  
  
  virtual void SetBlacklist(scoped_ptr<URLBlacklist> blacklist);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

 protected:
  
  
  void ScheduleUpdate();

  
  
  virtual void Update();

  
  
  void UpdateOnIO(scoped_ptr<base::ListValue> block,
                  scoped_ptr<base::ListValue> allow);

 private:
  
  
  

  
  PrefChangeRegistrar pref_change_registrar_;
  PrefService* pref_service_;  

  
  scoped_refptr<base::SequencedTaskRunner> background_task_runner_;

  
  scoped_refptr<base::SequencedTaskRunner> io_task_runner_;

  
  URLBlacklist::SegmentURLCallback segment_url_;

  
  OverrideBlacklistCallback override_blacklist_;

  
  
  

  
  scoped_refptr<base::SequencedTaskRunner> ui_task_runner_;

  
  scoped_ptr<URLBlacklist> blacklist_;

  
  base::WeakPtrFactory<URLBlacklistManager> ui_weak_ptr_factory_;

  
  base::WeakPtrFactory<URLBlacklistManager> io_weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(URLBlacklistManager);
};

}  

#endif  
