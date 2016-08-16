// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_WEB_UI_MOJO_H_
#define CONTENT_RENDERER_WEB_UI_MOJO_H_

#include <string>

#include "content/public/renderer/render_frame_observer.h"
#include "content/public/renderer/render_view_observer.h"
#include "content/public/renderer/render_view_observer_tracker.h"
#include "mojo/public/cpp/system/core.h"

namespace gin {
class PerContextData;
}

namespace content {

class WebUIMojoContextState;

class WebUIMojo
    : public RenderViewObserver,
      public RenderViewObserverTracker<WebUIMojo> {
 public:
  explicit WebUIMojo(RenderView* render_view);

 private:
  class MainFrameObserver : public RenderFrameObserver {
   public:
    explicit MainFrameObserver(WebUIMojo* web_ui_mojo);
    virtual ~MainFrameObserver();

    
    virtual void WillReleaseScriptContext(v8::Handle<v8::Context> context,
                                          int world_id) OVERRIDE;
    virtual void DidFinishDocumentLoad() OVERRIDE;

   private:
    WebUIMojo* web_ui_mojo_;

    DISALLOW_COPY_AND_ASSIGN(MainFrameObserver);
  };

  virtual ~WebUIMojo();

  void CreateContextState();
  void DestroyContextState(v8::Handle<v8::Context> context);

  
  
  void OnDidFinishDocumentLoad();

  WebUIMojoContextState* GetContextState();

  
  virtual void DidCreateDocumentElement(blink::WebLocalFrame* frame) OVERRIDE;
  virtual void DidClearWindowObject(blink::WebLocalFrame* frame) OVERRIDE;

  MainFrameObserver main_frame_observer_;

  DISALLOW_COPY_AND_ASSIGN(WebUIMojo);
};

}  

#endif  
