// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_WEBRTC_LOCAL_AUDIO_TRACK_ADAPTER_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_WEBRTC_LOCAL_AUDIO_TRACK_ADAPTER_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/synchronization/lock.h"
#include "content/common/content_export.h"
#include "third_party/libjingle/source/talk/app/webrtc/mediastreamtrack.h"
#include "third_party/libjingle/source/talk/media/base/audiorenderer.h"

namespace cricket {
class AudioRenderer;
}

namespace webrtc {
class AudioSourceInterface;
class AudioProcessorInterface;
}

namespace content {

class MediaStreamAudioProcessor;
class WebRtcAudioSinkAdapter;
class WebRtcLocalAudioTrack;

class CONTENT_EXPORT WebRtcLocalAudioTrackAdapter
    : NON_EXPORTED_BASE(public cricket::AudioRenderer),
      NON_EXPORTED_BASE(
          public webrtc::MediaStreamTrack<webrtc::AudioTrackInterface>) {
 public:
  static scoped_refptr<WebRtcLocalAudioTrackAdapter> Create(
      const std::string& label,
      webrtc::AudioSourceInterface* track_source);

  WebRtcLocalAudioTrackAdapter(
      const std::string& label,
      webrtc::AudioSourceInterface* track_source);

  virtual ~WebRtcLocalAudioTrackAdapter();

  void Initialize(WebRtcLocalAudioTrack* owner);

  std::vector<int> VoeChannels() const;

  
  
  void SetSignalLevel(int signal_level);

  
  
  
  
  void SetAudioProcessor(
      const scoped_refptr<MediaStreamAudioProcessor>& processor);

 private:
  
  virtual std::string kind() const OVERRIDE;

  
  virtual void AddSink(webrtc::AudioTrackSinkInterface* sink) OVERRIDE;
  virtual void RemoveSink(webrtc::AudioTrackSinkInterface* sink) OVERRIDE;
  virtual bool GetSignalLevel(int* level) OVERRIDE;
  virtual rtc::scoped_refptr<webrtc::AudioProcessorInterface>
      GetAudioProcessor() OVERRIDE;

  
  virtual void AddChannel(int channel_id) OVERRIDE;
  virtual void RemoveChannel(int channel_id) OVERRIDE;

  
  virtual webrtc::AudioSourceInterface* GetSource() const OVERRIDE;
  virtual cricket::AudioRenderer* GetRenderer() OVERRIDE;

  
  WebRtcLocalAudioTrack* owner_;

  
  
  rtc::scoped_refptr<webrtc::AudioSourceInterface> track_source_;

  
  
  scoped_refptr<MediaStreamAudioProcessor> audio_processor_;

  
  std::vector<int> voe_channels_;

  
  
  ScopedVector<WebRtcAudioSinkAdapter> sink_adapters_;

  
  int signal_level_;

  
  mutable base::Lock lock_;
};

}  

#endif  
