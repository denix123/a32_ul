// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_SUBTREE_SET_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_SUBTREE_SET_H_

#include "base/containers/hash_tables.h"
#include "base/files/file_path.h"

namespace base {
class FilePath;
}  

namespace sync_file_system {

class SubtreeSet {
 public:
  SubtreeSet();
  ~SubtreeSet();

  
  
  bool IsDisjointWith(const base::FilePath& subtree_root) const;

  
  
  bool insert(const base::FilePath& subtree_root);

  
  
  bool erase(const base::FilePath& subtree_root);

  size_t size() const;
  bool empty() const { return inclusive_ancestors_of_subtree_roots_.empty(); }

 private:
  struct Node {
    bool contained_as_subtree_root;
    size_t number_of_subtrees_below;

    Node();
    Node(bool contained_as_subtree_root,
         size_t number_of_subtrees_below);
  };

  typedef base::FilePath::StringType StringType;
  typedef base::hash_map<StringType, Node> Subtrees;

  
  
  Subtrees inclusive_ancestors_of_subtree_roots_;
};

}  

#endif  
