// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_LOCAL_AUDIO_TRACK_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_LOCAL_AUDIO_TRACK_H_

#include <list>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "content/renderer/media/media_stream_track.h"
#include "content/renderer/media/tagged_list.h"
#include "content/renderer/media/webrtc_audio_device_impl.h"

namespace content {

class MediaStreamAudioLevelCalculator;
class MediaStreamAudioProcessor;
class MediaStreamAudioSink;
class MediaStreamAudioSinkOwner;
class MediaStreamAudioTrackSink;
class PeerConnectionAudioSink;
class WebAudioCapturerSource;
class WebRtcAudioCapturer;
class WebRtcLocalAudioTrackAdapter;

class CONTENT_EXPORT WebRtcLocalAudioTrack
    : NON_EXPORTED_BASE(public MediaStreamTrack) {
 public:
  WebRtcLocalAudioTrack(WebRtcLocalAudioTrackAdapter* adapter,
                        const scoped_refptr<WebRtcAudioCapturer>& capturer,
                        WebAudioCapturerSource* webaudio_source);

  virtual ~WebRtcLocalAudioTrack();

  
  
  
  void AddSink(MediaStreamAudioSink* sink);

  
  
  void RemoveSink(MediaStreamAudioSink* sink);

  
  
  
  void AddSink(PeerConnectionAudioSink* sink);
  void RemoveSink(PeerConnectionAudioSink* sink);

  
  
  void Start();

  
  
  virtual void Stop() OVERRIDE;

  
  
  void Capture(const int16* audio_data,
               base::TimeDelta delay,
               int volume,
               bool key_pressed,
               bool need_audio_processing,
               bool force_report_nonzero_energy);

  
  
  
  void OnSetFormat(const media::AudioParameters& params);

  
  
  
  void SetAudioProcessor(
      const scoped_refptr<MediaStreamAudioProcessor>& processor);

 private:
  typedef TaggedList<MediaStreamAudioTrackSink> SinkList;

  
  
  WebRtcLocalAudioTrackAdapter* adapter_;

  
  scoped_refptr<WebRtcAudioCapturer> capturer_;

  
  
  scoped_refptr<WebAudioCapturerSource> webaudio_source_;

  
  
  
  SinkList sinks_;

  
  base::ThreadChecker main_render_thread_checker_;

  
  base::ThreadChecker capture_thread_checker_;

  
  mutable base::Lock lock_;

  
  
  media::AudioParameters audio_parameters_;

  
  
  scoped_ptr<MediaStreamAudioLevelCalculator> level_calculator_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcLocalAudioTrack);
};

}  

#endif  
