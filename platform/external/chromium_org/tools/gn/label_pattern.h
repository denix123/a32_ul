// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_LABEL_PATTERN_H_
#define TOOLS_GN_LABEL_PATTERN_H_

#include "base/strings/string_piece.h"
#include "tools/gn/label.h"
#include "tools/gn/source_dir.h"

class Err;
class Value;

extern const char kLabelPattern_Help[];

class LabelPattern {
 public:
  enum Type {
    MATCH = 1,  
    DIRECTORY,  
    RECURSIVE_DIRECTORY  
                         
  };

  LabelPattern();
  LabelPattern(Type type,
               const SourceDir& dir,
               const base::StringPiece& name,
               const Label& toolchain_label);
  ~LabelPattern();

  
  
  static LabelPattern GetPattern(const SourceDir& current_dir,
                                 const Value& value,
                                 Err* err);

  
  bool Matches(const Label& label) const;

  
  std::string Describe() const;

  Type type() const { return type_; }

  const SourceDir& dir() const { return dir_; }
  const std::string& name() const { return name_; }

  const Label& toolchain() const { return toolchain_; }
  void set_toolchain(const Label& tc) { toolchain_ = tc; }

 private:
  
  
  Label toolchain_;

  Type type_;

  
  
  SourceDir dir_;

  
  
  std::string name_;
};

#endif  
