// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_SOURCE_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_SOURCE_H_

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "content/common/content_export.h"
#include "content/common/media/media_stream_options.h"
#include "third_party/WebKit/public/platform/WebMediaStreamSource.h"

namespace blink {
class WebMediaStreamTrack;
}  

namespace content {

class CONTENT_EXPORT MediaStreamSource
    : NON_EXPORTED_BASE(public blink::WebMediaStreamSource::ExtraData) {
 public:
  typedef base::Callback<void(const blink::WebMediaStreamSource& source)>
      SourceStoppedCallback;

  typedef base::Callback<void(MediaStreamSource* source,
                              MediaStreamRequestResult result,
                              const blink::WebString& result_name)>
      ConstraintsCallback;

  
  
  static const char kSourceId[];

  MediaStreamSource();
  virtual ~MediaStreamSource();

  
  
  const StreamDeviceInfo& device_info() const {
    return device_info_;
  }

  
  
  
  void StopSource();

  void ResetSourceStoppedCallback() {
    DCHECK(!stop_callback_.is_null());
    stop_callback_.Reset();
  }

 protected:
  
  
  virtual void DoStopSource() = 0;

  
  
  void SetDeviceInfo(const StreamDeviceInfo& device_info) {
    device_info_ = device_info;
  }

  
  void SetStopCallback(const SourceStoppedCallback& stop_callback) {
    DCHECK(stop_callback_.is_null());
    stop_callback_ = stop_callback;
  }

 private:
  StreamDeviceInfo device_info_;
  SourceStoppedCallback stop_callback_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamSource);
};

}  

#endif  
