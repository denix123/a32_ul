// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_AUDIO_MUTER_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_AUDIO_MUTER_H_

#include "base/memory/ref_counted.h"

namespace content {

class WebContents;

class WebContentsAudioMuter {
 public:
  explicit WebContentsAudioMuter(WebContents* web_contents);
  ~WebContentsAudioMuter();

  bool is_muting() const { return is_muting_; }

  void StartMuting();
  void StopMuting();

 private:
  
  
  
  class MuteDestination;
  const scoped_refptr<MuteDestination> destination_;

  bool is_muting_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsAudioMuter);
};

}  

#endif  
