// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_NINJA_TARGET_WRITER_H_
#define TOOLS_GN_NINJA_TARGET_WRITER_H_

#include <iosfwd>

#include "base/basictypes.h"
#include "tools/gn/path_output.h"
#include "tools/gn/substitution_type.h"

class FileTemplate;
class OutputFile;
class Settings;
class Target;

class NinjaTargetWriter {
 public:
  NinjaTargetWriter(const Target* target, std::ostream& out);
  virtual ~NinjaTargetWriter();

  static void RunAndWriteFile(const Target* target);

  virtual void Run() = 0;

 protected:
  
  
  // identified by the given bits will be written.
  void WriteSharedVars(const SubstitutionBits& bits);

  
  
  
  
  
  OutputFile WriteInputDepsStampAndGetDep(
      const std::vector<const Target*>& extra_hard_deps) const;

  
  
  
  void WriteStampForTarget(const std::vector<OutputFile>& deps,
                           const std::vector<OutputFile>& order_only_deps);

  const Settings* settings_;  
  const Target* target_;  
  std::ostream& out_;
  PathOutput path_output_;

 private:
  void WriteCopyRules();

  DISALLOW_COPY_AND_ASSIGN(NinjaTargetWriter);
};

#endif  
