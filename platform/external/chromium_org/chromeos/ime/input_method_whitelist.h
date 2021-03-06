// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_IME_INPUT_METHOD_WHITELIST_H_
#define CHROMEOS_IME_INPUT_METHOD_WHITELIST_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"

namespace chromeos {
namespace input_method {

class InputMethodDescriptor;
typedef std::vector<InputMethodDescriptor> InputMethodDescriptors;

class CHROMEOS_EXPORT InputMethodWhitelist {
 public:
  InputMethodWhitelist();
  ~InputMethodWhitelist();

  
  bool InputMethodIdIsWhitelisted(const std::string& input_method_id) const;

  
  
  
  scoped_ptr<InputMethodDescriptors> GetSupportedInputMethods() const;

 private:
  std::set<std::string> supported_input_methods_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodWhitelist);
};

}  
}  

#endif  
