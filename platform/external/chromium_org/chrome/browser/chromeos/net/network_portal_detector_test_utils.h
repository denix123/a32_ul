// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_NET_NETWORK_PORTAL_DETECTOR_TEST_UTILS_H_
#define CHROME_BROWSER_CHROMEOS_NET_NETWORK_PORTAL_DETECTOR_TEST_UTILS_H_

#include <string>
#include <vector>

#include "base/macros.h"

namespace base {
class HistogramSamples;
}

namespace chromeos {

class EnumHistogramChecker {
 public:
  EnumHistogramChecker(const std::string& histogram, int count,
                       base::HistogramSamples* base);
  ~EnumHistogramChecker();

  
  
  EnumHistogramChecker* Expect(int key, int value);

  
  bool Check();

 private:
  
  std::string histogram_;

  
  std::vector<int> expect_;

  
  
  base::HistogramSamples* base_;

  DISALLOW_COPY_AND_ASSIGN(EnumHistogramChecker);
};

}  

#endif  
