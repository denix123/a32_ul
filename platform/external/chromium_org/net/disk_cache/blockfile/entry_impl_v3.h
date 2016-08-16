// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_DISK_CACHE_BLOCKFILE_ENTRY_IMPL_V3_H_
#define NET_DISK_CACHE_BLOCKFILE_ENTRY_IMPL_V3_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "net/base/net_log.h"
#include "net/disk_cache/blockfile/disk_format_v3.h"
#include "net/disk_cache/blockfile/storage_block.h"
#include "net/disk_cache/disk_cache.h"

namespace disk_cache {

class BackendImplV3;
class SparseControlV3;

class NET_EXPORT_PRIVATE EntryImplV3
    : public Entry,
      public base::RefCounted<EntryImplV3> {
  friend class base::RefCounted<EntryImplV3>;
  
 public:
  enum Operation {
    kRead,
    kWrite,
    kSparseRead,
    kSparseWrite,
    kAsyncIO,
    kReadAsync1,
    kWriteAsync1
  };

  EntryImplV3(BackendImplV3* backend, Addr address, bool read_only);

  
  
  bool CreateEntry(Addr node_address, const std::string& key, uint32 hash);

  uint32 GetHash();

  uint32 GetHash() const;
  Addr GetAddress() const;
  int GetReuseCounter() const;
  void SetReuseCounter(int count);
  int GetRefetchCounter() const;
  void SetRefetchCounter(int count);

  
  bool IsSameEntry(const std::string& key, uint32 hash);

  
  void InternalDoom();

  
  bool SanityCheck();
  bool DataSanityCheck();

  
  void FixForDelete();

  
  
  void SetTimes(base::Time last_used, base::Time last_modified);

  
  
  
  
  void BeginLogging(net::NetLog* net_log, bool created);

  const net::BoundNetLog& net_log() const;

  
  virtual void Doom() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual std::string GetKey() const OVERRIDE;
  virtual base::Time GetLastUsed() const OVERRIDE;
  virtual base::Time GetLastModified() const OVERRIDE;
  virtual int32 GetDataSize(int index) const OVERRIDE;
  virtual int ReadData(int index, int offset, IOBuffer* buf, int buf_len,
                       const CompletionCallback& callback) OVERRIDE;
  virtual int WriteData(int index, int offset, IOBuffer* buf, int buf_len,
                        const CompletionCallback& callback,
                        bool truncate) OVERRIDE;
  virtual int ReadSparseData(int64 offset, IOBuffer* buf, int buf_len,
                             const CompletionCallback& callback) OVERRIDE;
  virtual int WriteSparseData(int64 offset, IOBuffer* buf, int buf_len,
                              const CompletionCallback& callback) OVERRIDE;
  virtual int GetAvailableRange(int64 offset, int len, int64* start,
                                const CompletionCallback& callback) OVERRIDE;
  virtual bool CouldBeSparse() const OVERRIDE;
  virtual void CancelSparseIO() OVERRIDE;
  virtual int ReadyForSparseIO(const CompletionCallback& callback) OVERRIDE;

 private:
  enum {
     kNumStreams = 3
  };
  class UserBuffer;

  virtual ~EntryImplV3();

  
  
  int InternalReadData(int index, int offset, IOBuffer* buf,
                       int buf_len, const CompletionCallback& callback);
  int InternalWriteData(int index, int offset, IOBuffer* buf, int buf_len,
                        const CompletionCallback& callback, bool truncate);

  
  bool CreateDataBlock(int index, int size);

  
  bool CreateBlock(int size, Addr* address);

  
  
  
  
  void DeleteData(Addr address, int index);

  
  void UpdateRank(bool modified);

  
  
  void DeleteEntryData(bool everything);

  
  
  bool PrepareTarget(int index, int offset, int buf_len, bool truncate);

  
  
  bool HandleTruncation(int index, int offset, int buf_len);

  
  bool CopyToLocalBuffer(int index);

  
  bool MoveToLocalBuffer(int index);

  
  bool ImportSeparateFile(int index, int new_size);

  
  
  bool PrepareBuffer(int index, int offset, int buf_len);

  
  
  bool Flush(int index, int min_len);

  
  void UpdateSize(int index, int old_size, int new_size);

  
  int InitSparseData();

  
  void SetEntryFlags(uint32 flags);

  
  uint32 GetEntryFlags();

  
  
  
  
  
  
  
  
  void GetData(int index, char** buffer, Addr* address);

  
  void ReportIOTime(Operation op, const base::TimeTicks& start);

  
  void Log(const char* msg);

  scoped_ptr<EntryRecord> entry_;  
  scoped_ptr<ShortEntryRecord> short_entry_;  
  base::WeakPtr<BackendImplV3> backend_;  
  scoped_ptr<UserBuffer> user_buffers_[kNumStreams];  
  mutable std::string key_;           
  Addr address_;
  int unreported_size_[kNumStreams];  
  bool doomed_;               
  bool read_only_;
  bool dirty_;                
  bool modified_;
  

  net::BoundNetLog net_log_;

  DISALLOW_COPY_AND_ASSIGN(EntryImplV3);
};

}  

#endif  
