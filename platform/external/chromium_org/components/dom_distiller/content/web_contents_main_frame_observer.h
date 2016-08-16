// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CONTENT_WEB_CONTENTS_MAIN_FRAME_OBSERVER_H_
#define COMPONENTS_DOM_DISTILLER_CONTENT_WEB_CONTENTS_MAIN_FRAME_OBSERVER_H_

#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace dom_distiller {

class WebContentsMainFrameObserver
    : public content::WebContentsObserver,
      public content::WebContentsUserData<WebContentsMainFrameObserver> {
 public:
  virtual ~WebContentsMainFrameObserver();

  bool is_document_loaded_in_main_frame() {
    return is_document_loaded_in_main_frame_;
  }

  bool is_initialized() { return is_initialized_; }

  
  virtual void DocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;

 private:
  explicit WebContentsMainFrameObserver(content::WebContents* web_contents);
  friend class content::WebContentsUserData<WebContentsMainFrameObserver>;

  
  void CleanUp();

  
  
  
  bool is_document_loaded_in_main_frame_;

  
  
  bool is_initialized_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsMainFrameObserver);
};

}  

#endif  
