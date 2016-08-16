// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_BROWSER_PLUGIN_DELEGATE_H_
#define CONTENT_PUBLIC_RENDERER_BROWSER_PLUGIN_DELEGATE_H_

#include <string>

#include "content/common/content_export.h"

namespace content {

class RenderFrame;

class CONTENT_EXPORT BrowserPluginDelegate {
 public:
  BrowserPluginDelegate(RenderFrame* render_frame,
                        const std::string& mime_type) {}
  virtual ~BrowserPluginDelegate() {}

  
  virtual void DidFinishLoading() {}

  
  virtual void DidReceiveData(const char* data, int data_length) {}

  
  
  virtual void SetElementInstanceID(int element_instance_id) {}
};

}  

#endif  
