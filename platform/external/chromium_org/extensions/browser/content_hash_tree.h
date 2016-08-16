// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_HASH_TREE_H_
#define EXTENSIONS_BROWSER_CONTENT_HASH_TREE_H_

#include <string>
#include <vector>

namespace extensions {

std::string ComputeTreeHashRoot(const std::vector<std::string>& leaf_hashes,
                                int branch_factor);

}  

#endif  
