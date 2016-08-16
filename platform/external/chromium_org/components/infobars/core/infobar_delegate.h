// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INFOBARS_CORE_INFOBAR_DELEGATE_H_
#define COMPONENTS_INFOBARS_CORE_INFOBAR_DELEGATE_H_

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "ui/base/window_open_disposition.h"

class AutoLoginInfoBarDelegate;
class ConfirmInfoBarDelegate;
class ExtensionInfoBarDelegate;
class InsecureContentInfoBarDelegate;
class MediaStreamInfoBarDelegate;
class PopupBlockedInfoBarDelegate;
class RegisterProtocolHandlerInfoBarDelegate;
class ScreenCaptureInfoBarDelegate;
class ThemeInstalledInfoBarDelegate;
class ThreeDAPIInfoBarDelegate;

namespace translate {
class TranslateInfoBarDelegate;
}

namespace gfx {
class Image;
}

namespace infobars {

class InfoBar;

class InfoBarDelegate {
 public:
  
  
  enum Type {
    WARNING_TYPE,
    PAGE_ACTION_TYPE,
  };

  enum InfoBarAutomationType {
    CONFIRM_INFOBAR,
    PASSWORD_INFOBAR,
    RPH_INFOBAR,
    UNKNOWN_INFOBAR,
  };

  
  
  struct NavigationDetails {
    
    int entry_id;
    
    bool is_navigation_to_different_page;
    
    bool did_replace_entry;
    
    bool is_main_frame;
    bool is_reload;
    bool is_redirect;
  };

  
  static const int kNoIconID;

  
  
  virtual ~InfoBarDelegate();

  virtual InfoBarAutomationType GetInfoBarAutomationType() const;

  
  
  
  
  
  
  virtual bool EqualsDelegate(InfoBarDelegate* delegate) const;

  
  
  
  
  
  virtual bool ShouldExpire(const NavigationDetails& details) const;

  
  virtual void InfoBarDismissed();

  
  
  virtual int GetIconID() const;

  
  
  virtual Type GetInfoBarType() const;

  
  virtual AutoLoginInfoBarDelegate* AsAutoLoginInfoBarDelegate();
  virtual ConfirmInfoBarDelegate* AsConfirmInfoBarDelegate();
  virtual ExtensionInfoBarDelegate* AsExtensionInfoBarDelegate();
  virtual InsecureContentInfoBarDelegate* AsInsecureContentInfoBarDelegate();
  virtual MediaStreamInfoBarDelegate* AsMediaStreamInfoBarDelegate();
  virtual PopupBlockedInfoBarDelegate* AsPopupBlockedInfoBarDelegate();
  virtual RegisterProtocolHandlerInfoBarDelegate*
      AsRegisterProtocolHandlerInfoBarDelegate();
  virtual ScreenCaptureInfoBarDelegate* AsScreenCaptureInfoBarDelegate();
  virtual ThemeInstalledInfoBarDelegate* AsThemePreviewInfobarDelegate();
  virtual translate::TranslateInfoBarDelegate* AsTranslateInfoBarDelegate();

  void set_infobar(InfoBar* infobar) { infobar_ = infobar; }

  
  
  void StoreActiveEntryUniqueID();

  
  
  virtual gfx::Image GetIcon() const;

 protected:
  InfoBarDelegate();

  
  virtual bool ShouldExpireInternal(const NavigationDetails& details) const;

  int contents_unique_id() const { return contents_unique_id_; }
  InfoBar* infobar() { return infobar_; }

 private:
  
  
  int contents_unique_id_;

  
  InfoBar* infobar_;

  DISALLOW_COPY_AND_ASSIGN(InfoBarDelegate);
};

}  

#endif  
