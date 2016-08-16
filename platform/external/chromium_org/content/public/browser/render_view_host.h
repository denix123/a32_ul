// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_RENDER_VIEW_HOST_H_
#define CONTENT_PUBLIC_BROWSER_RENDER_VIEW_HOST_H_

#include <list>

#include "base/callback_forward.h"
#include "content/common/content_export.h"
#include "content/public/browser/render_widget_host.h"
#include "content/public/common/file_chooser_params.h"
#include "content/public/common/page_zoom.h"
#include "mojo/public/cpp/system/core.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"

class GURL;

namespace base {
class FilePath;
class Value;
}

namespace blink {
struct WebMediaPlayerAction;
struct WebPluginAction;
}

namespace gfx {
class Point;
}

namespace media {
class AudioOutputController;
}

namespace ui {
struct SelectedFileInfo;
}

namespace content {

class ChildProcessSecurityPolicy;
class RenderFrameHost;
class RenderViewHostDelegate;
class SessionStorageNamespace;
class SiteInstance;
struct DropData;
struct WebPreferences;

class CONTENT_EXPORT RenderViewHost : virtual public RenderWidgetHost {
 public:
  
  
  static RenderViewHost* FromID(int render_process_id, int render_view_id);

  
  
  static RenderViewHost* From(RenderWidgetHost* rwh);

  virtual ~RenderViewHost() {}

  
  virtual RenderFrameHost* GetMainFrame() = 0;

  
  
  virtual void AllowBindings(int binding_flags) = 0;

  
  virtual void ClearFocusedElement() = 0;

  
  virtual bool IsFocusedElementEditable() = 0;

  
  
  
  virtual void ClosePage() = 0;

  
  
  virtual void CopyImageAt(int x, int y) = 0;

  
  
  virtual void SaveImageAt(int x, int y) = 0;

  
  virtual void DirectoryEnumerationFinished(
      int request_id,
      const std::vector<base::FilePath>& files) = 0;

  
  
  virtual void DisableScrollbarsForThreshold(const gfx::Size& size) = 0;

  
  
  virtual void DragSourceEndedAt(
      int client_x, int client_y, int screen_x, int screen_y,
      blink::WebDragOperation operation) = 0;

  
  
  virtual void DragSourceSystemDragEnded() = 0;

  
  virtual void DragTargetDragEnter(
      const DropData& drop_data,
      const gfx::Point& client_pt,
      const gfx::Point& screen_pt,
      blink::WebDragOperationsMask operations_allowed,
      int key_modifiers) = 0;
  virtual void DragTargetDragOver(
      const gfx::Point& client_pt,
      const gfx::Point& screen_pt,
      blink::WebDragOperationsMask operations_allowed,
      int key_modifiers) = 0;
  virtual void DragTargetDragLeave() = 0;
  virtual void DragTargetDrop(const gfx::Point& client_pt,
                              const gfx::Point& screen_pt,
                              int key_modifiers) = 0;

  
  
  virtual void EnableAutoResize(const gfx::Size& min_size,
                                const gfx::Size& max_size) = 0;

  
  virtual void DisableAutoResize(const gfx::Size& new_size) = 0;

  
  virtual void EnablePreferredSizeMode() = 0;

  
  
  virtual void ExecuteMediaPlayerActionAtLocation(
      const gfx::Point& location,
      const blink::WebMediaPlayerAction& action) = 0;

  
  
  virtual void ExecutePluginActionAtLocation(
      const gfx::Point& location, const blink::WebPluginAction& action) = 0;

  
  virtual void ExitFullscreen() = 0;

  
  
  
  virtual void FilesSelectedInChooser(
      const std::vector<ui::SelectedFileInfo>& files,
      FileChooserParams::Mode permissions) = 0;

  virtual RenderViewHostDelegate* GetDelegate() const = 0;

  
  
  virtual int GetEnabledBindings() const = 0;

  virtual SiteInstance* GetSiteInstance() const = 0;

  
  
  virtual bool IsRenderViewLive() const = 0;

  
  
  virtual void NotifyMoveOrResizeStarted() = 0;

  
  
  virtual void SetWebUIProperty(const std::string& name,
                                const std::string& value) = 0;

  
  virtual void Zoom(PageZoom zoom) = 0;

  
  
  virtual void SyncRendererPrefs() = 0;

  
  
  virtual WebPreferences GetWebkitPreferences() = 0;

  
  
  virtual void OnWebkitPreferencesChanged() = 0;

  
  virtual void UpdateWebkitPreferences(const WebPreferences& prefs) = 0;

  
  
  
  typedef std::list<scoped_refptr<media::AudioOutputController> >
      AudioOutputControllerList;
  typedef base::Callback<void(const AudioOutputControllerList&)>
      GetAudioOutputControllersCallback;
  virtual void GetAudioOutputControllers(
      const GetAudioOutputControllersCallback& callback) const = 0;

  
  virtual void SelectWordAroundCaret() = 0;

#if defined(OS_ANDROID)
  
  
  virtual void ActivateNearestFindResult(int request_id, float x, float y) = 0;

  
  virtual void RequestFindMatchRects(int current_version) = 0;
#endif

 private:
  
  friend class RenderViewHostImpl;
  RenderViewHost() {}
};

}  

#endif  
