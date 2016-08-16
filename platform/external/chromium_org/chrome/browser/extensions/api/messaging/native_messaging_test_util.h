// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_MESSAGING_NATIVE_MESSAGING_TEST_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_API_MESSAGING_NATIVE_MESSAGING_TEST_UTIL_H_

#include "base/files/scoped_temp_dir.h"
#include "base/memory/scoped_ptr.h"

#if defined(OS_WIN)
#include "base/test/test_reg_util_win.h"
#else
#include "base/test/scoped_path_override.h"
#endif

namespace extensions {

class ScopedTestNativeMessagingHost {
 public:
  static const char kHostName[];
  static const char kBinaryMissingHostName[];
  static const char kExtensionId[];

  ScopedTestNativeMessagingHost();
  ~ScopedTestNativeMessagingHost();

  void RegisterTestHost(bool user_level);

 private:
  base::ScopedTempDir temp_dir_;

#if defined(OS_WIN)
  registry_util::RegistryOverrideManager registry_override_;
#else
  scoped_ptr<base::ScopedPathOverride> path_override_;
#endif

  DISALLOW_COPY_AND_ASSIGN(ScopedTestNativeMessagingHost);
};

}  

#endif  