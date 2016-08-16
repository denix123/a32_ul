// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTERNAL_INSTALL_ERROR_H_
#define CHROME_BROWSER_EXTENSIONS_EXTERNAL_INSTALL_ERROR_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/extensions/extension_install_prompt.h"
#include "chrome/browser/extensions/webstore_data_fetcher_delegate.h"

class Browser;
class ExtensionInstallUI;
class GlobalError;
class GlobalErrorService;

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
class ExternalInstallManager;
class WebstoreDataFetcher;

class ExternalInstallError : public ExtensionInstallPrompt::Delegate,
                             public WebstoreDataFetcherDelegate {
 public:
  
  
  
  
  enum AlertType {
    BUBBLE_ALERT,
    MENU_ALERT
  };

  ExternalInstallError(content::BrowserContext* browser_context,
                       const std::string& extension_id,
                       AlertType error_type,
                       ExternalInstallManager* manager);
  virtual ~ExternalInstallError();

  
  virtual void InstallUIProceed() OVERRIDE;
  virtual void InstallUIAbort(bool user_initiated) OVERRIDE;

  
  
  void ShowDialog(Browser* browser);

  
  const Extension* GetExtension() const;

  const std::string& extension_id() const { return extension_id_; }
  AlertType alert_type() const { return alert_type_; }

 private:
  
  virtual void OnWebstoreRequestFailure() OVERRIDE;
  virtual void OnWebstoreResponseParseSuccess(
      scoped_ptr<base::DictionaryValue> webstore_data) OVERRIDE;
  virtual void OnWebstoreResponseParseFailure(
      const std::string& error) OVERRIDE;

  
  void OnFetchComplete();

  
  
  void OnDialogReady(const ExtensionInstallPrompt::ShowParams& show_params,
                     ExtensionInstallPrompt::Delegate* prompt_delegate,
                     scoped_refptr<ExtensionInstallPrompt::Prompt> prompt);

  
  content::BrowserContext* browser_context_;

  
  std::string extension_id_;

  
  AlertType alert_type_;

  
  ExternalInstallManager* manager_;

  
  GlobalErrorService* error_service_;

  
  scoped_ptr<ExtensionInstallPrompt> install_ui_;
  scoped_refptr<ExtensionInstallPrompt::Prompt> prompt_;

  
  
  scoped_ptr<GlobalError> global_error_;

  
  
  scoped_ptr<WebstoreDataFetcher> webstore_data_fetcher_;

  base::WeakPtrFactory<ExternalInstallError> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExternalInstallError);
};

}  

#endif  
