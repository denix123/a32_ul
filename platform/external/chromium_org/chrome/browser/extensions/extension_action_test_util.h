// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_TEST_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ACTION_TEST_UTIL_H_

#include "base/basictypes.h"

namespace content {
class WebContents;
}

namespace extensions {
namespace extension_action_test_util {


size_t GetVisiblePageActionCount(content::WebContents* web_contents);

size_t GetTotalPageActionCount(content::WebContents* web_contents);

}  
}  

#endif  
