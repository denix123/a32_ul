// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_HEADER_CHECKER_H_
#define TOOLS_GN_HEADER_CHECKER_H_

#include <map>
#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/run_loop.h"
#include "base/strings/string_piece.h"
#include "base/synchronization/lock.h"
#include "tools/gn/err.h"

class BuildSettings;
class InputFile;
class Label;
class LocationRange;
class SourceFile;
class Target;

namespace base {
class MessageLoop;
}

class HeaderChecker : public base::RefCountedThreadSafe<HeaderChecker> {
 public:
  
  struct ChainLink {
    ChainLink() : target(NULL), is_public(false) {}
    ChainLink(const Target* t, bool p) : target(t), is_public(p) {}

    const Target* target;

    
    bool is_public;

    
    bool operator==(const ChainLink& other) const {
      return target == other.target && is_public == other.is_public;
    }
  };
  typedef std::vector<ChainLink> Chain;

  HeaderChecker(const BuildSettings* build_settings,
                const std::vector<const Target*>& targets);

  
  
  
  
  
  
  
  
  
  bool Run(const std::vector<const Target*>& to_check,
           bool force_check,
           std::vector<Err>* errors);

 private:
  friend class base::RefCountedThreadSafe<HeaderChecker>;
  FRIEND_TEST_ALL_PREFIXES(HeaderCheckerTest, IsDependencyOf);
  FRIEND_TEST_ALL_PREFIXES(HeaderCheckerTest, CheckInclude);
  FRIEND_TEST_ALL_PREFIXES(HeaderCheckerTest, PublicFirst);
  FRIEND_TEST_ALL_PREFIXES(HeaderCheckerTest, CheckIncludeAllowCircular);
  ~HeaderChecker();

  struct TargetInfo {
    TargetInfo() : target(NULL), is_public(false), is_generated(false) {}
    TargetInfo(const Target* t, bool is_pub, bool is_gen)
        : target(t),
          is_public(is_pub),
          is_generated(is_gen) {
    }

    const Target* target;

    
    bool is_public;

    
    bool is_generated;
  };

  typedef std::vector<TargetInfo> TargetVector;
  typedef std::map<SourceFile, TargetVector> FileMap;

  
  
  void RunCheckOverFiles(const FileMap& flies, bool force_check);

  void DoWork(const Target* target, const SourceFile& file);

  
  static void AddTargetToFileMap(const Target* target, FileMap* dest);

  
  bool IsFileInOuputDir(const SourceFile& file) const;

  
  SourceFile SourceFileForInclude(const base::StringPiece& input) const;

  
  
  bool CheckFile(const Target* from_target,
                 const SourceFile& file,
                 Err* err) const;

  
  
  
  
  bool CheckInclude(const Target* from_target,
                    const InputFile& source_file,
                    const SourceFile& include_file,
                    const LocationRange& range,
                    Err* err) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool IsDependencyOf(const Target* search_for,
                      const Target* search_from,
                      Chain* chain,
                      bool* is_permitted) const;

  
  
  bool IsDependencyOf(const Target* search_for,
                      const Target* search_from,
                      bool require_permitted,
                      Chain* chain) const;

  
  
  
  

  base::MessageLoop* main_loop_;
  base::RunLoop main_thread_runner_;

  const BuildSettings* build_settings_;

  
  FileMap file_map_;

  
  
  

  base::Lock lock_;

  std::vector<Err> errors_;

  DISALLOW_COPY_AND_ASSIGN(HeaderChecker);
};

#endif  
