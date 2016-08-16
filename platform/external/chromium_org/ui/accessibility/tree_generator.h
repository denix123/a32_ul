// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace ui {

class AXTree;

class TreeGenerator {
 public:
  TreeGenerator(int node_count);

  int UniqueTreeCount() const;

  void BuildUniqueTree(int tree_index, AXTree* out_tree) const;

 private:
  int node_count_;
  int unique_tree_count_;
};

}  
