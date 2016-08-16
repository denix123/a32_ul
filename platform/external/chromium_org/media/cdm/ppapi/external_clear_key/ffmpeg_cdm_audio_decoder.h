// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PPAPI_EXTERNAL_CLEAR_KEY_FFMPEG_CDM_AUDIO_DECODER_H_
#define MEDIA_CDM_PPAPI_EXTERNAL_CLEAR_KEY_FFMPEG_CDM_AUDIO_DECODER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/cdm/ppapi/external_clear_key/clear_key_cdm_common.h"
#include "media/ffmpeg/ffmpeg_deleters.h"

struct AVCodecContext;
struct AVFrame;

namespace media {
class AudioBus;
class AudioTimestampHelper;
}

namespace media {
class FFmpegCdmAudioDecoder {
 public:
  explicit FFmpegCdmAudioDecoder(ClearKeyCdmHost* host);
  ~FFmpegCdmAudioDecoder();
  bool Initialize(const cdm::AudioDecoderConfig& config);
  void Deinitialize();
  void Reset();

  
  static bool IsValidConfig(const cdm::AudioDecoderConfig& config);

  
  
  
  
  
  
  
  cdm::Status DecodeBuffer(const uint8_t* compressed_buffer,
                           int32_t compressed_buffer_size,
                           int64_t timestamp,
                           cdm::AudioFrames* decoded_frames);

 private:
  void ResetTimestampState();
  void ReleaseFFmpegResources();

  base::TimeDelta GetNextOutputTimestamp() const;

  void SerializeInt64(int64_t value);

  bool is_initialized_;

  ClearKeyCdmHost* const host_;

  
  scoped_ptr<AVCodecContext, ScopedPtrAVFreeContext> codec_context_;
  scoped_ptr<AVFrame, ScopedPtrAVFreeFrame> av_frame_;

  
  int samples_per_second_;
  int channels_;

  
  int av_sample_format_;

  
  scoped_ptr<AudioTimestampHelper> output_timestamp_helper_;
  int bytes_per_frame_;
  base::TimeDelta last_input_timestamp_;

  
  
  
  int output_bytes_to_drop_;

  typedef std::vector<uint8_t> SerializedAudioFrames;
  SerializedAudioFrames serialized_audio_frames_;

  DISALLOW_COPY_AND_ASSIGN(FFmpegCdmAudioDecoder);
};

}  

#endif  
