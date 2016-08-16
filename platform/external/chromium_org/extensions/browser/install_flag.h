// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_INSTALL_FLAG_H_
#define EXTENSIONS_BROWSER_INSTALL_FLAG_H_

namespace extensions {

enum InstallFlag {
  kInstallFlagNone = 0,

  
  
  kInstallFlagHasRequirementErrors = 1 << 0,

  
  kInstallFlagIsBlacklistedForMalware = 1 << 1,

  
  kInstallFlagIsEphemeral = 1 << 2,

  
  kInstallFlagInstallImmediately = 1 << 3,

  
  kInstallFlagDoNotSync = 1 << 4,
};

}  

#endif  
