// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_NINJA_BINARY_TARGET_WRITER_H_
#define TOOLS_GN_NINJA_BINARY_TARGET_WRITER_H_

#include "base/compiler_specific.h"
#include "tools/gn/config_values.h"
#include "tools/gn/ninja_target_writer.h"
#include "tools/gn/toolchain.h"
#include "tools/gn/unique_vector.h"

struct EscapeOptions;

class NinjaBinaryTargetWriter : public NinjaTargetWriter {
 public:
  NinjaBinaryTargetWriter(const Target* target, std::ostream& out);
  virtual ~NinjaBinaryTargetWriter();

  virtual void Run() OVERRIDE;

 private:
  typedef std::set<OutputFile> OutputFileSet;

  void WriteCompilerVars();
  void WriteSources(std::vector<OutputFile>* object_files);
  void WriteLinkerStuff(const std::vector<OutputFile>& object_files);
  void WriteLinkerFlags();
  void WriteLibs();
  void WriteOutputExtension();
  void WriteSolibs(const std::vector<OutputFile>& solibs);

  
  void WriteSourceSetStamp(const std::vector<OutputFile>& object_files);

  
  
  void GetDeps(UniqueVector<OutputFile>* extra_object_files,
               UniqueVector<const Target*>* linkable_deps,
               UniqueVector<const Target*>* non_linkable_deps) const;

  
  
  
  
  void ClassifyDependency(const Target* dep,
                          UniqueVector<OutputFile>* extra_object_files,
                          UniqueVector<const Target*>* linkable_deps,
                          UniqueVector<const Target*>* non_linkable_deps) const;

  
  
  
  
  
  void WriteOrderOnlyDependencies(
      const UniqueVector<const Target*>& non_linkable_deps);

  
  
  
  
  
  
  
  
  
  
  // just passed to the output. The output will always be overwritten, not
  
  bool GetOutputFilesForSource(const Target* target,
                               const SourceFile& source,
                               Toolchain::ToolType* computed_tool_type,
                               std::vector<OutputFile>* outputs) const;

  const Tool* tool_;

  DISALLOW_COPY_AND_ASSIGN(NinjaBinaryTargetWriter);
};

#endif  

