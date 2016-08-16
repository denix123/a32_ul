// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_TEST_SWITCHES_H_
#define CHROME_TEST_BASE_TEST_SWITCHES_H_

#include "build/build_config.h"

namespace switches {

extern const char kAlsoEmitSuccessLogs[];

#if defined(OS_WIN)
extern const char kAshBrowserTests[];
#endif

}  

#endif  
