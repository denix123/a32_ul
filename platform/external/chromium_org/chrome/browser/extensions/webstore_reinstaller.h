// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_WEBSTORE_REINSTALLER_H_
#define CHROME_BROWSER_EXTENSIONS_WEBSTORE_REINSTALLER_H_

#include "chrome/browser/extensions/webstore_standalone_installer.h"
#include "content/public/browser/web_contents_observer.h"

namespace extensions {

class WebstoreReinstaller : public WebstoreStandaloneInstaller,
                            public content::WebContentsObserver {
 public:
  WebstoreReinstaller(content::WebContents* web_contents,
                      const std::string& extension_id,
                      const WebstoreStandaloneInstaller::Callback& callback);

  
  
  void BeginReinstall();

 private:
  virtual ~WebstoreReinstaller();

  
  virtual bool CheckRequestorAlive() const OVERRIDE;
  virtual const GURL& GetRequestorURL() const OVERRIDE;
  virtual bool ShouldShowPostInstallUI() const OVERRIDE;
  virtual bool ShouldShowAppInstalledBubble() const OVERRIDE;
  virtual content::WebContents* GetWebContents() const OVERRIDE;
  virtual scoped_refptr<ExtensionInstallPrompt::Prompt> CreateInstallPrompt()
      const OVERRIDE;
  virtual bool CheckInlineInstallPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;
  virtual bool CheckRequestorPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;
  virtual void InstallUIProceed() OVERRIDE;

  
  virtual void WebContentsDestroyed() OVERRIDE;

  
  void OnDeletionDone();
};

}  

#endif  
