// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_HEADER_TABLE_H_
#define NET_SPDY_HPACK_HEADER_TABLE_H_

#include <cstddef>
#include <deque>
#include <set>

#include "base/basictypes.h"
#include "base/macros.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_entry.h"


namespace net {

using base::StringPiece;

namespace test {
class HpackHeaderTablePeer;
}  

class NET_EXPORT_PRIVATE HpackHeaderTable {
 public:
  friend class test::HpackHeaderTablePeer;

  
  
  
  
  
  typedef std::deque<HpackEntry> EntryTable;

  
  
  
  
  
  struct NET_EXPORT_PRIVATE EntryComparator {
    bool operator() (const HpackEntry* lhs, const HpackEntry* rhs) const;
  };
  typedef std::set<HpackEntry*, EntryComparator> OrderedEntrySet;

  HpackHeaderTable();

  ~HpackHeaderTable();

  
  size_t settings_size_bound() { return settings_size_bound_; }

  
  
  size_t size() const { return size_; }
  size_t max_size() const { return max_size_; }

  
  const HpackEntry* GetByIndex(size_t index);

  
  const HpackEntry* GetByName(StringPiece name);

  
  const HpackEntry* GetByNameAndValue(StringPiece name, StringPiece value);

  
  size_t IndexOf(const HpackEntry* entry) const;

  
  
  void SetMaxSize(size_t max_size);

  
  
  void SetSettingsHeaderTableSize(size_t settings_size);

  
  
  
  void EvictionSet(StringPiece name,
                   StringPiece value,
                   EntryTable::iterator* begin_out,
                   EntryTable::iterator* end_out);

  
  
  
  
  const HpackEntry* TryAddEntry(StringPiece name, StringPiece value);

  void DebugLogTableState() const;

 private:
  
  size_t EvictionCountForEntry(StringPiece name, StringPiece value) const;

  
  size_t EvictionCountToReclaim(size_t reclaim_size) const;

  
  void Evict(size_t count);

  
  
  const EntryTable& static_entries_;
  EntryTable dynamic_entries_;

  const OrderedEntrySet& static_index_;
  OrderedEntrySet dynamic_index_;

  
  size_t settings_size_bound_;

  
  
  size_t size_;
  size_t max_size_;

  
  
  size_t total_insertions_;

  DISALLOW_COPY_AND_ASSIGN(HpackHeaderTable);
};

}  

#endif  
