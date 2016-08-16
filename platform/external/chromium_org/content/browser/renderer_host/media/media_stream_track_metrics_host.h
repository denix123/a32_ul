// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_TRACK_METRICS_HOST_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_TRACK_METRICS_HOST_H_

#include <map>
#include <string>

#include "base/time/time.h"
#include "content/public/browser/browser_message_filter.h"

namespace content {

class MediaStreamTrackMetricsHost
    : public BrowserMessageFilter {
 public:
  explicit MediaStreamTrackMetricsHost();

 protected:
  virtual ~MediaStreamTrackMetricsHost();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 private:
  void OnAddTrack(uint64 id, bool is_audio, bool is_remote);
  void OnRemoveTrack(uint64 id);

  
  
  
  
  
  struct TrackInfo {
    bool is_audio;
    bool is_remote;
    base::TimeTicks timestamp;
  };

  void ReportDuration(const TrackInfo& info);

  
  typedef std::map<uint64, TrackInfo> TrackMap;
  TrackMap tracks_;
};

}  

#endif  
