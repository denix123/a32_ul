// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_LEAK_DETECTOR_H_
#define CONTENT_SHELL_RENDERER_LEAK_DETECTOR_H_

#include "base/basictypes.h"
#include "content/shell/common/leak_detection_result.h"
#include "third_party/WebKit/public/web/WebLeakDetector.h"

namespace blink {
class WebLocalFrame;
}  

namespace content {

class WebKitTestRunner;

class LeakDetector : public blink::WebLeakDetectorClient {
 public:
  explicit LeakDetector(WebKitTestRunner* test_runner);
  virtual ~LeakDetector();

  
  
  
  
  
  void TryLeakDetection(blink::WebLocalFrame* frame);

  
  virtual void onLeakDetectionComplete(const Result& result) OVERRIDE;

 private:
  WebKitTestRunner* test_runner_;
  scoped_ptr<blink::WebLeakDetector> web_leak_detector_;
  blink::WebLeakDetectorClient::Result previous_result_;

  DISALLOW_COPY_AND_ASSIGN(LeakDetector);
};

}  

#endif  
