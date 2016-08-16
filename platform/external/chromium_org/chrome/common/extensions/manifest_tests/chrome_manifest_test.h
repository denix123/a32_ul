// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_MANIFEST_TESTS_CHROME_MANIFEST_TEST_H_
#define CHROME_COMMON_EXTENSIONS_MANIFEST_TESTS_CHROME_MANIFEST_TEST_H_

#include "base/macros.h"
#include "chrome/common/extensions/features/feature_channel.h"
#include "extensions/common/manifest_test.h"

class ChromeManifestTest : public extensions::ManifestTest {
 public:
  ChromeManifestTest();
  virtual ~ChromeManifestTest();

  
  virtual base::FilePath GetTestDataDir() OVERRIDE;

 private:
  
  
  
  
  
  
  extensions::ScopedCurrentChannel current_channel_;

  DISALLOW_COPY_AND_ASSIGN(ChromeManifestTest);
};

#endif  
