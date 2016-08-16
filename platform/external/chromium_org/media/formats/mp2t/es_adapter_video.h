// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_ADAPTER_VIDEO_H_
#define MEDIA_FORMATS_MP2T_ES_ADAPTER_VIDEO_H_

#include <deque>
#include <list>
#include <utility>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/stream_parser_buffer.h"

namespace media {

class VideoDecoderConfig;

namespace mp2t {

class MEDIA_EXPORT EsAdapterVideo {
 public:
  typedef base::Callback<void(const VideoDecoderConfig&)> NewVideoConfigCB;
  typedef base::Callback<void(scoped_refptr<StreamParserBuffer>)> EmitBufferCB;

  EsAdapterVideo(
      const NewVideoConfigCB& new_video_config_cb,
      const EmitBufferCB& emit_buffer_cb);
  ~EsAdapterVideo();

  
  void Flush();

  
  void Reset();

  
  void OnConfigChanged(const VideoDecoderConfig& video_decoder_config);

  
  void OnNewBuffer(
      const scoped_refptr<StreamParserBuffer>& stream_parser_buffer);

 private:
  typedef std::deque<scoped_refptr<StreamParserBuffer> > BufferQueue;
  typedef std::pair<int64, VideoDecoderConfig> ConfigEntry;

  void ProcessPendingBuffers(bool flush);

  
  
  base::TimeDelta GetNextFramePts(base::TimeDelta current_pts);

  
  
  void ReplaceDiscardedFrames(
      const scoped_refptr<StreamParserBuffer>& stream_parser_buffer);

  NewVideoConfigCB new_video_config_cb_;
  EmitBufferCB emit_buffer_cb_;

  bool has_valid_config_;
  bool has_valid_frame_;

  
  base::TimeDelta last_frame_duration_;

  
  std::list<ConfigEntry> config_list_;

  
  int64 buffer_index_;

  
  BufferQueue buffer_list_;
  std::list<base::TimeDelta> emitted_pts_;

  
  
  base::TimeDelta discarded_frames_min_pts_;
  std::list<DecodeTimestamp> discarded_frames_dts_;

  DISALLOW_COPY_AND_ASSIGN(EsAdapterVideo);
};

}  
}  

#endif  
