// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_DISK_CACHE_BLOCKFILE_INDEX_TABLE_V3_H_
#define NET_DISK_CACHE_BLOCKFILE_INDEX_TABLE_V3_H_


#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "net/base/net_export.h"
#include "net/disk_cache/blockfile/addr.h"
#include "net/disk_cache/blockfile/bitmap.h"
#include "net/disk_cache/blockfile/disk_format_v3.h"

namespace net {
class IOBuffer;
}

namespace disk_cache {

class BackendImplV3;
struct InitResult;

class NET_EXPORT_PRIVATE EntryCell {
 public:
  ~EntryCell();

  bool IsValid() const;

  int32 cell_num() const { return cell_num_; }
  uint32 hash() const { return hash_; }

  Addr GetAddress() const;
  EntryState GetState() const;
  EntryGroup GetGroup() const;
  int GetReuse() const;
  int GetTimestamp() const;

  void SetState(EntryState state);
  void SetGroup(EntryGroup group);
  void SetReuse(int count);
  void SetTimestamp(int timestamp);

  static EntryCell GetEntryCellForTest(int32 cell_num,
                                       uint32 hash,
                                       Addr address,
                                       IndexCell* cell,
                                       bool small_table);
  void SerializaForTest(IndexCell* destination);

 private:
  friend class IndexTable;
  friend class CacheDumperHelper;

  EntryCell();
  EntryCell(int32 cell_num, uint32 hash, Addr address, bool small_table);
  EntryCell(int32 cell_num,
            uint32 hash,
            const IndexCell& cell,
            bool small_table);

  void Clear() { cell_.Clear(); }
  void FixSum();

  
  uint32 GetLocation() const;

  
  
  uint32 RecomputeHash();

  void Serialize(IndexCell* destination) const;

  int32 cell_num_;
  uint32 hash_;
  IndexCell cell_;
  bool small_table_;
};

struct NET_EXPORT_PRIVATE EntrySet {
  EntrySet();
  ~EntrySet();

  int evicted_count;  
  size_t current;     
  std::vector<EntryCell> cells;
};

struct CellInfo { uint32 hash; Addr address; };
typedef std::vector<CellInfo> CellList;

struct NET_EXPORT_PRIVATE IndexIterator {
  IndexIterator();
  ~IndexIterator();

  CellList cells;
  int timestamp;  
  bool forward;   
};

class NET_EXPORT_PRIVATE IndexTableBackend {
 public:
  virtual ~IndexTableBackend() {}

  
  virtual void GrowIndex() = 0;

  
  virtual void SaveIndex(net::IOBuffer* buffer, int buffer_len) = 0;

  
  virtual void DeleteCell(EntryCell cell) = 0;
  virtual void FixCell(EntryCell cell) = 0;
};

struct NET_EXPORT_PRIVATE IndexTableInitData {
  IndexTableInitData();
  ~IndexTableInitData();

  IndexBitmap* index_bitmap;
  IndexBucket* main_table;
  IndexBucket* extra_table;
  scoped_ptr<IndexHeaderV3> backup_header;
  scoped_ptr<uint32[]> backup_bitmap;
};

class NET_EXPORT_PRIVATE IndexTable {
 public:
  explicit IndexTable(IndexTableBackend* backend);
  ~IndexTable();

  
  
  
  
  
  
  void Init(IndexTableInitData* params);

  
  void Shutdown();

  
  
  EntrySet LookupEntries(uint32 hash);

  
  EntryCell CreateEntryCell(uint32 hash, Addr address);

  
  
  
  
  EntryCell FindEntryCell(uint32 hash, Addr address);

  
  
  
  
  int CalculateTimestamp(base::Time time);

  
  base::Time TimeFromTimestamp(int timestamp);

  
  void SetSate(uint32 hash, Addr address, EntryState state);
  void UpdateTime(uint32 hash, Addr address, base::Time current);

  
  void Save(EntryCell* cell);

  
  
  
  void GetOldest(IndexIterator* no_use,
                 IndexIterator* low_use,
                 IndexIterator* high_use);

  
  
  
  
  bool GetNextCells(IndexIterator* iterator);

  
  
  
  
  void OnBackupTimer();

  IndexHeaderV3* header() { return header_; }
  const IndexHeaderV3* header() const { return header_; }

 private:
  EntryCell FindEntryCellImpl(uint32 hash, Addr address, bool allow_deleted);
  void CheckState(const EntryCell& cell);
  void Write(const EntryCell& cell);
  int NewExtraBucket();
  void WalkTables(int limit_time,
                  IndexIterator* no_use,
                  IndexIterator* low_use,
                  IndexIterator* high_use);
  void UpdateFromBucket(IndexBucket* bucket, int bucket_hash,
                        int limit_time,
                        IndexIterator* no_use,
                        IndexIterator* low_use,
                        IndexIterator* high_use);
  void MoveCells(IndexBucket* old_extra_table);
  void MoveSingleCell(IndexCell* current_cell, int cell_num,
                      int main_table_index, bool growing);
  void HandleMisplacedCell(IndexCell* current_cell, int cell_num,
                           int main_table_index);
  void CheckBucketList(int bucket_id);

  uint32 GetLocation(const IndexCell& cell);
  uint32 GetHashValue(const IndexCell& cell);
  uint32 GetFullHash(const IndexCell& cell, uint32 lower_part);
  bool IsHashMatch(const IndexCell& cell, uint32 hash);
  bool MisplacedHash(const IndexCell& cell, uint32 hash);

  IndexTableBackend* backend_;
  IndexHeaderV3* header_;
  scoped_ptr<Bitmap> bitmap_;
  scoped_ptr<Bitmap> backup_bitmap_;
  scoped_ptr<uint32[]> backup_bitmap_storage_;
  scoped_ptr<IndexHeaderV3> backup_header_;
  IndexBucket* main_table_;
  IndexBucket* extra_table_;
  uint32 mask_;     
  int extra_bits_;  
  bool modified_;
  bool small_table_;

  DISALLOW_COPY_AND_ASSIGN(IndexTable);
};

}  

#endif  
