// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_SOURCE_PLAYER_H_
#define MEDIA_BASE_ANDROID_MEDIA_SOURCE_PLAYER_H_

#include <jni.h>
#include <map>
#include <string>
#include <vector>

#include "base/android/scoped_java_ref.h"
#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "base/time/default_tick_clock.h"
#include "base/time/time.h"
#include "media/base/android/demuxer_android.h"
#include "media/base/android/media_codec_bridge.h"
#include "media/base/android/media_decoder_job.h"
#include "media/base/android/media_drm_bridge.h"
#include "media/base/android/media_player_android.h"
#include "media/base/media_export.h"
#include "media/base/time_delta_interpolator.h"

namespace media {

class AudioDecoderJob;
class VideoDecoderJob;

class MEDIA_EXPORT MediaSourcePlayer : public MediaPlayerAndroid,
                                       public DemuxerAndroidClient {
 public:
  
  
  MediaSourcePlayer(int player_id,
                    MediaPlayerManager* manager,
                    const RequestMediaResourcesCB& request_media_resources_cb,
                    scoped_ptr<DemuxerAndroid> demuxer,
                    const GURL& frame_url);
  virtual ~MediaSourcePlayer();

  
  virtual void SetVideoSurface(gfx::ScopedJavaSurface surface) OVERRIDE;
  virtual void Start() OVERRIDE;
  virtual void Pause(bool is_media_related_action ALLOW_UNUSED) OVERRIDE;
  virtual void SeekTo(base::TimeDelta timestamp) OVERRIDE;
  virtual void Release() OVERRIDE;
  virtual void SetVolume(double volume) OVERRIDE;
  virtual int GetVideoWidth() OVERRIDE;
  virtual int GetVideoHeight() OVERRIDE;
  virtual base::TimeDelta GetCurrentTime() OVERRIDE;
  virtual base::TimeDelta GetDuration() OVERRIDE;
  virtual bool IsPlaying() OVERRIDE;
  virtual bool CanPause() OVERRIDE;
  virtual bool CanSeekForward() OVERRIDE;
  virtual bool CanSeekBackward() OVERRIDE;
  virtual bool IsPlayerReady() OVERRIDE;
  virtual void SetCdm(BrowserCdm* cdm) OVERRIDE;

  
  virtual void OnDemuxerConfigsAvailable(const DemuxerConfigs& params) OVERRIDE;
  virtual void OnDemuxerDataAvailable(const DemuxerData& params) OVERRIDE;
  virtual void OnDemuxerSeekDone(
      base::TimeDelta actual_browser_seek_time) OVERRIDE;
  virtual void OnDemuxerDurationChanged(base::TimeDelta duration) OVERRIDE;

 private:
  friend class MediaSourcePlayerTest;

  
  void UpdateTimestamps(base::TimeDelta current_presentation_timestamp,
                        base::TimeDelta max_presentation_timestamp);

  
  void StartInternal();

  
  void PlaybackCompleted(bool is_audio);

  
  void MediaDecoderCallback(
        bool is_audio, MediaCodecStatus status,
        base::TimeDelta current_presentation_timestamp,
        base::TimeDelta max_presentation_timestamp);

  bool IsPrerollFinished(bool is_audio) const;

  
  base::android::ScopedJavaLocalRef<jobject> GetMediaCrypto();

  
  void OnMediaCryptoReady();

  
  void ProcessPendingEvents();

  
  void ClearDecodingData();

  
  void DecodeMoreAudio();
  void DecodeMoreVideo();

  
  bool HasVideo() const;
  bool HasAudio() const;

  
  
  bool AudioFinished();
  bool VideoFinished();

  
  bool Seekable();

  
  void OnDecoderStarved();

  
  
  
  
  
  
  void StartStarvationCallback(
      base::TimeDelta current_presentation_timestamp,
      base::TimeDelta max_presentation_timestamp);

  
  
  
  
  void ScheduleSeekEventAndStopDecoding(base::TimeDelta seek_time);

  
  
  
  
  
  
  void BrowserSeekToCurrentTime();

  
  
  bool IsProtectedSurfaceRequired();

  
  
  
  
  void OnPrefetchDone();

  
  void OnDemuxerConfigsChanged();

  
  void OnKeyAdded();

  
  void OnCdmUnset();

  
  
  
  
  void set_decode_callback_for_testing(const base::Closure& test_decode_cb) {
    decode_callback_for_testing_ = test_decode_cb;
  }

  
  enum PendingEventFlags {
    NO_EVENT_PENDING = 0,
    PREFETCH_DONE_EVENT_PENDING = 1 << 0,
    SEEK_EVENT_PENDING = 1 << 1,
    DECODER_CREATION_EVENT_PENDING = 1 << 2,
    PREFETCH_REQUEST_EVENT_PENDING = 1 << 3,
  };

  static const char* GetEventName(PendingEventFlags event);
  bool IsEventPending(PendingEventFlags event) const;
  void SetPendingEvent(PendingEventFlags event);
  void ClearPendingEvent(PendingEventFlags event);

  
  
  void RetryDecoderCreation(bool audio, bool video);

  scoped_ptr<DemuxerAndroid> demuxer_;

  
  unsigned pending_event_;

  
  base::TimeDelta duration_;
  bool playing_;

  
  base::DefaultTickClock default_tick_clock_;

  
  
  TimeDeltaInterpolator interpolator_;

  
  
  
  
  
  
  base::TimeTicks start_time_ticks_;
  base::TimeDelta start_presentation_timestamp_;

  
  
  
  
  bool doing_browser_seek_;

  
  
  
  
  bool pending_seek_;
  base::TimeDelta pending_seek_time_;

  
  scoped_ptr<AudioDecoderJob, MediaDecoderJob::Deleter> audio_decoder_job_;
  scoped_ptr<VideoDecoderJob, MediaDecoderJob::Deleter> video_decoder_job_;

  
  
  base::TimeDelta preroll_timestamp_;

  
  
  
  base::CancelableClosure decoder_starvation_callback_;

  MediaDrmBridge* drm_bridge_;
  int cdm_registration_id_;

  
  
  
  bool is_waiting_for_key_;

  
  
  
  bool is_waiting_for_audio_decoder_;
  bool is_waiting_for_video_decoder_;

  
  base::Closure decode_callback_for_testing_;

  
  bool prerolling_;

  
  
  base::WeakPtrFactory<MediaSourcePlayer> weak_factory_;
  base::WeakPtr<MediaSourcePlayer> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(MediaSourcePlayer);
};

}  

#endif  
