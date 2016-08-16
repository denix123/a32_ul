// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_SUBSTITUTION_WRITER_H_
#define TOOLS_GN_SUBSTITUTION_WRITER_H_

#include <iosfwd>
#include <vector>

#include "base/basictypes.h"
#include "tools/gn/substitution_type.h"

struct EscapeOptions;
class OutputFile;
class Settings;
class SourceDir;
class SourceFile;
class SubstitutionList;
class SubstitutionPattern;
class Target;
class Tool;

extern const char kSourceExpansion_Help[];

// cflags, ldflags, libraries, etc. These are written by the ninja target
class SubstitutionWriter {
 public:
  enum OutputStyle {
    OUTPUT_ABSOLUTE,  
    OUTPUT_RELATIVE,  
  };

  
  
  static void WriteWithNinjaVariables(
      const SubstitutionPattern& pattern,
      const EscapeOptions& escape_options,
      std::ostream& out);

  

  
  
  
  
  static void GetListAsSourceFiles(
      const SubstitutionList& list,
      std::vector<SourceFile>* output);
  static void GetListAsOutputFiles(
      const Settings* settings,
      const SubstitutionList& list,
      std::vector<OutputFile>* output);

  

  
  
  
  
  
  static SourceFile ApplyPatternToSource(
      const Settings* settings,
      const SubstitutionPattern& pattern,
      const SourceFile& source);
  static std::string ApplyPatternToSourceAsString(
      const Settings* settings,
      const SubstitutionPattern& pattern,
      const SourceFile& source);
  static OutputFile ApplyPatternToSourceAsOutputFile(
      const Settings* settings,
      const SubstitutionPattern& pattern,
      const SourceFile& source);

  
  
  
  
  static void ApplyListToSource(
      const Settings* settings,
      const SubstitutionList& list,
      const SourceFile& source,
      std::vector<SourceFile>* output);
  static void ApplyListToSourceAsString(
      const Settings* settings,
      const SubstitutionList& list,
      const SourceFile& source,
      std::vector<std::string>* output);
  static void ApplyListToSourceAsOutputFile(
      const Settings* settings,
      const SubstitutionList& list,
      const SourceFile& source,
      std::vector<OutputFile>* output);

  
  
  static void ApplyListToSources(
      const Settings* settings,
      const SubstitutionList& list,
      const std::vector<SourceFile>& sources,
      std::vector<SourceFile>* output);
  static void ApplyListToSourcesAsString(
      const Settings* settings,
      const SubstitutionList& list,
      const std::vector<SourceFile>& sources,
      std::vector<std::string>* output);
  static void ApplyListToSourcesAsOutputFile(
      const Settings* settings,
      const SubstitutionList& list,
      const std::vector<SourceFile>& sources,
      std::vector<OutputFile>* output);

  
  
  
  
  // for {{source}} will be written since that maps to Ninja's implicit $in
  
  static void WriteNinjaVariablesForSource(
      const Settings* settings,
      const SourceFile& source,
      const std::vector<SubstitutionType>& types,
      const EscapeOptions& escape_options,
      std::ostream& out);

  
  
  
  
  static std::string GetSourceSubstitution(
      const Settings* settings,
      const SourceFile& source,
      SubstitutionType type,
      OutputStyle output_style,
      const SourceDir& relative_to);

  
  
  
  
  static OutputFile ApplyPatternToTargetAsOutputFile(
      const Target* target,
      const Tool* tool,
      const SubstitutionPattern& pattern);
  static void ApplyListToTargetAsOutputFile(
      const Target* target,
      const Tool* tool,
      const SubstitutionList& list,
      std::vector<OutputFile>* output);

  
  
  
  
  static bool GetTargetSubstitution(
      const Target* target,
      SubstitutionType type,
      std::string* result);
  static std::string GetTargetSubstitution(
      const Target* target,
      SubstitutionType type);

  
  
  
  

  static OutputFile ApplyPatternToCompilerAsOutputFile(
      const Target* target,
      const SourceFile& source,
      const SubstitutionPattern& pattern);
  static void ApplyListToCompilerAsOutputFile(
      const Target* target,
      const SourceFile& source,
      const SubstitutionList& list,
      std::vector<OutputFile>* output);

  
  
  
  static std::string GetCompilerSubstitution(
      const Target* target,
      const SourceFile& source,
      SubstitutionType type);

  

  static OutputFile ApplyPatternToLinkerAsOutputFile(
      const Target* target,
      const Tool* tool,
      const SubstitutionPattern& pattern);
  static void ApplyListToLinkerAsOutputFile(
      const Target* target,
      const Tool* tool,
      const SubstitutionList& list,
      std::vector<OutputFile>* output);

  
  
  
  static std::string GetLinkerSubstitution(
      const Target* target,
      const Tool* tool,
      SubstitutionType type);
};

#endif  
