// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_UI_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_UI_UTIL_H_

#include "chrome/browser/extensions/webstore_installer.h"

class Profile;

namespace extensions {
namespace install_ui {

void ShowPostInstallUIForApproval(Profile* profile,
                                  const WebstoreInstaller::Approval& approval,
                                  const Extension* extension);

}  
}  

#endif  
