// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_WEBSTORE_STARTUP_INSTALLER_H_
#define CHROME_BROWSER_EXTENSIONS_WEBSTORE_STARTUP_INSTALLER_H_

#include "chrome/browser/extensions/webstore_install_with_prompt.h"

namespace extensions {

class WebstoreStartupInstaller : public WebstoreInstallWithPrompt {
 public:
  WebstoreStartupInstaller(const std::string& webstore_item_id,
                           Profile* profile,
                           bool show_prompt,
                           const Callback& callback);

 protected:
  friend class base::RefCountedThreadSafe<WebstoreStartupInstaller>;
  FRIEND_TEST_ALL_PREFIXES(WebstoreStartupInstallerTest, DomainVerification);

  virtual ~WebstoreStartupInstaller();

  
  virtual scoped_refptr<ExtensionInstallPrompt::Prompt> CreateInstallPrompt()
      const OVERRIDE;

 private:
  bool show_prompt_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(WebstoreStartupInstaller);
};

}  

#endif  
