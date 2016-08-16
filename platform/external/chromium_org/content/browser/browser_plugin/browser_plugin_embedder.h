// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_EMBEDDER_H_
#define CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_EMBEDDER_H_

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"

struct BrowserPluginHostMsg_Attach_Params;
struct BrowserPluginHostMsg_ResizeGuest_Params;

namespace gfx {
class Point;
}

namespace content {

class BrowserPluginGuest;
class BrowserPluginGuestManager;
class RenderWidgetHostImpl;
class WebContentsImpl;
struct NativeWebKeyboardEvent;

class CONTENT_EXPORT BrowserPluginEmbedder : public WebContentsObserver {
 public:
  virtual ~BrowserPluginEmbedder();

  static BrowserPluginEmbedder* Create(WebContentsImpl* web_contents);

  
  WebContentsImpl* GetWebContents() const;

  
  void DidSendScreenRects();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  void DragSourceEndedAt(int client_x, int client_y, int screen_x,
      int screen_y, blink::WebDragOperation operation);

  void OnUpdateDragCursor(bool* handled);

  void DragEnteredGuest(BrowserPluginGuest* guest);

  void DragLeftGuest(BrowserPluginGuest* guest);

  void StartDrag(BrowserPluginGuest* guest);

  
  
  void SystemDragEnded();

  
  bool HandleKeyboardEvent(const NativeWebKeyboardEvent& event);

 private:
  explicit BrowserPluginEmbedder(WebContentsImpl* web_contents);

  BrowserPluginGuestManager* GetBrowserPluginGuestManager() const;

  void ClearGuestDragStateIfApplicable();

  bool DidSendScreenRectsCallback(WebContents* guest_web_contents);

  bool SetZoomLevelCallback(double level, WebContents* guest_web_contents);

  bool UnlockMouseIfNecessaryCallback(bool* mouse_unlocked, WebContents* guest);

  
  void OnAttach(int instance_id,
                const BrowserPluginHostMsg_Attach_Params& params);
  void OnPluginAtPositionResponse(int instance_id,
                                  int request_id,
                                  const gfx::Point& position);

  
  
  
  
  
  base::WeakPtr<BrowserPluginGuest> guest_dragging_over_;

  
  
  base::WeakPtr<BrowserPluginGuest> guest_started_drag_;

  
  bool guest_drag_ending_;

  base::WeakPtrFactory<BrowserPluginEmbedder> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPluginEmbedder);
};

}  

#endif  
