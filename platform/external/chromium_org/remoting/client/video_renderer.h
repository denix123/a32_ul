// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CLIENT_VIDEO_RENDERER_H_
#define REMOTING_CLIENT_VIDEO_RENDERER_H_

#include "remoting/protocol/video_stub.h"

namespace remoting {

class ChromotingStats;

namespace protocol {
class SessionConfig;
}  

class VideoRenderer : public protocol::VideoStub {
 public:
  
  virtual void Initialize(const protocol::SessionConfig& config) = 0;

  
  virtual ChromotingStats* GetStats() = 0;
};

}  

#endif  
