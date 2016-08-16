// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_NINJA_ACTION_TARGET_WRITER_H_
#define TOOLS_GN_NINJA_ACTION_TARGET_WRITER_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "tools/gn/ninja_target_writer.h"

class OutputFile;

class NinjaActionTargetWriter : public NinjaTargetWriter {
 public:
  NinjaActionTargetWriter(const Target* target, std::ostream& out);
  virtual ~NinjaActionTargetWriter();

  virtual void Run() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(NinjaActionTargetWriter,
                           WriteOutputFilesForBuildLine);
  FRIEND_TEST_ALL_PREFIXES(NinjaActionTargetWriter,
                           WriteOutputFilesForBuildLineWithDepfile);
  FRIEND_TEST_ALL_PREFIXES(NinjaActionTargetWriter,
                           WriteArgsSubstitutions);

  
  
  
  
  
  std::string WriteRuleDefinition();

  
  
  
  
  
  void WriteSourceRules(const std::string& custom_rule_name,
                        const OutputFile& input_dep,
                        std::vector<OutputFile>* output_files);

  
  
  
  void WriteOutputFilesForBuildLine(const SourceFile& source,
                                    std::vector<OutputFile>* output_files);

  void WriteDepfile(const SourceFile& source);

  
  
  
  PathOutput path_output_no_escaping_;

  DISALLOW_COPY_AND_ASSIGN(NinjaActionTargetWriter);
};

#endif  
