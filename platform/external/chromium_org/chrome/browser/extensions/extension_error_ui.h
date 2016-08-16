// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_UI_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_ERROR_UI_H_

#include <vector>

#include "base/macros.h"
#include "base/strings/string16.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionSet;

class ExtensionErrorUI {
 public:
  class Delegate {
   public:
    
    virtual content::BrowserContext* GetContext() = 0;

    
    virtual const ExtensionSet& GetExternalExtensions() = 0;

    
    virtual const ExtensionSet& GetBlacklistedExtensions() = 0;

    
    virtual void OnAlertDetails() = 0;

    
    virtual void OnAlertAccept() = 0;

    
    virtual void OnAlertClosed() = 0;
  };

  static ExtensionErrorUI* Create(Delegate* delegate);

  virtual ~ExtensionErrorUI();

  
  
  virtual bool ShowErrorInBubbleView() = 0;

  
  
  
  
  virtual void ShowExtensions() = 0;

  
  
  virtual void Close() = 0;

 protected:
  explicit ExtensionErrorUI(Delegate* delegate);

  
  base::string16 GetBubbleViewTitle();
  std::vector<base::string16> GetBubbleViewMessages();
  base::string16 GetBubbleViewAcceptButtonLabel();
  base::string16 GetBubbleViewCancelButtonLabel();

  
  
  void BubbleViewDidClose();  
  void BubbleViewAcceptButtonPressed();
  void BubbleViewCancelButtonPressed();

 private:
  base::string16 GenerateMessage();

  Delegate* delegate_;

  base::string16 message_;  

  DISALLOW_COPY_AND_ASSIGN(ExtensionErrorUI);
};

}  

#endif  
