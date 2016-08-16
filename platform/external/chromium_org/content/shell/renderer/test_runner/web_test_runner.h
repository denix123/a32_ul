// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_WEBTESTRUNNER_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_WEBTESTRUNNER_H_

#include <vector>

namespace blink {
class WebPermissionClient;
}

namespace content {

class WebTestRunner {
 public:
  
  
  virtual blink::WebPermissionClient* GetWebPermissions() const = 0;

  
  
  

  
  
  virtual bool ShouldDumpAsAudio() const = 0;
  virtual void GetAudioData(std::vector<unsigned char>* buffer_view) const = 0;

  
  
  virtual bool ShouldDumpBackForwardList() const = 0;

  
  
  virtual bool ShouldGeneratePixelResults() = 0;
};

}  

#endif  
