// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_APPCACHE_APPCACHE_H_
#define CONTENT_BROWSER_APPCACHE_APPCACHE_H_

#include <map>
#include <set>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "content/browser/appcache/appcache_database.h"
#include "content/browser/appcache/appcache_entry.h"
#include "content/browser/appcache/appcache_manifest_parser.h"
#include "content/common/content_export.h"
#include "url/gurl.h"

namespace net {
class IOBuffer;
}

namespace content {
FORWARD_DECLARE_TEST(AppCacheTest, InitializeWithManifest);
FORWARD_DECLARE_TEST(AppCacheTest, ToFromDatabaseRecords);
class AppCacheExecutableHandler;
class AppCacheGroup;
class AppCacheHost;
class AppCacheStorage;
class AppCacheTest;
class AppCacheStorageImplTest;
class AppCacheUpdateJobTest;

class CONTENT_EXPORT AppCache
    : public base::RefCounted<AppCache> {
 public:
  typedef std::map<GURL, AppCacheEntry> EntryMap;
  typedef std::set<AppCacheHost*> AppCacheHosts;

  AppCache(AppCacheStorage* storage, int64 cache_id);

  int64 cache_id() const { return cache_id_; }

  AppCacheGroup* owning_group() const { return owning_group_.get(); }

  bool is_complete() const { return is_complete_; }
  void set_complete(bool value) { is_complete_ = value; }

  
  void AddEntry(const GURL& url, const AppCacheEntry& entry);

  
  
  
  bool AddOrModifyEntry(const GURL& url, const AppCacheEntry& entry);

  
  void RemoveEntry(const GURL& url);

  
  AppCacheEntry* GetEntry(const GURL& url);
  const AppCacheEntry* GetEntryWithResponseId(int64 response_id) {
    return GetEntryAndUrlWithResponseId(response_id, NULL);
  }
  const AppCacheEntry* GetEntryAndUrlWithResponseId(
      int64 response_id, GURL* optional_url);
  const EntryMap& entries() const { return entries_; }

  
  
  
  
  
  AppCacheExecutableHandler* GetExecutableHandler(int64 response_id);
  AppCacheExecutableHandler* GetOrCreateExecutableHandler(
      int64 response_id, net::IOBuffer* handler_source);

  
  GURL GetFallbackEntryUrl(const GURL& namespace_url) const {
    return GetNamespaceEntryUrl(fallback_namespaces_, namespace_url);
  }
  GURL GetInterceptEntryUrl(const GURL& namespace_url) const {
    return GetNamespaceEntryUrl(intercept_namespaces_, namespace_url);
  }

  AppCacheHosts& associated_hosts() { return associated_hosts_; }

  bool IsNewerThan(AppCache* cache) const {
    
    
    if (update_time_ > cache->update_time_)
      return true;

    
    if (update_time_ == cache->update_time_)
      return cache_id_ > cache->cache_id_;

    return false;
  }

  base::Time update_time() const { return update_time_; }

  int64 cache_size() const { return cache_size_; }

  void set_update_time(base::Time ticks) { update_time_ = ticks; }

  
  
  void InitializeWithManifest(AppCacheManifest* manifest);

  
  void InitializeWithDatabaseRecords(
      const AppCacheDatabase::CacheRecord& cache_record,
      const std::vector<AppCacheDatabase::EntryRecord>& entries,
      const std::vector<AppCacheDatabase::NamespaceRecord>& intercepts,
      const std::vector<AppCacheDatabase::NamespaceRecord>& fallbacks,
      const std::vector<AppCacheDatabase::OnlineWhiteListRecord>& whitelists);

  
  
  void ToDatabaseRecords(
      const AppCacheGroup* group,
      AppCacheDatabase::CacheRecord* cache_record,
      std::vector<AppCacheDatabase::EntryRecord>* entries,
      std::vector<AppCacheDatabase::NamespaceRecord>* intercepts,
      std::vector<AppCacheDatabase::NamespaceRecord>* fallbacks,
      std::vector<AppCacheDatabase::OnlineWhiteListRecord>* whitelists);

  bool FindResponseForRequest(const GURL& url,
      AppCacheEntry* found_entry, GURL* found_intercept_namespace,
      AppCacheEntry* found_fallback_entry, GURL* found_fallback_namespace,
      bool* found_network_namespace);

  
  void ToResourceInfoVector(AppCacheResourceInfoVector* infos) const;

  static const AppCacheNamespace* FindNamespace(
      const AppCacheNamespaceVector& namespaces,
      const GURL& url);

 private:
  friend class AppCacheGroup;
  friend class AppCacheHost;
  friend class content::AppCacheTest;
  friend class content::AppCacheStorageImplTest;
  friend class content::AppCacheUpdateJobTest;
  friend class base::RefCounted<AppCache>;

  ~AppCache();

  
  void set_owning_group(AppCacheGroup* group) { owning_group_ = group; }

  
  const AppCacheNamespace* FindInterceptNamespace(const GURL& url) {
    return FindNamespace(intercept_namespaces_, url);
  }
  const AppCacheNamespace* FindFallbackNamespace(const GURL& url) {
    return FindNamespace(fallback_namespaces_, url);
  }
  bool IsInNetworkNamespace(const GURL& url) {
    return FindNamespace(online_whitelist_namespaces_, url) != NULL;
  }

  GURL GetNamespaceEntryUrl(const AppCacheNamespaceVector& namespaces,
                            const GURL& namespace_url) const;

  
  void AssociateHost(AppCacheHost* host) {
    associated_hosts_.insert(host);
  }
  void UnassociateHost(AppCacheHost* host);

  const int64 cache_id_;
  scoped_refptr<AppCacheGroup> owning_group_;
  AppCacheHosts associated_hosts_;

  EntryMap entries_;    

  AppCacheNamespaceVector intercept_namespaces_;
  AppCacheNamespaceVector fallback_namespaces_;
  AppCacheNamespaceVector online_whitelist_namespaces_;
  bool online_whitelist_all_;

  bool is_complete_;

  
  base::Time update_time_;

  int64 cache_size_;

  typedef std::map<int64, AppCacheExecutableHandler*> HandlerMap;
  HandlerMap executable_handlers_;

  
  AppCacheStorage* storage_;

  FRIEND_TEST_ALL_PREFIXES(content::AppCacheTest, InitializeWithManifest);
  FRIEND_TEST_ALL_PREFIXES(content::AppCacheTest, ToFromDatabaseRecords);
  DISALLOW_COPY_AND_ASSIGN(AppCache);
};

}  

#endif  
