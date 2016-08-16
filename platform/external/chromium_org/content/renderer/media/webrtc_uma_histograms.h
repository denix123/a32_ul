// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_UMA_HISTOGRAMS_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_UMA_HISTOGRAMS_H_

#include "base/memory/singleton.h"
#include "base/threading/non_thread_safe.h"
#include "content/common/content_export.h"
#include "content/public/common/media_stream_request.h"

namespace content {

enum MediaStreamRequestState {
  MEDIA_STREAM_REQUEST_EXPLICITLY_CANCELLED = 0,
  MEDIA_STREAM_REQUEST_NOT_GENERATED = 1,
  MEDIA_STREAM_REQUEST_PENDING_MEDIA_TRACKS = 2,
  NUM_MEDIA_STREAM_REQUEST_WITH_NO_RESULT
};

void LogUserMediaRequestWithNoResult(MediaStreamRequestState state);
void LogUserMediaRequestResult(MediaStreamRequestResult result);

enum JavaScriptAPIName {
  WEBKIT_GET_USER_MEDIA,
  WEBKIT_PEER_CONNECTION,
  WEBKIT_DEPRECATED_PEER_CONNECTION,
  WEBKIT_RTC_PEER_CONNECTION,
  WEBKIT_GET_MEDIA_DEVICES,
  INVALID_NAME
};

void UpdateWebRTCMethodCount(JavaScriptAPIName api_name);

class CONTENT_EXPORT PerSessionWebRTCAPIMetrics : public base::NonThreadSafe {
 public:
  virtual ~PerSessionWebRTCAPIMetrics();

  static PerSessionWebRTCAPIMetrics* GetInstance();

  
  
  void IncrementStreamCounter();
  void DecrementStreamCounter();

 protected:
  friend struct DefaultSingletonTraits<PerSessionWebRTCAPIMetrics>;
  friend void UpdateWebRTCMethodCount(JavaScriptAPIName);

  
  
  PerSessionWebRTCAPIMetrics();

  
  virtual void LogUsage(JavaScriptAPIName api_name);

  
  
  void LogUsageOnlyOnce(JavaScriptAPIName api_name);

 private:
  void ResetUsage();

  int num_streams_;
  bool has_used_api_[INVALID_NAME];

  DISALLOW_COPY_AND_ASSIGN(PerSessionWebRTCAPIMetrics);
};

} 

#endif  
