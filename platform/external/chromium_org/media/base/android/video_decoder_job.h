// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_VIDEO_DECODER_JOB_H_
#define MEDIA_BASE_ANDROID_VIDEO_DECODER_JOB_H_

#include <jni.h>

#include "media/base/android/media_decoder_job.h"

namespace media {

class VideoCodecBridge;

class VideoDecoderJob : public MediaDecoderJob {
 public:
  
  
  
  
  
  VideoDecoderJob(
      const base::Closure& request_data_cb,
      const base::Closure& request_resources_cb,
      const base::Closure& on_demuxer_config_changed_cb);
  virtual ~VideoDecoderJob();

  
  
  bool SetVideoSurface(gfx::ScopedJavaSurface surface);

  
  virtual bool HasStream() const OVERRIDE;
  virtual void Flush() OVERRIDE;
  virtual void ReleaseDecoderResources() OVERRIDE;
  virtual void SetDemuxerConfigs(const DemuxerConfigs& configs) OVERRIDE;

  bool next_video_data_is_iframe() {
    return next_video_data_is_iframe_;
  }

  int output_width() const { return output_width_; }
  int output_height() const { return output_height_; }

 private:
  
  virtual void ReleaseOutputBuffer(
      int output_buffer_index,
      size_t size,
      bool render_output,
      base::TimeDelta current_presentation_timestamp,
      const ReleaseOutputCompletionCallback& callback) OVERRIDE;
  virtual bool ComputeTimeToRender() const OVERRIDE;
  virtual bool IsCodecReconfigureNeeded(
      const DemuxerConfigs& configs) const OVERRIDE;
  virtual bool AreDemuxerConfigsChanged(
      const DemuxerConfigs& configs) const OVERRIDE;
  virtual bool CreateMediaCodecBridgeInternal() OVERRIDE;
  virtual void CurrentDataConsumed(bool is_config_change) OVERRIDE;
  virtual bool UpdateOutputFormat() OVERRIDE;

  
  bool IsProtectedSurfaceRequired();

  
  VideoCodec video_codec_;
  int config_width_;
  int config_height_;

  
  int output_width_;
  int output_height_;

  
  gfx::ScopedJavaSurface surface_;

  
  base::Closure request_resources_cb_;
  base::Closure release_resources_cb_;

  
  
  
  bool next_video_data_is_iframe_;

  DISALLOW_COPY_AND_ASSIGN(VideoDecoderJob);
};

}  

#endif  
