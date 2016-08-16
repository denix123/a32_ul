// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_TARGET_H_
#define TOOLS_GN_TARGET_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/strings/string_piece.h"
#include "base/synchronization/lock.h"
#include "tools/gn/action_values.h"
#include "tools/gn/config_values.h"
#include "tools/gn/item.h"
#include "tools/gn/label_ptr.h"
#include "tools/gn/ordered_set.h"
#include "tools/gn/output_file.h"
#include "tools/gn/source_file.h"
#include "tools/gn/unique_vector.h"

class InputFile;
class Settings;
class Token;
class Toolchain;

class Target : public Item {
 public:
  enum OutputType {
    UNKNOWN,
    GROUP,
    EXECUTABLE,
    SHARED_LIBRARY,
    STATIC_LIBRARY,
    SOURCE_SET,
    COPY_FILES,
    ACTION,
    ACTION_FOREACH,
  };
  typedef std::vector<SourceFile> FileList;
  typedef std::vector<std::string> StringVector;

  Target(const Settings* settings, const Label& label);
  virtual ~Target();

  
  static const char* GetStringForOutputType(OutputType type);

  
  virtual Target* AsTarget() OVERRIDE;
  virtual const Target* AsTarget() const OVERRIDE;
  virtual bool OnResolved(Err* err) OVERRIDE;

  OutputType output_type() const { return output_type_; }
  void set_output_type(OutputType t) { output_type_ = t; }

  
  bool IsLinkable() const;

  
  bool IsFinal() const;

  
  
  const std::string& output_name() const { return output_name_; }
  void set_output_name(const std::string& name) { output_name_ = name; }

  
  
  
  
  
  
  std::string GetComputedOutputName(bool include_prefix) const;

  const std::string& output_extension() const { return output_extension_; }
  void set_output_extension(const std::string& extension) {
    output_extension_ = extension;
  }

  const FileList& sources() const { return sources_; }
  FileList& sources() { return sources_; }

  
  
  bool all_headers_public() const { return all_headers_public_; }
  void set_all_headers_public(bool p) { all_headers_public_ = p; }

  
  
  const FileList& public_headers() const { return public_headers_; }
  FileList& public_headers() { return public_headers_; }

  
  bool check_includes() const { return check_includes_; }
  void set_check_includes(bool ci) { check_includes_ = ci; }

  
  bool complete_static_lib() const { return complete_static_lib_; }
  void set_complete_static_lib(bool complete) {
    DCHECK_EQ(STATIC_LIBRARY, output_type_);
    complete_static_lib_ = complete;
  }

  bool testonly() const { return testonly_; }
  void set_testonly(bool value) { testonly_ = value; }

  
  const FileList& inputs() const { return inputs_; }
  FileList& inputs() { return inputs_; }

  
  const FileList& data() const { return data_; }
  FileList& data() { return data_; }

  
  
  bool hard_dep() const {
    return output_type_ == ACTION ||
           output_type_ == ACTION_FOREACH ||
           output_type_ == COPY_FILES;
  }

  
  const LabelTargetVector& private_deps() const { return private_deps_; }
  LabelTargetVector& private_deps() { return private_deps_; }

  
  const LabelTargetVector& public_deps() const { return public_deps_; }
  LabelTargetVector& public_deps() { return public_deps_; }

  
  const LabelTargetVector& data_deps() const { return data_deps_; }
  LabelTargetVector& data_deps() { return data_deps_; }

  
  
  const UniqueVector<LabelConfigPair>& configs() const { return configs_; }
  UniqueVector<LabelConfigPair>& configs() { return configs_; }

  
  
  
  const UniqueVector<LabelConfigPair>& all_dependent_configs() const {
    return all_dependent_configs_;
  }
  UniqueVector<LabelConfigPair>& all_dependent_configs() {
    return all_dependent_configs_;
  }

  
  
  const UniqueVector<LabelConfigPair>& public_configs() const {
    return public_configs_;
  }
  UniqueVector<LabelConfigPair>& public_configs() {
    return public_configs_;
  }

  
  
  const UniqueVector<LabelTargetPair>& forward_dependent_configs() const {
    return forward_dependent_configs_;
  }
  UniqueVector<LabelTargetPair>& forward_dependent_configs() {
    return forward_dependent_configs_;
  }

  
  const std::set<Label>& allow_circular_includes_from() const {
    return allow_circular_includes_from_;
  }
  std::set<Label>& allow_circular_includes_from() {
    return allow_circular_includes_from_;
  }

  const UniqueVector<const Target*>& inherited_libraries() const {
    return inherited_libraries_;
  }

  
  ConfigValues& config_values() { return config_values_; }
  const ConfigValues& config_values() const { return config_values_; }

  ActionValues& action_values() { return action_values_; }
  const ActionValues& action_values() const { return action_values_; }

  const OrderedSet<SourceDir>& all_lib_dirs() const { return all_lib_dirs_; }
  const OrderedSet<std::string>& all_libs() const { return all_libs_; }

  const std::set<const Target*>& recursive_hard_deps() const {
    return recursive_hard_deps_;
  }

  
  
  
  const Toolchain* toolchain() const { return toolchain_; }

  
  
  
  
  bool SetToolchain(const Toolchain* toolchain, Err* err = NULL);

  
  
  
  
  
  
  
  
  
  
  
  
  
  const OutputFile& link_output_file() const {
    return link_output_file_;
  }
  const OutputFile& dependency_output_file() const {
    return dependency_output_file_;
  }

 private:
  
  
  void PullDependentTargetInfo();

  
  
  void PullForwardedDependentConfigs();
  void PullForwardedDependentConfigsFrom(const Target* from);
  void PullRecursiveHardDeps();

  
  void FillOutputFiles();

  
  bool CheckVisibility(Err* err) const;
  bool CheckTestonly(Err* err) const;
  bool CheckNoNestedStaticLibs(Err* err) const;

  OutputType output_type_;
  std::string output_name_;
  std::string output_extension_;

  FileList sources_;
  bool all_headers_public_;
  FileList public_headers_;
  bool check_includes_;
  bool complete_static_lib_;
  bool testonly_;
  FileList inputs_;
  FileList data_;

  bool hard_dep_;

  LabelTargetVector private_deps_;
  LabelTargetVector public_deps_;
  LabelTargetVector data_deps_;

  UniqueVector<LabelConfigPair> configs_;
  UniqueVector<LabelConfigPair> all_dependent_configs_;
  UniqueVector<LabelConfigPair> public_configs_;
  UniqueVector<LabelTargetPair> forward_dependent_configs_;

  std::set<Label> allow_circular_includes_from_;

  bool external_;

  
  
  
  
  
  UniqueVector<const Target*> inherited_libraries_;

  
  
  OrderedSet<SourceDir> all_lib_dirs_;
  OrderedSet<std::string> all_libs_;

  
  
  std::set<const Target*> recursive_hard_deps_;

  ConfigValues config_values_;  
  ActionValues action_values_;  

  
  const Toolchain* toolchain_;

  
  OutputFile link_output_file_;
  OutputFile dependency_output_file_;

  DISALLOW_COPY_AND_ASSIGN(Target);
};

namespace BASE_HASH_NAMESPACE {

#if defined(COMPILER_GCC)
template<> struct hash<const Target*> {
  std::size_t operator()(const Target* t) const {
    return reinterpret_cast<std::size_t>(t);
  }
};
#elif defined(COMPILER_MSVC)
inline size_t hash_value(const Target* t) {
  return reinterpret_cast<size_t>(t);
}
#endif  

}  

#endif  
