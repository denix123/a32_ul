// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_UNINSTALL_DIALOG_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_UNINSTALL_DIALOG_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/native_widget_types.h"

class Profile;

namespace base {
class MessageLoop;
}

namespace gfx {
class Image;
}

namespace extensions {
class Extension;

class ExtensionUninstallDialog
    : public base::SupportsWeakPtr<ExtensionUninstallDialog> {
 public:
  class Delegate {
   public:
    
    virtual void ExtensionUninstallAccepted() = 0;

    
    virtual void ExtensionUninstallCanceled() = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  static ExtensionUninstallDialog* Create(Profile* profile,
                                          gfx::NativeWindow parent,
                                          Delegate* delegate);

  virtual ~ExtensionUninstallDialog();

  
  
  
  
  void ConfirmUninstall(const Extension* extension);

  
  
  void ConfirmProgrammaticUninstall(const Extension* extension,
                                    const Extension* triggering_extension);

  std::string GetHeadingText();

 protected:
  
  ExtensionUninstallDialog(Profile* profile, Delegate* delegate);

  
  Profile* const profile_;

  
  Delegate* delegate_;

  
  const Extension* extension_;

  
  
  const Extension* triggering_extension_;

  
  gfx::ImageSkia icon_;

 private:
  
  
  void SetIcon(const gfx::Image& image);

  void OnImageLoaded(const std::string& extension_id, const gfx::Image& image);

  
  
  virtual void Show() = 0;

  base::MessageLoop* ui_loop_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionUninstallDialog);
};

}  

#endif  
