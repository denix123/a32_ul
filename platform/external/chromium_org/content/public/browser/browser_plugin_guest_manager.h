// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_BROWSER_PLUGIN_GUEST_MANAGER_H_
#define CONTENT_PUBLIC_BROWSER_BROWSER_PLUGIN_GUEST_MANAGER_H_

#include "base/callback.h"
#include "content/common/content_export.h"

namespace content {

class WebContents;

class CONTENT_EXPORT BrowserPluginGuestManager {
 public:
  virtual ~BrowserPluginGuestManager() {}

  
  
  
  virtual WebContents* GetGuestByInstanceID(WebContents* embedder_web_contents,
                                            int browser_plugin_instance_id);

  
  
  
  typedef base::Callback<bool(WebContents*)> GuestCallback;
  virtual bool ForEachGuest(WebContents* embedder_web_contents,
                            const GuestCallback& callback);
};

}  

#endif  
