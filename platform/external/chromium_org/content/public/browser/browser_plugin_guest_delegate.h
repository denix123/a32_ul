// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_BROWSER_PLUGIN_GUEST_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_BROWSER_PLUGIN_GUEST_DELEGATE_H_

#include "base/callback_forward.h"
#include "base/process/kill.h"
#include "content/common/content_export.h"
#include "content/public/browser/web_contents.h"

namespace base {
class DictionaryValue;
}  

namespace gfx {
class Size;
}  

namespace content {

class CONTENT_EXPORT BrowserPluginGuestDelegate {
 public:
  virtual ~BrowserPluginGuestDelegate() {}

  
  
  
  virtual void WillAttach(content::WebContents* embedder_web_contents,
                          int element_instance_id) {}

  virtual WebContents* CreateNewGuestWindow(
      const WebContents::CreateParams& create_params);

  
  
  
  virtual void DidAttach(int guest_proxy_routing_id) {}

  
  virtual void ElementSizeChanged(const gfx::Size& old_size,
                                  const gfx::Size& new_size) {}

  
  
  
  virtual void GuestSizeChanged(const gfx::Size& old_size,
                                const gfx::Size& new_size) {}

  
  
  virtual void RequestPointerLockPermission(
      bool user_gesture,
      bool last_unlocked_by_target,
      const base::Callback<void(bool)>& callback) {}

  
  
  virtual void Destroy() {}

  
  
  typedef base::Callback<void()> DestructionCallback;
  virtual void RegisterDestructionCallback(
      const DestructionCallback& callback) {}
};

}  

#endif  
