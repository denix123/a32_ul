// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_TOOLCHAIN_H_
#define TOOLS_GN_TOOLCHAIN_H_

#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "tools/gn/item.h"
#include "tools/gn/label_ptr.h"
#include "tools/gn/scope.h"
#include "tools/gn/source_file_type.h"
#include "tools/gn/substitution_type.h"
#include "tools/gn/tool.h"
#include "tools/gn/value.h"

class Toolchain : public Item {
 public:
  enum ToolType {
    TYPE_NONE = 0,
    TYPE_CC,
    TYPE_CXX,
    TYPE_OBJC,
    TYPE_OBJCXX,
    TYPE_RC,
    TYPE_ASM,
    TYPE_ALINK,
    TYPE_SOLINK,
    TYPE_LINK,
    TYPE_STAMP,
    TYPE_COPY,

    TYPE_NUMTYPES  
  };

  static const char* kToolCc;
  static const char* kToolCxx;
  static const char* kToolObjC;
  static const char* kToolObjCxx;
  static const char* kToolRc;
  static const char* kToolAsm;
  static const char* kToolAlink;
  static const char* kToolSolink;
  static const char* kToolLink;
  static const char* kToolStamp;
  static const char* kToolCopy;

  Toolchain(const Settings* settings, const Label& label);
  virtual ~Toolchain();

  
  virtual Toolchain* AsToolchain() OVERRIDE;
  virtual const Toolchain* AsToolchain() const OVERRIDE;

  
  static ToolType ToolNameToType(const base::StringPiece& str);
  static std::string ToolTypeToName(ToolType type);

  
  const Tool* GetTool(ToolType type) const;

  
  
  void SetTool(ToolType type, scoped_ptr<Tool> t);

  
  void ToolchainSetupComplete();

  
  const LabelTargetVector& deps() const { return deps_; }
  LabelTargetVector& deps() { return deps_; }

  
  
  
  
  Scope::KeyValueMap& args() { return args_; }
  const Scope::KeyValueMap& args() const { return args_; }

  
  static ToolType GetToolTypeForSourceType(SourceFileType type);
  const Tool* GetToolForSourceType(SourceFileType type);

  
  
  
  
  static ToolType GetToolTypeForTargetFinalOutput(const Target* target);
  const Tool* GetToolForTargetFinalOutput(const Target* target) const;

  const SubstitutionBits& substitution_bits() const {
    DCHECK(setup_complete_);
    return substitution_bits_;
  }

  void set_concurrent_links(int cl) { concurrent_links_ = cl; }
  int concurrent_links() const { return concurrent_links_; }

 private:
  scoped_ptr<Tool> tools_[TYPE_NUMTYPES];

  
  
  int concurrent_links_;

  bool setup_complete_;

  
  SubstitutionBits substitution_bits_;

  LabelTargetVector deps_;
  Scope::KeyValueMap args_;
};

#endif  
