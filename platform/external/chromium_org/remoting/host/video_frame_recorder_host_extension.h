// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_VIDEO_FRAME_RECORDER_HOST_EXTENSION_H_
#define REMOTING_HOST_VIDEO_FRAME_RECORDER_HOST_EXTENSION_H_

#include "base/memory/scoped_ptr.h"
#include "remoting/host/host_extension.h"

namespace remoting {

class VideoFrameRecorderHostExtension : public HostExtension {
 public:
  VideoFrameRecorderHostExtension();
  virtual ~VideoFrameRecorderHostExtension();

  
  void SetMaxContentBytes(int64_t max_content_bytes);

  
  virtual std::string capability() const OVERRIDE;
  virtual scoped_ptr<HostExtensionSession> CreateExtensionSession(
      ClientSessionControl* client_session,
      protocol::ClientStub* client_stub) OVERRIDE;

 private:
  int64_t max_content_bytes_;

  DISALLOW_COPY_AND_ASSIGN(VideoFrameRecorderHostExtension);
};

}  

#endif  
