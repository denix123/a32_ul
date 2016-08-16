// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_EXTENSION_OPTIONS_EXTENSION_OPTIONS_GUEST_DELEGATE_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_EXTENSION_OPTIONS_EXTENSION_OPTIONS_GUEST_DELEGATE_H_

#include "base/macros.h"

namespace content {
struct ContextMenuParams;
struct OpenURLParams;
class WebContents;
}

namespace extensions {

class ExtensionOptionsGuest;

class ExtensionOptionsGuestDelegate {
 public:
  explicit ExtensionOptionsGuestDelegate(ExtensionOptionsGuest* guest);
  virtual ~ExtensionOptionsGuestDelegate();

  
  virtual void DidInitialize() = 0;

  
  
  virtual bool HandleContextMenu(const content::ContextMenuParams& params) = 0;

  virtual content::WebContents* OpenURLInNewTab(
      const content::OpenURLParams& params) = 0;

  ExtensionOptionsGuest* extension_options_guest() const { return guest_; }

 private:
  ExtensionOptionsGuest* const guest_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionOptionsGuestDelegate);
};

}  

#endif  
