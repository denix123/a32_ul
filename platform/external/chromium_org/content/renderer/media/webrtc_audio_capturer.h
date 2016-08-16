// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_CAPTURER_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_AUDIO_CAPTURER_H_

#include <list>
#include <string>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "content/common/media/media_stream_options.h"
#include "content/renderer/media/tagged_list.h"
#include "media/audio/audio_input_device.h"
#include "media/audio/audio_power_monitor.h"
#include "media/base/audio_capturer_source.h"
#include "third_party/WebKit/public/platform/WebMediaConstraints.h"

namespace media {
class AudioBus;
}

namespace content {

class MediaStreamAudioProcessor;
class MediaStreamAudioSource;
class WebRtcAudioDeviceImpl;
class WebRtcLocalAudioRenderer;
class WebRtcLocalAudioTrack;

class CONTENT_EXPORT WebRtcAudioCapturer
    : public base::RefCountedThreadSafe<WebRtcAudioCapturer>,
      NON_EXPORTED_BASE(public media::AudioCapturerSource::CaptureCallback) {
 public:
  
  
  
  
  
  
  
  
  
  
  static scoped_refptr<WebRtcAudioCapturer> CreateCapturer(
      int render_view_id,
      const StreamDeviceInfo& device_info,
      const blink::WebMediaConstraints& constraints,
      WebRtcAudioDeviceImpl* audio_device,
      MediaStreamAudioSource* audio_source);


  
  
  
  
  
  void AddTrack(WebRtcLocalAudioTrack* track);

  
  
  
  
  void RemoveTrack(WebRtcLocalAudioTrack* track);

  
  
  
  void EnablePeerConnectionMode();

  
  
  void SetVolume(int volume);
  int Volume() const;
  int MaxVolume() const;

  
  
  
  media::AudioParameters source_audio_parameters() const;

  
  
  bool GetPairedOutputParameters(int* session_id,
                                 int* output_sample_rate,
                                 int* output_frames_per_buffer) const;

  const std::string& device_id() const { return device_info_.device.id; }
  int session_id() const { return device_info_.session_id; }

  
  
  
  
  void Stop();

  
  
  
  void GetAudioProcessingParams(base::TimeDelta* delay, int* volume,
                                bool* key_pressed);

  
  void SetCapturerSourceForTesting(
      const scoped_refptr<media::AudioCapturerSource>& source,
      media::AudioParameters params);

 protected:
  friend class base::RefCountedThreadSafe<WebRtcAudioCapturer>;
  virtual ~WebRtcAudioCapturer();

 private:
  class TrackOwner;
  typedef TaggedList<TrackOwner> TrackList;

  WebRtcAudioCapturer(int render_view_id,
                      const StreamDeviceInfo& device_info,
                      const blink::WebMediaConstraints& constraints,
                      WebRtcAudioDeviceImpl* audio_device,
                      MediaStreamAudioSource* audio_source);

  
  
  virtual void Capture(const media::AudioBus* audio_source,
                       int audio_delay_milliseconds,
                       double volume,
                       bool key_pressed) OVERRIDE;
  virtual void OnCaptureError() OVERRIDE;

  
  
  bool Initialize();

  
  
  
  
  void SetCapturerSource(
      const scoped_refptr<media::AudioCapturerSource>& source,
      media::ChannelLayout channel_layout,
      float sample_rate);

  
  
  
  void Start();

  
  
  int GetBufferSize(int sample_rate) const;

  
  base::ThreadChecker thread_checker_;

  
  
  mutable base::Lock lock_;

  
  
  
  TrackList tracks_;

  
  scoped_refptr<media::AudioCapturerSource> source_;

  
  blink::WebMediaConstraints constraints_;

  
  
  scoped_refptr<MediaStreamAudioProcessor> audio_processor_;

  bool running_;

  int render_view_id_;

  
  const StreamDeviceInfo device_info_;

  
  
  int volume_;

  
  bool peer_connection_mode_;

  
  base::TimeDelta audio_delay_;
  bool key_pressed_;

  
  bool need_audio_processing_;

  
  
  WebRtcAudioDeviceImpl* audio_device_;

  
  
  
  
  
  
  
  MediaStreamAudioSource* const audio_source_;

    
  media::AudioPowerMonitor audio_power_monitor_;

  
  base::TimeTicks last_audio_level_log_time_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcAudioCapturer);
};

}  

#endif  
