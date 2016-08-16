// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_BACKEND_IMPL_V3_H_
#define NET_DISK_CACHE_BLOCKFILE_BACKEND_IMPL_V3_H_

#include "base/containers/hash_tables.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/timer/timer.h"
#include "net/disk_cache/blockfile/block_bitmaps_v3.h"
#include "net/disk_cache/blockfile/block_files.h"
#include "net/disk_cache/blockfile/eviction_v3.h"
#include "net/disk_cache/blockfile/index_table_v3.h"
#include "net/disk_cache/blockfile/stats.h"
#include "net/disk_cache/blockfile/stress_support.h"
#include "net/disk_cache/blockfile/trace.h"
#include "net/disk_cache/disk_cache.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace net {
class NetLog;
}  

namespace disk_cache {

class EntryImplV3;

class NET_EXPORT_PRIVATE BackendImplV3 : public Backend {
 public:
  enum BackendFlags {
    MAX_SIZE = 1 << 1,            
    UNIT_TEST_MODE = 1 << 2,      
    UPGRADE_MODE = 1 << 3,        
    EVICTION_V2 = 1 << 4,         
    BASIC_UNIT_TEST = 1 << 5,     
    NO_LOAD_PROTECTION = 1 << 6,  
    NO_BUFFERING = 1 << 7,        
    NO_CLEAN_ON_EXIT = 1 << 8     
  };

  BackendImplV3(const base::FilePath& path,
                const scoped_refptr<base::SingleThreadTaskRunner>& cache_thread,
                net::NetLog* net_log);
  virtual ~BackendImplV3();

  
  int Init(const CompletionCallback& callback);

  
  bool SetMaxSize(int max_bytes);

  
  void SetType(net::CacheType type);

  
  bool CreateBlock(FileType block_type, int block_count,
                   Addr* block_address);

  
  void UpdateRank(EntryImplV3* entry, bool modified);

  
  void InternalDoomEntry(EntryImplV3* entry);

  
  
  
  void OnEntryDestroyBegin(Addr address);

  
  
  void OnEntryDestroyEnd();

  
  
  
  EntryImplV3* GetOpenEntry(Addr address) const;

  
  int32 GetCurrentEntryId() const;

  
  int MaxFileSize() const;

  
  void ModifyStorageSize(int32 old_size, int32 new_size);

  
  void TooMuchStorageRequested(int32 size);

  
  bool IsAllocAllowed(int current_size, int new_size);

  
  void BufferDeleted(int size);

  
  int GetTotalBuffersSize() const {
    return buffer_bytes_;
  }

  
  bool IsLoaded() const;

  
  
  std::string HistogramName(const char* name) const;

  net::CacheType cache_type() const {
    return cache_type_;
  }

  bool read_only() const {
    return read_only_;
  }

  
  base::WeakPtr<BackendImplV3> GetWeakPtr();

  
  
  
  bool ShouldReportAgain();

  
  void FirstEviction();

  
  void OnEvent(Stats::Counters an_event);

  
  void OnRead(int bytes);
  void OnWrite(int bytes);

  
  void OnTimerTick();

  
  void SetUnitTestMode();

  
  void SetUpgradeMode();

  
  void SetNewEviction();

  
  void SetFlags(uint32 flags);

  
  int FlushQueueForTest(const CompletionCallback& callback);

  
  
  void TrimForTest(bool empty);

  
  
  void TrimDeletedListForTest(bool empty);

  
  
  int SelfCheck();

  
  virtual net::CacheType GetCacheType() const OVERRIDE;
  virtual int32 GetEntryCount() const OVERRIDE;
  virtual int OpenEntry(const std::string& key, Entry** entry,
                        const CompletionCallback& callback) OVERRIDE;
  virtual int CreateEntry(const std::string& key, Entry** entry,
                          const CompletionCallback& callback) OVERRIDE;
  virtual int DoomEntry(const std::string& key,
                        const CompletionCallback& callback) OVERRIDE;
  virtual int DoomAllEntries(const CompletionCallback& callback) OVERRIDE;
  virtual int DoomEntriesBetween(base::Time initial_time,
                                 base::Time end_time,
                                 const CompletionCallback& callback) OVERRIDE;
  virtual int DoomEntriesSince(base::Time initial_time,
                               const CompletionCallback& callback) OVERRIDE;
  virtual scoped_ptr<Iterator> CreateIterator() OVERRIDE;
  virtual void GetStats(StatsItems* stats) OVERRIDE;
  virtual void OnExternalCacheHit(const std::string& key) OVERRIDE;

 private:
  friend class EvictionV3;
  typedef base::hash_map<CacheAddr, EntryImplV3*> EntriesMap;
  class IteratorImpl;
  class NotImplementedIterator;
  class Worker;

  void AdjustMaxCacheSize();
  bool InitStats(void* stats_data);
  void StoreStats();

  
  void RestartCache(bool failure);
  void PrepareForRestart();

  
  void CleanupCache();

  
  
  int NewEntry(Addr address, EntryImplV3** entry);

  
  void AddStorageSize(int32 bytes);
  void SubstractStorageSize(int32 bytes);

  
  void IncreaseNumRefs();
  void DecreaseNumRefs();
  void IncreaseNumEntries();
  void DecreaseNumEntries();

  
  void LogStats();

  
  void ReportStats();

  
  void ReportError(int error);

  
  bool CheckIndex();

  
  int CheckAllEntries();

  
  bool CheckEntry(EntryImplV3* cache_entry);

  
  int MaxBuffersSize();

  IndexTable index_;
  base::FilePath path_;  
  BlockBitmaps block_files_;
  int32 max_size_;  
  EvictionV3 eviction_;  
  EntriesMap open_entries_;
  int num_refs_;  
  int max_refs_;  
  int entry_count_;  
  int byte_count_;  // Number of bytes read/written lately.
  int buffer_bytes_;  
  int up_ticks_;  
  net::CacheType cache_type_;
  int uma_report_;  
  uint32 user_flags_;  
  bool init_;  
  bool restarted_;
  bool read_only_;  
  bool disabled_;
  bool lru_eviction_;  
  bool first_timer_;  
  bool user_load_;  

  net::NetLog* net_log_;

  Stats stats_;  
  scoped_ptr<base::RepeatingTimer<BackendImplV3> > timer_;  
  scoped_refptr<TraceObject> trace_object_;  
  base::WeakPtrFactory<BackendImplV3> ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BackendImplV3);
};

}  

#endif  
