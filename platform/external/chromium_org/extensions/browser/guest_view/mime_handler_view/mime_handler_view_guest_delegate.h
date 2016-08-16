// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_MIME_HANDLER_VIEW_MIME_HANDLER_VIEW_GUEST_DELEGATE_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_MIME_HANDLER_VIEW_MIME_HANDLER_VIEW_GUEST_DELEGATE_H_

#include "base/macros.h"

namespace content {
class WebContents;
}  

namespace extensions {

class MimeHandlerViewGuest;

class MimeHandlerViewGuestDelegate {
 public:
  explicit MimeHandlerViewGuestDelegate(MimeHandlerViewGuest* guest) {}
  virtual ~MimeHandlerViewGuestDelegate() {}

  
  virtual void AttachHelpers() {}

  
  
  virtual void ChangeZoom(bool zoom_in) {}

 private:
  DISALLOW_COPY_AND_ASSIGN(MimeHandlerViewGuestDelegate);
};

}  

#endif  
