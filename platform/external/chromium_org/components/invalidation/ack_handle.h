// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_ACK_HANDLE_H_
#define COMPONENTS_INVALIDATION_ACK_HANDLE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "components/invalidation/invalidation_export.h"

namespace base {
class DictionaryValue;
}

namespace syncer {

class INVALIDATION_EXPORT AckHandle {
 public:
  static AckHandle CreateUnique();
  static AckHandle InvalidAckHandle();

  bool Equals(const AckHandle& other) const;

  scoped_ptr<base::DictionaryValue> ToValue() const;
  bool ResetFromValue(const base::DictionaryValue& value);

  bool IsValid() const;

  ~AckHandle();

 private:
  
  AckHandle(const std::string& state, base::Time timestamp);

  std::string state_;
  base::Time timestamp_;
};

}  

#endif  
