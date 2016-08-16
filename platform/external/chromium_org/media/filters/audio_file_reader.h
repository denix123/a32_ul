// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_AUDIO_FILE_READER_H_
#define MEDIA_FILTERS_AUDIO_FILE_READER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/media_export.h"
#include "media/filters/ffmpeg_glue.h"

struct AVCodecContext;
struct AVPacket;
struct AVStream;

namespace base { class TimeDelta; }

namespace media {

class AudioBus;
class FFmpegURLProtocol;

class MEDIA_EXPORT AudioFileReader {
 public:
  
  
  
  explicit AudioFileReader(FFmpegURLProtocol* protocol);
  virtual ~AudioFileReader();

  
  
  
  bool Open();
  void Close();

  
  
  
  
  
  
  
  int Read(AudioBus* audio_bus);

  
  int channels() const { return channels_; }
  int sample_rate() const { return sample_rate_; }

  
  
  
  
  
  base::TimeDelta GetDuration() const;
  int GetNumberOfFrames() const;

  
  
  

  
  bool OpenDemuxerForTesting();

  
  
  bool ReadPacketForTesting(AVPacket* output_packet);

  
  
  bool SeekForTesting(base::TimeDelta seek_time);

  const AVStream* GetAVStreamForTesting() const;
  const AVCodecContext* codec_context_for_testing() const {
    return codec_context_;
  }

 private:
  bool OpenDemuxer();
  bool OpenDecoder();
  bool ReadPacket(AVPacket* output_packet);

  scoped_ptr<FFmpegGlue> glue_;
  AVCodecContext* codec_context_;
  int stream_index_;
  FFmpegURLProtocol* protocol_;
  int channels_;
  int sample_rate_;
  int64_t end_padding_;

  
  int av_sample_format_;

  DISALLOW_COPY_AND_ASSIGN(AudioFileReader);
};

}  

#endif  
