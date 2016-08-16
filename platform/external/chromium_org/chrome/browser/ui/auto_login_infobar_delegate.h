// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTO_LOGIN_INFOBAR_DELEGATE_H_
#define CHROME_BROWSER_UI_AUTO_LOGIN_INFOBAR_DELEGATE_H_

#include <string>
#include "components/auto_login_parser/auto_login_parser.h"
#include "components/infobars/core/confirm_infobar_delegate.h"
#include "components/signin/core/browser/signin_manager.h"

class PrefService;
class Profile;

namespace content {
class NavigationController;
class WebContents;
}

class AutoLoginInfoBarDelegate : public ConfirmInfoBarDelegate,
                                 public SigninManagerBase::Observer {
 public:
  struct Params {
    
    auto_login_parser::HeaderData header;

    
    
    
    std::string username;
  };

  
  
  
  static bool Create(content::WebContents* web_contents, const Params& params);

 protected:
  
  enum Actions {
    SHOWN,       
    ACCEPTED,    
    REJECTED,    
    DISMISSED,   
    IGNORED,     
    LEARN_MORE,  
    HISTOGRAM_BOUNDING_VALUE
  };

  AutoLoginInfoBarDelegate(const Params& params, Profile* profile);
  virtual ~AutoLoginInfoBarDelegate();

  void RecordHistogramAction(Actions action);

 private:
  
  virtual void InfoBarDismissed() OVERRIDE;
  virtual int GetIconID() const OVERRIDE;
  virtual Type GetInfoBarType() const OVERRIDE;
  virtual AutoLoginInfoBarDelegate* AsAutoLoginInfoBarDelegate() OVERRIDE;
  virtual base::string16 GetMessageText() const OVERRIDE;
  virtual base::string16 GetButtonLabel(InfoBarButton button) const OVERRIDE;
  virtual bool Accept() OVERRIDE;
  virtual bool Cancel() OVERRIDE;

  
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  const Params params_;

  Profile* profile_;

  
  bool button_pressed_;

  DISALLOW_COPY_AND_ASSIGN(AutoLoginInfoBarDelegate);
};

#endif  
