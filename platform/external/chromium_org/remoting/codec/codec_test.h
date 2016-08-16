// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CODEC_CODEC_TEST_H_
#define REMOTING_CODEC_CODEC_TEST_H_

#include <list>

#include "base/memory/ref_counted.h"

namespace webrtc {
class DesktopFrame;
class DesktopSize;
}

namespace remoting {

class VideoDecoder;
class VideoEncoder;

void TestVideoEncoder(VideoEncoder* encoder, bool strict);

void TestVideoEncoderDecoder(VideoEncoder* encoder,
                             VideoDecoder* decoder,
                             bool strict);

void TestVideoEncoderDecoderGradient(VideoEncoder* encoder,
                                     VideoDecoder* decoder,
                                     const webrtc::DesktopSize& screen_size,
                                     const webrtc::DesktopSize& view_size,
                                     double max_error_limit,
                                     double mean_error_limit);

float MeasureVideoEncoderFpsWithSize(VideoEncoder* encoder,
                                     const webrtc::DesktopSize& size);
float MeasureVideoEncoderFpsWithFrames(
    VideoEncoder* encoder,
    const std::list<webrtc::DesktopFrame*>& frames);

}  

#endif  