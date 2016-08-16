// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_I18N_STREAMING_UTF8_VALIDATOR_H_
#define BASE_I18N_STREAMING_UTF8_VALIDATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/i18n/base_i18n_export.h"

namespace base {

class BASE_I18N_EXPORT StreamingUtf8Validator {
 public:
  
  
  
  
  enum State {
    VALID_ENDPOINT,
    VALID_MIDPOINT,
    INVALID
  };

  StreamingUtf8Validator() : state_(0u) {}
  

  
  
  
  
  
  State AddBytes(const char* data, size_t size);

  
  void Reset();

  
  
  static bool Validate(const std::string& string);

 private:
  
  
  
  uint8 state_;

  
  
  DISALLOW_COPY_AND_ASSIGN(StreamingUtf8Validator);
};

}  

#endif  
