// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UPDATER_LOCAL_EXTENSION_CACHE_H_
#define CHROME_BROWSER_EXTENSIONS_UPDATER_LOCAL_EXTENSION_CACHE_H_

#include <map>
#include <string>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"

namespace extensions {

class LocalExtensionCache {
 public:
  
  typedef base::Callback<void(const base::FilePath& file_path,
                              bool file_ownership_passed)> PutExtensionCallback;

  
  
  
  
  
  LocalExtensionCache(const base::FilePath& cache_dir,
                      uint64 max_cache_size,
                      const base::TimeDelta& max_cache_age,
                      const scoped_refptr<base::SequencedTaskRunner>&
                          backend_task_runner);
  ~LocalExtensionCache();

  
  static const char kCacheReadyFlagFileName[];

  
  
  
  
  void Init(bool wait_for_cache_initialization,
            const base::Closure& callback);

  
  
  void Shutdown(const base::Closure& callback);

  
  
  
  bool GetExtension(const std::string& id,
                    base::FilePath* file_path,
                    std::string* version);

  
  
  
  
  
  void PutExtension(const std::string& id,
                    const base::FilePath& file_path,
                    const std::string& version,
                    const PutExtensionCallback& callback);

  
  
  bool RemoveExtension(const std::string& id);

  
  bool GetStatistics(uint64* cache_size,
                     size_t* extensions_count);

  bool is_ready() const { return state_ == kReady; }
  bool is_uninitialized() const { return state_ == kUninitialized; }
  bool is_shutdown() const { return state_ == kShutdown; }

  
  void SetCacheStatusPollingDelayForTests(const base::TimeDelta& delay);

 private:
  struct CacheItemInfo {
    std::string version;
    base::Time last_used;
    uint64 size;
    base::FilePath file_path;

    CacheItemInfo(const std::string& version,
                  const base::Time& last_used,
                  uint64 size,
                  const base::FilePath& file_path);
  };
  typedef std::map<std::string, CacheItemInfo> CacheMap;

  enum State {
    kUninitialized,
    kWaitInitialization,
    kReady,
    kShutdown
  };

  
  void CheckCacheStatus(const base::Closure& callback);

  
  
  
  static void BackendCheckCacheStatus(
      base::WeakPtr<LocalExtensionCache> local_cache,
      const base::FilePath& cache_dir,
      const base::Closure& callback);

  
  
  
  void OnCacheStatusChecked(bool ready, const base::Closure& callback);

  
  
  void CheckCacheContents(const base::Closure& callback);

  
  
  
  static void BackendCheckCacheContents(
      base::WeakPtr<LocalExtensionCache> local_cache,
      const base::FilePath& cache_dir,
      const base::Closure& callback);

  
  static void BackendCheckCacheContentsInternal(
      const base::FilePath& cache_dir,
      CacheMap* cache_content);

  
  
  void OnCacheContentsChecked(scoped_ptr<CacheMap> cache_content,
                              const base::Closure& callback);

  
  
  static void BackendMarkFileUsed(const base::FilePath& file_path,
                                  const base::Time& time);

  
  
  static void BackendInstallCacheEntry(
      base::WeakPtr<LocalExtensionCache> local_cache,
      const base::FilePath& cache_dir,
      const std::string& id,
      const base::FilePath& file_path,
      const std::string& version,
      const PutExtensionCallback& callback);

  
  void OnCacheEntryInstalled(const std::string& id,
                             const CacheItemInfo& info,
                             bool was_error,
                             const PutExtensionCallback& callback);

  
  
  static void BackendRemoveCacheEntry(const base::FilePath& cache_dir,
                                      const std::string& id);

  
  static bool CompareCacheItemsAge(const CacheMap::iterator& lhs,
                                   const CacheMap::iterator& rhs);

  
  void CleanUp();

  
  base::FilePath cache_dir_;

  
  uint64 max_cache_size_;

  
  
  base::Time min_cache_age_;

  
  scoped_refptr<base::SequencedTaskRunner> backend_task_runner_;

  
  State state_;

  
  CacheMap cached_extensions_;

  
  base::WeakPtrFactory<LocalExtensionCache> weak_ptr_factory_;

  
  base::TimeDelta cache_status_polling_delay_;

  DISALLOW_COPY_AND_ASSIGN(LocalExtensionCache);
};

}  

#endif  
