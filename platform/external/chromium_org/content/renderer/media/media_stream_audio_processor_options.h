// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_PROCESSOR_OPTIONS_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_PROCESSOR_OPTIONS_H_

#include <string>

#include "base/files/file.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebMediaConstraints.h"
#include "third_party/libjingle/source/talk/app/webrtc/mediastreaminterface.h"

namespace webrtc {

class AudioFrame;
class AudioProcessing;
class MediaConstraintsInterface;
class TypingDetection;

}

namespace content {

class RTCMediaConstraints;

using webrtc::AudioProcessing;
using webrtc::MediaConstraintsInterface;

class CONTENT_EXPORT MediaAudioConstraints {
 public:
  
  static const char kEchoCancellation[];
  static const char kGoogEchoCancellation[];
  static const char kGoogExperimentalEchoCancellation[];
  static const char kGoogAutoGainControl[];
  static const char kGoogExperimentalAutoGainControl[];
  static const char kGoogNoiseSuppression[];
  static const char kGoogExperimentalNoiseSuppression[];
  static const char kGoogHighpassFilter[];
  static const char kGoogTypingNoiseDetection[];
  static const char kGoogAudioMirroring[];

  
  
  
  
  static void ApplyFixedAudioConstraints(RTCMediaConstraints* constraints);

  
  
  
  
  MediaAudioConstraints(const blink::WebMediaConstraints& constraints,
                        int effects);
  virtual ~MediaAudioConstraints();

  
  
  bool NeedsAudioProcessing();

  
  
  
  
  
  bool GetProperty(const std::string& key);

  
  
  
  bool GetEchoCancellationProperty();

  
  
  bool IsValid();

 private:
  
  bool GetDefaultValueForConstraint(
      const blink::WebMediaConstraints& constraints, const std::string& key);

  const blink::WebMediaConstraints constraints_;
  const int effects_;
  bool default_audio_processing_constraint_value_;
};

void EnableEchoCancellation(AudioProcessing* audio_processing);

void EnableNoiseSuppression(AudioProcessing* audio_processing);

void EnableHighPassFilter(AudioProcessing* audio_processing);

void EnableTypingDetection(AudioProcessing* audio_processing,
                           webrtc::TypingDetection* typing_detector);

void StartEchoCancellationDump(AudioProcessing* audio_processing,
                               base::File aec_dump_file);

void StopEchoCancellationDump(AudioProcessing* audio_processing);

void EnableAutomaticGainControl(AudioProcessing* audio_processing);

void GetAecStats(AudioProcessing* audio_processing,
                 webrtc::AudioProcessorInterface::AudioProcessorStats* stats);

}  

#endif  
