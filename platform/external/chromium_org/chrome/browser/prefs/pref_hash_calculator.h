// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_PREF_HASH_CALCULATOR_H_
#define CHROME_BROWSER_PREFS_PREF_HASH_CALCULATOR_H_

#include <string>

#include "base/basictypes.h"

namespace base {
class Value;
}  

class PrefHashCalculator {
 public:
  enum ValidationResult {
    INVALID,
    VALID,
    
    VALID_SECURE_LEGACY,
  };

  
  
  
  PrefHashCalculator(const std::string& seed, const std::string& device_id);

  ~PrefHashCalculator();

  
  
  std::string Calculate(const std::string& path, const base::Value* value)
      const;

  
  
  ValidationResult Validate(const std::string& path,
                            const base::Value* value,
                            const std::string& hash) const;

 private:
  const std::string seed_;
  const std::string device_id_;
  const std::string legacy_device_id_;

  DISALLOW_COPY_AND_ASSIGN(PrefHashCalculator);
};

#endif  
