// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_IP_PATTERN_H_
#define NET_BASE_IP_PATTERN_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/base/net_util.h"

namespace net {

class NET_EXPORT IPPattern {
 public:
  IPPattern();
  ~IPPattern();

  
  
  bool ParsePattern(const std::string& ip_pattern);
  
  
  bool Match(const IPAddressNumber& address) const;

  bool is_ipv4() const { return is_ipv4_; }

 private:
  class ComponentPattern;
  typedef std::vector<std::string> Strings;
  typedef std::vector<ComponentPattern*> ComponentPatternList;

  
  
  bool ParseComponentPattern(const base::StringPiece& text,
                             ComponentPattern* pattern) const;
  
  bool ValueTextToInt(const base::StringPiece& input, uint32* output) const;

  bool is_ipv4_;
  
  
  
  
  
  std::vector<bool> ip_mask_;
  
  
  
  
  
  std::vector<uint32> component_values_;
  
  
  
  
  ComponentPatternList component_patterns_;

  DISALLOW_COPY_AND_ASSIGN(IPPattern);
};

}  

#endif  
