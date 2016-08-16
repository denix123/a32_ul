// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_CONTROLLER_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/extension_error_ui.h"
#include "extensions/common/extension_set.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionErrorController : public ExtensionErrorUI::Delegate {
 public:
  typedef ExtensionErrorUI* (*UICreateMethod)(ExtensionErrorUI::Delegate*);

  ExtensionErrorController(content::BrowserContext* context, bool is_first_run);
  virtual ~ExtensionErrorController();

  void ShowErrorIfNeeded();

  
  static void SetUICreateMethodForTesting(UICreateMethod method);

 private:
  
  virtual content::BrowserContext* GetContext() OVERRIDE;
  virtual const ExtensionSet& GetExternalExtensions() OVERRIDE;
  virtual const ExtensionSet& GetBlacklistedExtensions() OVERRIDE;
  virtual void OnAlertDetails() OVERRIDE;
  virtual void OnAlertAccept() OVERRIDE;
  virtual void OnAlertClosed() OVERRIDE;

  
  
  void IdentifyAlertableExtensions();

  
  
  ExtensionSet external_extensions_;

  
  ExtensionSet blacklisted_extensions_;

  
  scoped_ptr<ExtensionErrorUI> error_ui_;

  
  content::BrowserContext* browser_context_;

  
  
  bool is_first_run_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionErrorController);
};

}  

#endif  
