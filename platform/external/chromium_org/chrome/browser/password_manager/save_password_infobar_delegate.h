// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_SAVE_PASSWORD_INFOBAR_DELEGATE_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_SAVE_PASSWORD_INFOBAR_DELEGATE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/elapsed_timer.h"
#include "components/infobars/core/confirm_infobar_delegate.h"
#include "components/infobars/core/infobar_delegate.h"
#include "components/password_manager/core/browser/password_form_manager.h"
#include "components/password_manager/core/browser/password_manager_metrics_util.h"

namespace content {
class WebContents;
}

class SavePasswordInfoBarDelegate : public ConfirmInfoBarDelegate {
 public:
  
  
  
  
  
  
  static void Create(
      content::WebContents* web_contents,
      scoped_ptr<password_manager::PasswordFormManager> form_to_save,
      const std::string& uma_histogram_suffix);

  virtual ~SavePasswordInfoBarDelegate();

  
  
  void SetUseAdditionalPasswordAuthentication(
      bool use_additional_authentication);

 private:
  SavePasswordInfoBarDelegate(
      scoped_ptr<password_manager::PasswordFormManager> form_to_save,
      const std::string& uma_histogram_suffix);

  
  static scoped_ptr<infobars::InfoBar> CreateInfoBar(
      scoped_ptr<SavePasswordInfoBarDelegate> delegate);

  
  virtual bool ShouldExpire(const NavigationDetails& details) const OVERRIDE;

  
  virtual int GetIconID() const OVERRIDE;
  virtual Type GetInfoBarType() const OVERRIDE;
  virtual base::string16 GetMessageText() const OVERRIDE;
  virtual base::string16 GetButtonLabel(InfoBarButton button) const OVERRIDE;
  virtual bool Accept() OVERRIDE;
  virtual bool Cancel() OVERRIDE;
  virtual void InfoBarDismissed() OVERRIDE;

  virtual InfoBarAutomationType GetInfoBarAutomationType() const OVERRIDE;

  
  
  scoped_ptr<password_manager::PasswordFormManager> form_to_save_;

  
  password_manager::metrics_util::ResponseType infobar_response_;

  
  
  base::ElapsedTimer timer_;

  
  
  const std::string uma_histogram_suffix_;

  DISALLOW_COPY_AND_ASSIGN(SavePasswordInfoBarDelegate);
};

#endif  
