// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_DISK_CACHE_BLOCKFILE_BACKEND_IMPL_H_
#define NET_DISK_CACHE_BLOCKFILE_BACKEND_IMPL_H_

#include "base/containers/hash_tables.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/timer/timer.h"
#include "net/disk_cache/blockfile/block_files.h"
#include "net/disk_cache/blockfile/eviction.h"
#include "net/disk_cache/blockfile/in_flight_backend_io.h"
#include "net/disk_cache/blockfile/rankings.h"
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

struct Index;

enum BackendFlags {
  kNone = 0,
  kMask = 1,                    
  kMaxSize = 1 << 1,            
  kUnitTestMode = 1 << 2,       
  kUpgradeMode = 1 << 3,        
  kNewEviction = 1 << 4,        
  kNoRandom = 1 << 5,           
  kNoLoadProtection = 1 << 6,   
  kNoBuffering = 1 << 7         
};

class NET_EXPORT_PRIVATE BackendImpl : public Backend {
  friend class Eviction;
 public:
  BackendImpl(const base::FilePath& path,
              const scoped_refptr<base::SingleThreadTaskRunner>& cache_thread,
              net::NetLog* net_log);
  
  BackendImpl(const base::FilePath& path,
              uint32 mask,
              const scoped_refptr<base::SingleThreadTaskRunner>& cache_thread,
              net::NetLog* net_log);
  virtual ~BackendImpl();

  
  int Init(const CompletionCallback& callback);

  
  int SyncInit();
  void CleanupCache();

  
  int SyncOpenEntry(const std::string& key, Entry** entry);
  int SyncCreateEntry(const std::string& key, Entry** entry);
  int SyncDoomEntry(const std::string& key);
  int SyncDoomAllEntries();
  int SyncDoomEntriesBetween(base::Time initial_time,
                             base::Time end_time);
  int SyncDoomEntriesSince(base::Time initial_time);
  int SyncOpenNextEntry(Rankings::Iterator* iterator, Entry** next_entry);
  void SyncEndEnumeration(scoped_ptr<Rankings::Iterator> iterator);
  void SyncOnExternalCacheHit(const std::string& key);

  
  EntryImpl* OpenEntryImpl(const std::string& key);
  EntryImpl* CreateEntryImpl(const std::string& key);
  EntryImpl* OpenNextEntryImpl(Rankings::Iterator* iter);

  
  bool SetMaxSize(int max_bytes);

  
  void SetType(net::CacheType type);

  
  base::FilePath GetFileName(Addr address) const;

  
  MappedFile* File(Addr address);

  
  base::WeakPtr<InFlightBackendIO> GetBackgroundQueue();

  
  bool CreateExternalFile(Addr* address);

  
  bool CreateBlock(FileType block_type, int block_count,
                   Addr* block_address);

  
  
  void DeleteBlock(Addr block_address, bool deep);

  
  LruData* GetLruData();

  
  void UpdateRank(EntryImpl* entry, bool modified);

  
  
  void RecoveredEntry(CacheRankingsBlock* rankings);

  
  void InternalDoomEntry(EntryImpl* entry);

#if defined(NET_BUILD_STRESS_CACHE)
  
  CacheAddr GetNextAddr(Addr address);

  
  void NotLinked(EntryImpl* entry);
#endif

  
  void RemoveEntry(EntryImpl* entry);

  
  
  
  void OnEntryDestroyBegin(Addr address);

  
  
  void OnEntryDestroyEnd();

  
  
  
  EntryImpl* GetOpenEntry(CacheRankingsBlock* rankings) const;

  
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

  
  
  
  std::string HistogramName(const char* name, int experiment) const;

  net::CacheType cache_type() const {
    return cache_type_;
  }

  bool read_only() const {
    return read_only_;
  }

  
  base::WeakPtr<BackendImpl> GetWeakPtr();

  
  
  
  bool ShouldReportAgain();

  
  void FirstEviction();

  
  void CriticalError(int error);

  
  void ReportError(int error);

  
  void OnEvent(Stats::Counters an_event);

  
  void OnRead(int bytes);
  void OnWrite(int bytes);

  
  void OnStatsTimer();

  
  void IncrementIoCount();
  void DecrementIoCount();

  
  void SetUnitTestMode();

  
  void SetUpgradeMode();

  
  void SetNewEviction();

  
  void SetFlags(uint32 flags);

  
  void ClearRefCountForTest();

  
  int FlushQueueForTest(const CompletionCallback& callback);

  
  
  int RunTaskForTest(const base::Closure& task,
                     const CompletionCallback& callback);

  
  
  void TrimForTest(bool empty);

  
  
  void TrimDeletedListForTest(bool empty);

  
  base::RepeatingTimer<BackendImpl>* GetTimerForTest();

  
  
  int SelfCheck();

  
  void FlushIndex();

  
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
  typedef base::hash_map<CacheAddr, EntryImpl*> EntriesMap;
  class IteratorImpl;

  
  bool CreateBackingStore(disk_cache::File* file);
  bool InitBackingStore(bool* file_created);
  void AdjustMaxCacheSize(int table_len);

  bool InitStats();
  void StoreStats();

  
  void RestartCache(bool failure);
  void PrepareForRestart();

  
  
  int NewEntry(Addr address, EntryImpl** entry);

  
  
  
  
  
  
  
  EntryImpl* MatchEntry(const std::string& key, uint32 hash, bool find_parent,
                        Addr entry_addr, bool* match_error);

  
  
  
  bool OpenFollowingEntryFromList(Rankings::List list,
                                  CacheRankingsBlock** from_entry,
                                  EntryImpl** next_entry);

  
  EntryImpl* GetEnumeratedEntry(CacheRankingsBlock* next, Rankings::List list);

  
  EntryImpl* ResurrectEntry(EntryImpl* deleted_entry);

  void DestroyInvalidEntry(EntryImpl* entry);

  
  void AddStorageSize(int32 bytes);
  void SubstractStorageSize(int32 bytes);

  
  void IncreaseNumRefs();
  void DecreaseNumRefs();
  void IncreaseNumEntries();
  void DecreaseNumEntries();

  
  void LogStats();

  
  void ReportStats();

  
  void UpgradeTo2_1();

  
  bool CheckIndex();

  
  int CheckAllEntries();

  
  bool CheckEntry(EntryImpl* cache_entry);

  
  int MaxBuffersSize();

  InFlightBackendIO background_queue_;  
  scoped_refptr<MappedFile> index_;  
  base::FilePath path_;  
  Index* data_;  
  BlockFiles block_files_;  
  Rankings rankings_;  
  uint32 mask_;  
  int32 max_size_;  
  Eviction eviction_;  
  EntriesMap open_entries_;  
  int num_refs_;  
  int max_refs_;  
  int num_pending_io_;  
  int entry_count_;  
  int byte_count_;  // Number of bytes read/written lately.
  int buffer_bytes_;  
  int up_ticks_;  
  net::CacheType cache_type_;
  int uma_report_;  
  uint32 user_flags_;  
  bool init_;  
  bool restarted_;
  bool unit_test_;
  bool read_only_;  
  bool disabled_;
  bool new_eviction_;  
  bool first_timer_;  
  bool user_load_;  

  net::NetLog* net_log_;

  Stats stats_;  
  scoped_ptr<base::RepeatingTimer<BackendImpl> > timer_;  
  base::WaitableEvent done_;  
  scoped_refptr<TraceObject> trace_object_;  
  base::WeakPtrFactory<BackendImpl> ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BackendImpl);
};

}  

#endif  
