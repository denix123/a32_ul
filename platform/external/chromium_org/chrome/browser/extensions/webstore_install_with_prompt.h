// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_WEBSTORE_INSTALL_WITH_PROMPT_H_
#define CHROME_BROWSER_EXTENSIONS_WEBSTORE_INSTALL_WITH_PROMPT_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/extensions/webstore_standalone_installer.h"
#include "content/public/browser/page_navigator.h"
#include "ui/gfx/native_widget_types.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}

namespace extensions {

class WebstoreInstallWithPrompt : public WebstoreStandaloneInstaller,
                                  public content::PageNavigator {
 public:
  
  
  WebstoreInstallWithPrompt(const std::string& webstore_item_id,
                            Profile* profile,
                            const Callback& callback);

  
  
  WebstoreInstallWithPrompt(const std::string& webstore_item_id,
                            Profile* profile,
                            gfx::NativeWindow parent_window,
                            const Callback& callback);

 protected:
  friend class base::RefCountedThreadSafe<WebstoreInstallWithPrompt>;
  virtual ~WebstoreInstallWithPrompt();

  void set_show_post_install_ui(bool show) { show_post_install_ui_ = show; }

  
  virtual bool CheckRequestorAlive() const OVERRIDE;
  virtual const GURL& GetRequestorURL() const OVERRIDE;
  virtual bool ShouldShowPostInstallUI() const OVERRIDE;
  virtual bool ShouldShowAppInstalledBubble() const OVERRIDE;
  virtual content::WebContents* GetWebContents() const OVERRIDE;
  virtual scoped_refptr<ExtensionInstallPrompt::Prompt> CreateInstallPrompt()
      const OVERRIDE;
  virtual scoped_ptr<ExtensionInstallPrompt> CreateInstallUI() OVERRIDE;
  virtual bool CheckInlineInstallPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;
  virtual bool CheckRequestorPermitted(
      const base::DictionaryValue& webstore_data,
      std::string* error) const OVERRIDE;

  
  virtual content::WebContents* OpenURL(
      const content::OpenURLParams& params) OVERRIDE;

 private:
  bool show_post_install_ui_;

  GURL dummy_requestor_url_;

  
  scoped_ptr<content::WebContents> dummy_web_contents_;

  gfx::NativeWindow parent_window_;

  DISALLOW_COPY_AND_ASSIGN(WebstoreInstallWithPrompt);
};

}  

#endif  
