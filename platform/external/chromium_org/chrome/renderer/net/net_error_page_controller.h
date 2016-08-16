// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_NET_NET_ERROR_PAGE_CONTROLLER_H_
#define CHROME_RENDERER_NET_NET_ERROR_PAGE_CONTROLLER_H_

#include "base/macros.h"
#include "content/public/renderer/render_frame_observer.h"
#include "gin/arguments.h"
#include "gin/wrappable.h"


namespace content {
class RenderFrame;
}

class NetErrorPageController
    : public gin::Wrappable<NetErrorPageController>,
      public content::RenderFrameObserver {
 public:
  static gin::WrapperInfo kWrapperInfo;

  static void Install(content::RenderFrame* render_frame);

 private:
  explicit NetErrorPageController(content::RenderFrame* render_frame);
  virtual ~NetErrorPageController();

  
  bool LoadStaleButtonClick();

  
  bool ReloadButtonClick();

  
  bool DetailsButtonClick();

  
  
  bool TrackClick(const gin::Arguments& args);

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

  
  
  
  virtual void OnDestruct() OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(NetErrorPageController);
};

#endif  
