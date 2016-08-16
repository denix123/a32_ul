// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_DOM_AUTOMATION_CONTROLLER_H_
#define CONTENT_RENDERER_DOM_AUTOMATION_CONTROLLER_H_

#include "base/basictypes.h"
#include "content/public/renderer/render_frame_observer.h"
#include "gin/wrappable.h"


namespace blink {
class WebFrame;
}

namespace gin {
class Arguments;
}

namespace content {

class RenderFrame;

class DomAutomationController : public gin::Wrappable<DomAutomationController>,
                                public RenderFrameObserver {
 public:
  static gin::WrapperInfo kWrapperInfo;

  static void Install(RenderFrame* render_frame, blink::WebFrame* frame);

  
  
  
  
  bool SendMsg(const gin::Arguments& args);

  
  
  bool SendJSON(const std::string& json);

  
  bool SendWithId(int automation_id, const std::string& str);

  bool SetAutomationId(int automation_id);

 private:
  explicit DomAutomationController(RenderFrame* render_view);
  virtual ~DomAutomationController();

  
  virtual gin::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate) OVERRIDE;

  
  virtual void OnDestruct() OVERRIDE;

  int automation_id_;  

  DISALLOW_COPY_AND_ASSIGN(DomAutomationController);
};

}  

#endif  
