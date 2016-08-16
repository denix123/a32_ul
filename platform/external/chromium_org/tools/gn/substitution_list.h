// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_SUBSTUTITION_LIST_H
#define TOOLS_GN_SUBSTUTITION_LIST_H

#include <string>
#include <vector>

#include "tools/gn/substitution_pattern.h"

class SubstitutionList {
 public:
  SubstitutionList();
  ~SubstitutionList();

  bool Parse(const Value& value, Err* err);
  bool Parse(const std::vector<std::string>& values,
             const ParseNode* origin,
             Err* err);

  
  static SubstitutionList MakeForTest(
      const char* a,
      const char* b = NULL,
      const char* c = NULL);

  const std::vector<SubstitutionPattern>& list() const { return list_; }

  
  
  const std::vector<SubstitutionType>& required_types() const {
    return required_types_;
  }

  void FillRequiredTypes(SubstitutionBits* bits) const;

 private:
  std::vector<SubstitutionPattern> list_;

  std::vector<SubstitutionType> required_types_;
};

#endif  
