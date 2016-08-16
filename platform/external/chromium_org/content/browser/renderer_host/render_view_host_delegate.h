// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_DELEGATE_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_DELEGATE_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/process/kill.h"
#include "base/strings/string16.h"
#include "content/browser/dom_storage/session_storage_namespace_impl.h"
#include "content/common/content_export.h"
#include "net/base/load_states.h"
#include "third_party/WebKit/public/web/WebPopupType.h"
#include "ui/base/window_open_disposition.h"

class GURL;
class SkBitmap;
struct ViewHostMsg_CreateWindow_Params;
struct FrameHostMsg_DidCommitProvisionalLoad_Params;
struct ViewMsg_PostMessage_Params;

namespace base {
class ListValue;
class TimeTicks;
}

namespace IPC {
class Message;
}

namespace gfx {
class Point;
class Rect;
class Size;
}

namespace content {

class BrowserContext;
class CrossSiteTransferringRequest;
class FrameTree;
class PageState;
class RenderViewHost;
class RenderViewHostDelegateView;
class SessionStorageNamespace;
class SiteInstance;
class WebContents;
class WebContentsImpl;
struct FileChooserParams;
struct GlobalRequestID;
struct NativeWebKeyboardEvent;
struct Referrer;
struct RendererPreferences;
struct WebPreferences;

class CONTENT_EXPORT RenderViewHostDelegate {
 public:
  
  
  virtual RenderViewHostDelegateView* GetDelegateView();

  
  virtual bool OnMessageReceived(RenderViewHost* render_view_host,
                                 const IPC::Message& message);

  
  
  
  virtual WebContents* GetAsWebContents();

  
  
  virtual gfx::Rect GetRootWindowResizerRect() const = 0;

  
  
  
  virtual void RenderViewCreated(RenderViewHost* render_view_host) {}

  
  virtual void RenderViewReady(RenderViewHost* render_view_host) {}

  
  virtual void RenderViewTerminated(RenderViewHost* render_view_host,
                                    base::TerminationStatus status,
                                    int error_code) {}

  
  
  virtual void RenderViewDeleted(RenderViewHost* render_view_host) {}

  
  virtual void UpdateState(RenderViewHost* render_view_host,
                           int32 page_id,
                           const PageState& state) {}

  
  virtual void UpdateTargetURL(const GURL& url) {}

  
  virtual void Close(RenderViewHost* render_view_host) {}

  
  virtual void RequestMove(const gfx::Rect& new_bounds) {}

  
  virtual void DidCancelLoading() {}

  
  
  virtual void DocumentAvailableInMainFrame(RenderViewHost* render_view_host) {}

  
  virtual void RouteCloseEvent(RenderViewHost* rvh) {}

  
  virtual void RouteMessageEvent(
      RenderViewHost* rvh,
      const ViewMsg_PostMessage_Params& params) {}

  
  
  virtual RendererPreferences GetRendererPrefs(
      BrowserContext* browser_context) const = 0;

  
  
  virtual WebPreferences ComputeWebkitPrefs();

  
  
  
  virtual void OnUserGesture() {}

  
  
  
  
  virtual void OnIgnoredUIEvent() {}

  
  
  virtual void RendererUnresponsive(RenderViewHost* render_view_host,
                                    bool is_during_before_unload,
                                    bool is_during_unload) {}

  
  
  
  virtual void RendererResponsive(RenderViewHost* render_view_host) {}

  
  virtual void LoadStateChanged(const GURL& url,
                                const net::LoadStateWithParam& load_state,
                                uint64 upload_position,
                                uint64 upload_size) {}

  
  
  virtual void Activate() {}
  virtual void Deactivate() {}

  
  virtual void LostCapture() {}

  
  
  virtual void HandleMouseMove() {}
  virtual void HandleMouseDown() {}
  virtual void HandleMouseLeave() {}
  virtual void HandleMouseUp() {}
  virtual void HandlePointerActivate() {}
  virtual void HandleGestureBegin() {}
  virtual void HandleGestureEnd() {}

  
  virtual void RunFileChooser(
      RenderViewHost* render_view_host,
      const FileChooserParams& params) {}

  
  virtual void ToggleFullscreenMode(bool enter_fullscreen) {}
  virtual bool IsFullscreenForCurrentTab() const;

  
  virtual void UpdatePreferredSize(const gfx::Size& pref_size) {}

  
  virtual void ResizeDueToAutoResize(const gfx::Size& new_size) {}

  
  
  
  virtual void RequestToLockMouse(bool user_gesture,
                                  bool last_unlocked_by_target) {}

  
  virtual void LostMouseLock() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CreateNewWindow(
      int render_process_id,
      int route_id,
      int main_frame_route_id,
      const ViewHostMsg_CreateWindow_Params& params,
      SessionStorageNamespace* session_storage_namespace) {}

  
  
  
  
  
  
  virtual void CreateNewWidget(int render_process_id,
                               int route_id,
                               blink::WebPopupType popup_type) {}

  
  virtual void CreateNewFullscreenWidget(int render_process_id, int route_id) {}

  
  
  
  
  
  virtual void ShowCreatedWindow(int route_id,
                                 WindowOpenDisposition disposition,
                                 const gfx::Rect& initial_pos,
                                 bool user_gesture) {}

  
  
  virtual void ShowCreatedWidget(int route_id,
                                 const gfx::Rect& initial_pos) {}

  
  virtual void ShowCreatedFullscreenWidget(int route_id) {}

  
  
  virtual SessionStorageNamespace* GetSessionStorageNamespace(
      SiteInstance* instance);

  
  
  virtual SessionStorageNamespaceMap GetSessionStorageNamespaceMap();

  
  virtual bool IsNeverVisible();

  
  
  
  
  
  virtual FrameTree* GetFrameTree();

  
  
  
  
  virtual void SetIsVirtualKeyboardRequested(bool requested) {}
  virtual bool IsVirtualKeyboardRequested();

 protected:
  virtual ~RenderViewHostDelegate() {}
};

}  

#endif  
