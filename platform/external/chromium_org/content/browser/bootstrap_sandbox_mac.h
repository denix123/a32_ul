// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_BOOTSTRAP_SANDBOX_MAC_H_
#define CONTENT_BROWSER_BOOTSTRAP_SANDBOX_MAC_H_

namespace sandbox {
class BootstrapSandbox;
}

namespace content {

bool ShouldEnableBootstrapSandbox();

sandbox::BootstrapSandbox* GetBootstrapSandbox();

}  

#endif  
