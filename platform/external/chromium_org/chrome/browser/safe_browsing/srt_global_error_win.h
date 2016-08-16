// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_SRT_GLOBAL_ERROR_WIN_H_
#define CHROME_BROWSER_SAFE_BROWSING_SRT_GLOBAL_ERROR_WIN_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/global_error/global_error.h"

class GlobalErrorBubbleViewBase;
class GlobalErrorService;

class SRTGlobalError : public GlobalErrorWithStandardBubble,
                       public base::SupportsWeakPtr<SRTGlobalError> {
 public:
  explicit SRTGlobalError(GlobalErrorService* global_error_service);
  virtual ~SRTGlobalError();

  
  virtual bool HasMenuItem() OVERRIDE;
  virtual int MenuItemCommandID() OVERRIDE;
  virtual base::string16 MenuItemLabel() OVERRIDE;
  virtual void ExecuteMenuItem(Browser* browser) OVERRIDE;
  virtual void ShowBubbleView(Browser* browser) OVERRIDE;

  
  virtual base::string16 GetBubbleViewTitle() OVERRIDE;
  virtual std::vector<base::string16> GetBubbleViewMessages() OVERRIDE;
  virtual base::string16 GetBubbleViewAcceptButtonLabel() OVERRIDE;
  virtual base::string16 GetBubbleViewCancelButtonLabel() OVERRIDE;
  virtual void OnBubbleViewDidClose(Browser* browser) OVERRIDE;
  virtual void BubbleViewAcceptButtonPressed(Browser* browser) OVERRIDE;
  virtual void BubbleViewCancelButtonPressed(Browser* browser) OVERRIDE;
  virtual bool ShouldCloseOnDeactivate() const OVERRIDE;

 private:
  
  void DismissGlobalError();

  
  GlobalErrorService* global_error_service_;

  DISALLOW_COPY_AND_ASSIGN(SRTGlobalError);
};

#endif  
