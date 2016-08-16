// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GOOGLE_GOOGLE_BRAND_H__
#define CHROME_BROWSER_GOOGLE_GOOGLE_BRAND_H__

#include <string>

#include "base/basictypes.h"

class GURL;

namespace google_brand {

bool GetBrand(std::string* brand);

bool GetReactivationBrand(std::string* brand);

bool IsOrganic(const std::string& brand);

bool IsOrganicFirstRun(const std::string& brand);

bool IsInternetCafeBrandCode(const std::string& brand);

class BrandForTesting {
 public:
  explicit BrandForTesting(const std::string& brand);
  ~BrandForTesting();

 private:
  std::string brand_;
  DISALLOW_COPY_AND_ASSIGN(BrandForTesting);
};

}  

#endif  
