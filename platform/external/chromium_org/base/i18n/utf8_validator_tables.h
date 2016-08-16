// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_I18N_UTF8_VALIDATOR_TABLES_H_
#define BASE_I18N_UTF8_VALIDATOR_TABLES_H_

#include "base/basictypes.h"

namespace base {
namespace internal {

extern const uint8 kUtf8ValidatorTables[];

extern const size_t kUtf8ValidatorTablesSize;

enum {
  I18N_UTF8_VALIDATOR_INVALID_INDEX = 129
};

}  
}  

#endif  
