// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_TRIE_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_TRIE_H_

#include <stdint.h>
#include <map>
#include <set>
#include <vector>

namespace autofill {

template <typename T>
class Trie {
 public:
  Trie();
  ~Trie();

  
  bool empty() const { return data_list_.empty() && sub_nodes_.empty(); }

  
  
  void AddDataForKey(const std::vector<uint8_t>& key, const T& data_item);

  
  
  void FindDataForKeyPrefix(const std::vector<uint8_t>& key_prefix,
                            std::set<T>* results) const;

 private:
  
  
  std::set<T> data_list_;

  
  
  
  
  std::map<uint8_t, Trie<T> > sub_nodes_;
};

}  

#endif  
