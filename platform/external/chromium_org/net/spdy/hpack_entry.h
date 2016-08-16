// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_ENTRY_H_
#define NET_SPDY_HPACK_ENTRY_H_

#include <cstddef>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"


namespace net {

class NET_EXPORT_PRIVATE HpackEntry {
 public:
  
  
  static const size_t kSizeOverhead;

  
  
  
  
  
  
  
  
  HpackEntry(base::StringPiece name,
             base::StringPiece value,
             bool is_static,
             size_t insertion_index);

  
  
  HpackEntry(base::StringPiece name, base::StringPiece value);

  
  
  HpackEntry();

  ~HpackEntry();

  const std::string& name() const { return name_; }
  const std::string& value() const { return value_; }

  
  
  bool IsStatic() const { return type_ == STATIC; }

  
  bool IsLookup() const { return type_ == LOOKUP; }

  
  size_t InsertionIndex() const { return insertion_index_; }

  
  static size_t Size(base::StringPiece name, base::StringPiece value);
  size_t Size() const;

  std::string GetDebugString() const;

 private:
  enum EntryType {
    LOOKUP,
    DYNAMIC,
    STATIC,
  };

  
  std::string name_;
  std::string value_;

  
  
  size_t insertion_index_;

  EntryType type_;
};

}  

#endif  
