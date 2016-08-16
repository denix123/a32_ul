// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_AUDIO_DECODER_JOB_H_
#define MEDIA_BASE_ANDROID_AUDIO_DECODER_JOB_H_

#include <jni.h>
#include <vector>

#include "base/callback.h"
#include "media/base/android/media_decoder_job.h"

namespace media {

class AudioCodecBridge;
class AudioTimestampHelper;

class AudioDecoderJob : public MediaDecoderJob {
 public:
  
  
  
  
  AudioDecoderJob(const base::Closure& request_data_cb,
                  const base::Closure& on_demuxer_config_changed_cb);
  virtual ~AudioDecoderJob();

  
  virtual bool HasStream() const OVERRIDE;
  virtual void SetDemuxerConfigs(const DemuxerConfigs& configs) OVERRIDE;

  
  void SetVolume(double volume);

  
  void SetBaseTimestamp(base::TimeDelta base_timestamp);

 private:
  
  virtual void ReleaseOutputBuffer(
      int output_buffer_index,
      size_t size,
      bool render_output,
      base::TimeDelta current_presentation_timestamp,
      const ReleaseOutputCompletionCallback& callback) OVERRIDE;
  virtual bool ComputeTimeToRender() const OVERRIDE;
  virtual bool AreDemuxerConfigsChanged(
      const DemuxerConfigs& configs) const OVERRIDE;
  virtual bool CreateMediaCodecBridgeInternal() OVERRIDE;

  
  void SetVolumeInternal();

  
  AudioCodec audio_codec_;
  int num_channels_;
  int sampling_rate_;
  std::vector<uint8> audio_extra_data_;
  double volume_;
  int bytes_per_frame_;

  
  base::TimeDelta base_timestamp_;

  
  scoped_ptr<AudioTimestampHelper> audio_timestamp_helper_;

  DISALLOW_COPY_AND_ASSIGN(AudioDecoderJob);
};

}  

#endif  
