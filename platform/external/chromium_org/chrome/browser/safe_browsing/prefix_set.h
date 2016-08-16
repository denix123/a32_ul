// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_PREFIX_SET_H_
#define CHROME_BROWSER_SAFE_BROWSING_PREFIX_SET_H_

#include <utility>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/safe_browsing/safe_browsing_util.h"

namespace base {
class FilePath;
}

namespace safe_browsing {

class PrefixSet {
 public:
  ~PrefixSet();

  
  
  bool Exists(const SBFullHash& hash) const;

  
  static scoped_ptr<PrefixSet> LoadFile(const base::FilePath& filter_name);
  bool WriteFile(const base::FilePath& filter_name) const;

 private:
  friend class PrefixSetBuilder;

  friend class PrefixSetTest;
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, AllBig);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, EdgeCases);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, Empty);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, FullHashBuild);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, IntMinMax);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, OneElement);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, ReadWrite);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, ReadWriteSigned);
  FRIEND_TEST_ALL_PREFIXES(PrefixSetTest, Version3);

  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, BasicStore);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, DeleteChunks);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, DetectsCorruption);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, Empty);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, PrefixMinMax);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, SubKnockout);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, Version7);
  FRIEND_TEST_ALL_PREFIXES(SafeBrowsingStoreFileTest, Version8);

  
  
  
  static const size_t kMaxRun = 100;

  
  typedef std::pair<SBPrefix, uint32> IndexPair;
  typedef std::vector<IndexPair> IndexVector;
  static bool PrefixLess(const IndexPair& a, const IndexPair& b);

  
  
  void AddRun(SBPrefix index_prefix,
              const uint16* run_begin, const uint16* run_end);

  
  
  bool PrefixExists(SBPrefix prefix) const;

  
  
  void GetPrefixes(std::vector<SBPrefix>* prefixes) const;

  
  PrefixSet();

  
  PrefixSet(IndexVector* index,
            std::vector<uint16>* deltas,
            std::vector<SBFullHash>* full_hashes);

  
  
  
  
  IndexVector index_;

  
  
  
  std::vector<uint16> deltas_;

  
  std::vector<SBFullHash> full_hashes_;

  DISALLOW_COPY_AND_ASSIGN(PrefixSet);
};

class PrefixSetBuilder {
 public:
  PrefixSetBuilder();
  ~PrefixSetBuilder();

  
  explicit PrefixSetBuilder(const std::vector<SBPrefix>& prefixes);

  
  
  void AddPrefix(SBPrefix prefix);

  
  
  
  scoped_ptr<PrefixSet> GetPrefixSet(const std::vector<SBFullHash>& hashes);

  
  
  scoped_ptr<PrefixSet> GetPrefixSetNoHashes();

 private:
  
  
  void EmitRun();

  
  std::vector<SBPrefix> buffer_;

  
  scoped_ptr<PrefixSet> prefix_set_;
};

}  

#endif  
