// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_GN_C_INCLUDE_ITERATOR_H_
#define TOOLS_GN_C_INCLUDE_ITERATOR_H_

#include "base/basictypes.h"
#include "base/strings/string_piece.h"

class InputFile;
class LocationRange;

class CIncludeIterator {
 public:
  
  CIncludeIterator(const InputFile* input);
  ~CIncludeIterator();

  
  
  
  bool GetNextIncludeString(base::StringPiece* out, LocationRange* location);

  
  
  static const int kMaxNonIncludeLines;

 private:
  
  
  bool GetNextLine(base::StringPiece* line, int* line_number);

  const InputFile* input_file_;

  
  base::StringPiece file_;

  
  size_t offset_;

  int line_number_;  

  
  
  int lines_since_last_include_;

  DISALLOW_COPY_AND_ASSIGN(CIncludeIterator);
};

#endif  
