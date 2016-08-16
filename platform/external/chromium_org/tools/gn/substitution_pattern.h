// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_SUBSTITUTION_PATTERN_H_
#define TOOLS_GN_SUBSTITUTION_PATTERN_H_

#include <string>
#include <vector>

#include "tools/gn/substitution_type.h"

class BuildSettings;
class Err;
class ParseNode;
class Value;

class SubstitutionPattern {
 public:
  struct Subrange {
    Subrange();
    Subrange(SubstitutionType t, const std::string& l = std::string());
    ~Subrange();

    inline bool operator==(const Subrange& other) const {
      return type == other.type && literal == other.literal;
    }

    SubstitutionType type;

    
    std::string literal;
  };

  SubstitutionPattern();
  ~SubstitutionPattern();

  
  
  bool Parse(const Value& value, Err* err);
  bool Parse(const std::string& str, const ParseNode* origin, Err* err);

  
  
  static SubstitutionPattern MakeForTest(const char* str);

  
  std::string AsString() const;

  
  
  void FillRequiredTypes(SubstitutionBits* bits) const;

  
  
  
  bool IsInOutputDir(const BuildSettings* build_settings,
                     Err* err) const;

  
  
  const std::vector<SubstitutionType>& required_types() const {
    return required_types_;
  }

  const std::vector<Subrange>& ranges() const { return ranges_; }
  bool empty() const { return ranges_.empty(); }

 private:
  std::vector<Subrange> ranges_;
  const ParseNode* origin_;

  std::vector<SubstitutionType> required_types_;
};

#endif  
