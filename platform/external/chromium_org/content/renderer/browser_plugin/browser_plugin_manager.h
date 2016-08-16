// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_BROWSER_PLUGIN_BROWSER_PLUGIN_MANAGER_H_
#define CONTENT_RENDERER_BROWSER_PLUGIN_BROWSER_PLUGIN_MANAGER_H_

#include "base/id_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "content/public/renderer/render_view_observer.h"
#include "ipc/ipc_sender.h"

namespace base {
class DictionaryValue;
}

namespace blink {
class WebFrame;
class WebNode;
struct WebPluginParams;
}

namespace content {

class BrowserPlugin;
class BrowserPluginDelegate;
class BrowserPluginManagerFactory;
class RenderViewImpl;

class CONTENT_EXPORT BrowserPluginManager
    : public RenderViewObserver,
      public base::RefCounted<BrowserPluginManager> {
 public:
  
  static BrowserPluginManager* Create(RenderViewImpl* render_view);

  
  
  static void set_factory_for_testing(BrowserPluginManagerFactory* factory) {
    BrowserPluginManager::factory_ = factory;
  }

  explicit BrowserPluginManager(RenderViewImpl* render_view);

  
  
  
  
  virtual BrowserPlugin* CreateBrowserPlugin(
      RenderViewImpl* render_view,
      blink::WebFrame* frame,
      scoped_ptr<BrowserPluginDelegate> delegate) = 0;

  void Attach(int browser_plugin_instance_id);

  void AddBrowserPlugin(int browser_plugin_instance_id,
                        BrowserPlugin* browser_plugin);
  void RemoveBrowserPlugin(int browser_plugin_instance_id);
  BrowserPlugin* GetBrowserPlugin(int browser_plugin_instance_id) const;

  void UpdateDeviceScaleFactor();
  void UpdateFocusState();
  RenderViewImpl* render_view() const { return render_view_.get(); }
  int GetNextInstanceID();

  

  
  virtual bool Send(IPC::Message* msg) OVERRIDE = 0;

  
  
  
  
  virtual void OnDestruct() OVERRIDE {}

 protected:
  
  friend class base::RefCounted<BrowserPluginManager>;

  
  static BrowserPluginManagerFactory* factory_;

  virtual ~BrowserPluginManager();
  
  IDMap<BrowserPlugin> instances_;
  int current_instance_id_;
  base::WeakPtr<RenderViewImpl> render_view_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPluginManager);
};

}  

#endif 
