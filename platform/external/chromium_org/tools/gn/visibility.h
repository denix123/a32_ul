// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_VISIBILITY_H_
#define TOOLS_GN_VISIBILITY_H_

#include <vector>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "tools/gn/label_pattern.h"
#include "tools/gn/source_dir.h"

class Err;
class Item;
class Label;
class Scope;
class Value;

class Visibility {
 public:
  
  Visibility();
  ~Visibility();

  
  
  bool Set(const SourceDir& current_dir, const Value& value, Err* err);

  
  void SetPublic();

  
  void SetPrivate(const SourceDir& current_dir);

  
  
  bool CanSeeMe(const Label& label) const;

  
  
  
  
  std::string Describe(int indent, bool include_brackets) const;

  
  
  static bool CheckItemVisibility(const Item* from, const Item* to, Err* err);

  
  
  static bool FillItemVisibility(Item* item, Scope* scope, Err* err);

 private:
  std::vector<LabelPattern> patterns_;

  DISALLOW_COPY_AND_ASSIGN(Visibility);
};

#endif  
