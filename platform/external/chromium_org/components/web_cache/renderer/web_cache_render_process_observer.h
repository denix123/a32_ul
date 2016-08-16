// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_WEB_CACHE_RENDERER_WEB_CACHE_RENDER_PROCESS_OBSERVER_H_
#define COMPONENTS_WEB_CACHE_RENDERER_WEB_CACHE_RENDER_PROCESS_OBSERVER_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "content/public/renderer/render_process_observer.h"

namespace web_cache {

class WebCacheRenderProcessObserver : public content::RenderProcessObserver {
 public:
  WebCacheRenderProcessObserver();
  virtual ~WebCacheRenderProcessObserver();

  
  
  void ExecutePendingClearCache();

 private:
  
  virtual bool OnControlMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void WebKitInitialized() OVERRIDE;
  virtual void OnRenderProcessShutdown() OVERRIDE;

  
  void OnSetCacheCapacities(size_t min_dead_capacity,
                            size_t max_dead_capacity,
                            size_t capacity);
  
  
  void OnClearCache(bool on_navigation);

  
  bool clear_cache_pending_;
  bool webkit_initialized_;
  size_t pending_cache_min_dead_capacity_;
  size_t pending_cache_max_dead_capacity_;
  size_t pending_cache_capacity_;

  DISALLOW_COPY_AND_ASSIGN(WebCacheRenderProcessObserver);
};

}  

#endif  

