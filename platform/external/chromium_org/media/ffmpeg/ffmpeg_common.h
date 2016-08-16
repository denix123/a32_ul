// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FFMPEG_FFMPEG_COMMON_H_
#define MEDIA_FFMPEG_FFMPEG_COMMON_H_

#include <cerrno>

#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/channel_layout.h"
#include "media/base/media_export.h"
#include "media/base/video_decoder_config.h"
#include "media/base/video_frame.h"
#include "media/ffmpeg/ffmpeg_deleters.h"

extern "C" {
#define FF_API_PIX_FMT_DESC 0
#define FF_API_OLD_DECODE_AUDIO 0
#define FF_API_DESTRUCT_PACKET 0
#define FF_API_GET_BUFFER 0

MSVC_PUSH_DISABLE_WARNING(4244);
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/log.h>
#include <libavutil/mathematics.h>
#include <libavutil/opt.h>
MSVC_POP_WARNING();
}  

namespace media {

class AudioDecoderConfig;
class VideoDecoderConfig;


inline void ScopedPtrAVFree::operator()(void* x) const {
  av_free(x);
}

inline void ScopedPtrAVFreePacket::operator()(void* x) const {
  AVPacket* packet = static_cast<AVPacket*>(x);
  av_free_packet(packet);
  delete packet;
}

inline void ScopedPtrAVFreeContext::operator()(void* x) const {
  AVCodecContext* codec_context = static_cast<AVCodecContext*>(x);
  avcodec_free_context(&codec_context);
}

inline void ScopedPtrAVFreeFrame::operator()(void* x) const {
  AVFrame* frame = static_cast<AVFrame*>(x);
  av_frame_free(&frame);
}

MEDIA_EXPORT base::TimeDelta ConvertFromTimeBase(const AVRational& time_base,
                                                 int64 timestamp);

MEDIA_EXPORT int64 ConvertToTimeBase(const AVRational& time_base,
                                     const base::TimeDelta& timestamp);

void AVStreamToAudioDecoderConfig(
    const AVStream* stream,
    AudioDecoderConfig* config,
    bool record_stats);
void AudioDecoderConfigToAVCodecContext(
    const AudioDecoderConfig& config,
    AVCodecContext* codec_context);

void AVStreamToVideoDecoderConfig(
    const AVStream* stream,
    VideoDecoderConfig* config,
    bool record_stats);
void VideoDecoderConfigToAVCodecContext(
    const VideoDecoderConfig& config,
    AVCodecContext* codec_context);

MEDIA_EXPORT void AVCodecContextToAudioDecoderConfig(
    const AVCodecContext* codec_context,
    bool is_encrypted,
    AudioDecoderConfig* config,
    bool record_stats);

MEDIA_EXPORT ChannelLayout ChannelLayoutToChromeChannelLayout(int64_t layout,
                                                              int channels);

MEDIA_EXPORT SampleFormat
    AVSampleFormatToSampleFormat(AVSampleFormat sample_format);

MEDIA_EXPORT VideoFrame::Format PixelFormatToVideoFormat(
    PixelFormat pixel_format);

PixelFormat VideoFormatToPixelFormat(VideoFrame::Format video_format);

MEDIA_EXPORT bool FFmpegUTCDateToTime(const char* date_utc, base::Time* out);

}  

#endif  
