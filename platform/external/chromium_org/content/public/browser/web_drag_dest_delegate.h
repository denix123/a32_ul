// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_WEB_DRAG_DEST_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_WEB_DRAG_DEST_DELEGATE_H_

#include "base/strings/string16.h"

class GURL;

namespace ui {
class OSExchangeData;
}

namespace content {
class WebContents;
struct DropData;

class WebDragDestDelegate {
 public:
  
  
  
  virtual void DragInitialize(WebContents* contents) = 0;

  
  virtual void OnDragOver() = 0;
  virtual void OnDragEnter() = 0;
  virtual void OnDrop() = 0;
  
  virtual void OnDragLeave() = 0;

#if defined(USE_AURA)
  
  
  virtual void OnReceiveDragData(const ui::OSExchangeData& data) = 0;
#endif  

  virtual ~WebDragDestDelegate() {}
};

}  

#endif  
