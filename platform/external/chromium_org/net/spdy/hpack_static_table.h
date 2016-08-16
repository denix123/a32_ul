// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_STATIC_TABLE_H_
#define NET_SPDY_HPACK_STATIC_TABLE_H_

#include "net/spdy/hpack_header_table.h"

namespace net {

struct HpackStaticEntry;

class NET_EXPORT_PRIVATE HpackStaticTable {
 public:
  HpackStaticTable();
  ~HpackStaticTable();

  
  
  void Initialize(const HpackStaticEntry* static_entry_table,
                  size_t static_entry_count);

  
  bool IsInitialized() const;

  
  const HpackHeaderTable::EntryTable& GetStaticEntries() const {
    return static_entries_;
  }
  const HpackHeaderTable::OrderedEntrySet& GetStaticIndex() const {
    return static_index_;
  }

 private:
  HpackHeaderTable::EntryTable static_entries_;
  HpackHeaderTable::OrderedEntrySet static_index_;
};

}  

#endif  
