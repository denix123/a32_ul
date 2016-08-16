// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_SUBSTITUTION_TYPE_H_
#define TOOLS_GN_SUBSTITUTION_TYPE_H_

#include <vector>

class Err;
class ParseNode;

enum SubstitutionType {
  SUBSTITUTION_LITERAL = 0,

  
  
  SUBSTITUTION_FIRST_PATTERN,

  
  SUBSTITUTION_SOURCE = SUBSTITUTION_FIRST_PATTERN,  
  SUBSTITUTION_OUTPUT,  

  
  SUBSTITUTION_SOURCE_NAME_PART,  
  SUBSTITUTION_SOURCE_FILE_PART,  
  SUBSTITUTION_SOURCE_DIR,  
  SUBSTITUTION_SOURCE_ROOT_RELATIVE_DIR,  
  SUBSTITUTION_SOURCE_GEN_DIR,  
  SUBSTITUTION_SOURCE_OUT_DIR,  

  
  
  SUBSTITUTION_LABEL,  
  SUBSTITUTION_ROOT_GEN_DIR,  
  SUBSTITUTION_ROOT_OUT_DIR,  
  SUBSTITUTION_TARGET_GEN_DIR,  
  SUBSTITUTION_TARGET_OUT_DIR,  
  SUBSTITUTION_TARGET_OUTPUT_NAME,  

  
  SUBSTITUTION_CFLAGS,  
  SUBSTITUTION_CFLAGS_C,  
  SUBSTITUTION_CFLAGS_CC,  
  SUBSTITUTION_CFLAGS_OBJC,  
  SUBSTITUTION_CFLAGS_OBJCC,  
  SUBSTITUTION_DEFINES,  
  SUBSTITUTION_INCLUDE_DIRS,  

  
  SUBSTITUTION_LINKER_INPUTS,  
  SUBSTITUTION_LINKER_INPUTS_NEWLINE,  
  SUBSTITUTION_LDFLAGS,  
  SUBSTITUTION_LIBS,  
  SUBSTITUTION_OUTPUT_EXTENSION,  
  SUBSTITUTION_SOLIBS,  

  SUBSTITUTION_NUM_TYPES  
};

extern const char* kSubstitutionNames[SUBSTITUTION_NUM_TYPES];

extern const char* kSubstitutionNinjaNames[SUBSTITUTION_NUM_TYPES];

struct SubstitutionBits {
  SubstitutionBits();

  
  
  void MergeFrom(const SubstitutionBits& other);

  
  
  void FillVector(std::vector<SubstitutionType>* vect) const;

  bool used[SUBSTITUTION_NUM_TYPES];
};

bool SubstitutionIsInOutputDir(SubstitutionType type);

bool IsValidSourceSubstitution(SubstitutionType type);
bool IsValidToolSubstutition(SubstitutionType type);
bool IsValidCompilerSubstitution(SubstitutionType type);
bool IsValidCompilerOutputsSubstitution(SubstitutionType type);
bool IsValidLinkerSubstitution(SubstitutionType type);
bool IsValidLinkerOutputsSubstitution(SubstitutionType type);
bool IsValidCopySubstitution(SubstitutionType type);

bool EnsureValidSourcesSubstitutions(
    const std::vector<SubstitutionType>& types,
    const ParseNode* origin,
    Err* err);

#endif  
