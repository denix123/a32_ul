// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_RENDERER_NACL_HELPER_H_
#define COMPONENTS_NACL_RENDERER_NACL_HELPER_H_

#include "base/compiler_specific.h"
#include "content/public/renderer/render_frame_observer.h"

namespace nacl {

class NaClHelper : public content::RenderFrameObserver {
 public:
  explicit NaClHelper(content::RenderFrame* render_frame);
  virtual ~NaClHelper();

  
  virtual void DidCreatePepperPlugin(content::RendererPpapiHost* host) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NaClHelper);
};

}  

#endif  
