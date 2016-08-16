// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MANIFEST_MANIFEST_MANAGER_H_
#define CONTENT_RENDERER_MANIFEST_MANIFEST_MANAGER_H_

#include <list>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/common/manifest.h"
#include "content/public/renderer/render_frame_observer.h"

class GURL;

namespace blink {
class WebURLResponse;
}

namespace content {

class ManifestFetcher;

class ManifestManager : public RenderFrameObserver {
 public:
  typedef base::Callback<void(const Manifest&)> GetManifestCallback;

  explicit ManifestManager(RenderFrame* render_frame);
  virtual ~ManifestManager();

  
  
  void GetManifest(const GetManifestCallback& callback);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidChangeManifest() OVERRIDE;

 private:
  enum ResolveState {
    ResolveStateSuccess,
    ResolveStateFailure
  };

  
  
  void OnRequestManifest(int request_id);
  void OnRequestManifestComplete(int request_id, const Manifest&);

  void FetchManifest();
  void OnManifestFetchComplete(const GURL& document_url,
                               const blink::WebURLResponse& response,
                               const std::string& data);
  void ResolveCallbacks(ResolveState state);

  scoped_ptr<ManifestFetcher> fetcher_;

  
  
  
  
  bool may_have_manifest_;

  
  bool manifest_dirty_;

  
  Manifest manifest_;

  std::list<GetManifestCallback> pending_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(ManifestManager);
};

} 

#endif 
