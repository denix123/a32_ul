// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_MEDIA_WEB_CONTENTS_OBSERVER_H_
#define CONTENT_BROWSER_MEDIA_MEDIA_WEB_CONTENTS_OBSERVER_H_

#include "base/compiler_specific.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "content/common/content_export.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {

class BrowserCdmManager;
class BrowserMediaPlayerManager;
class RenderViewHost;

class CONTENT_EXPORT MediaWebContentsObserver : public WebContentsObserver {
 public:
  explicit MediaWebContentsObserver(RenderViewHost* render_view_host);
  virtual ~MediaWebContentsObserver();

  
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) OVERRIDE;

#if defined(OS_ANDROID)
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 RenderFrameHost* render_frame_host) OVERRIDE;

  
  
  bool OnMediaPlayerMessageReceived(const IPC::Message& message,
                                    RenderFrameHost* render_frame_host);
  bool OnMediaPlayerSetCdmMessageReceived(const IPC::Message& message,
                                          RenderFrameHost* render_frame_host);

  
  
  BrowserMediaPlayerManager* GetMediaPlayerManager(
      RenderFrameHost* render_frame_host);

  void OnSetCdm(RenderFrameHost* render_frame_host, int player_id, int cdm_id);

#if defined(VIDEO_HOLE)
  void OnFrameInfoUpdated();
#endif  

 private:
  
  typedef base::ScopedPtrHashMap<uintptr_t, BrowserMediaPlayerManager>
      MediaPlayerManagerMap;
  MediaPlayerManagerMap media_player_managers_;
#endif  

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaWebContentsObserver);
};

}  

#endif  
