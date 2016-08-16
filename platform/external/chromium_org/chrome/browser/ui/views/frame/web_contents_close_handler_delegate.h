// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_WEB_CONTENTS_CLOSE_HANDLER_DELEGATE_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_WEB_CONTENTS_CLOSE_HANDLER_DELEGATE_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace ui {
class LayerTreeOwner;
}

class WebContentsCloseHandlerDelegate {
 public:
  
  
  
  
  virtual void CloneWebContentsLayer() = 0;

  
  
  virtual void DestroyClonedLayer() = 0;

 protected:
  virtual ~WebContentsCloseHandlerDelegate() {}
};

#endif  
