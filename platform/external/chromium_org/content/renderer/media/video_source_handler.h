// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_VIDEO_SOURCE_HANDLER_H_
#define CONTENT_RENDERER_MEDIA_VIDEO_SOURCE_HANDLER_H_

#include <map>
#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "media/base/video_frame.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"

namespace content {

class MediaStreamRegistryInterface;
class MediaStreamVideoSink;
class PpFrameReceiver;

class CONTENT_EXPORT FrameReaderInterface {
 public:
  
  virtual bool GotFrame(const scoped_refptr<media::VideoFrame>& frame) = 0;

 protected:
  virtual ~FrameReaderInterface() {}
};

class CONTENT_EXPORT VideoSourceHandler {
 public:
  
  
  explicit VideoSourceHandler(MediaStreamRegistryInterface* registry);
  virtual ~VideoSourceHandler();
  
  
  
  bool Open(const std::string& url, FrameReaderInterface* reader);
  
  
  
  bool Close(FrameReaderInterface* reader);

 private:
  FRIEND_TEST_ALL_PREFIXES(VideoSourceHandlerTest, OpenClose);

  struct SourceInfo {
    SourceInfo(const blink::WebMediaStreamTrack& blink_track,
               FrameReaderInterface* reader);
    ~SourceInfo();

    scoped_ptr<PpFrameReceiver> receiver_;
  };

  typedef std::map<FrameReaderInterface*, SourceInfo*> SourceInfoMap;

  
  
  void DeliverFrameForTesting(FrameReaderInterface* reader,
                              const scoped_refptr<media::VideoFrame>& frame);

  blink::WebMediaStreamTrack GetFirstVideoTrack(const std::string& url);

  MediaStreamRegistryInterface* registry_;
  SourceInfoMap reader_to_receiver_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(VideoSourceHandler);
};

}  

#endif  
