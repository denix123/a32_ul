// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_AUDIO_STREAM_MONITOR_H_
#define CONTENT_BROWSER_MEDIA_AUDIO_STREAM_MONITOR_H_

#include <map>
#include <utility>

#include "base/callback_forward.h"
#include "base/threading/thread_checker.h"
#include "base/time/default_tick_clock.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "build/build_config.h"
#include "content/common/content_export.h"
#include "media/audio/audio_output_controller.h"

namespace base {
class TickClock;
}

namespace content {
class WebContents;

class CONTENT_EXPORT AudioStreamMonitor {
 public:
  explicit AudioStreamMonitor(WebContents* contents);
  ~AudioStreamMonitor();

  
  
  static bool monitoring_available() {
    return media::AudioOutputController::will_monitor_audio_levels();
  }

  
  
  
  
  bool WasRecentlyAudible() const;

  
  
  
  
  
  
  typedef base::Callback<std::pair<float, bool>()> ReadPowerAndClipCallback;
  static void StartMonitoringStream(
      int render_process_id,
      int render_frame_id,
      int stream_id,
      const ReadPowerAndClipCallback& read_power_callback);
  static void StopMonitoringStream(int render_process_id,
                                   int render_frame_id,
                                   int stream_id);

  void set_was_recently_audible_for_testing(bool value) {
    was_recently_audible_ = value;
  }

 private:
  friend class AudioStreamMonitorTest;

  enum {
    
    
    kPowerMeasurementsPerSecond = 15,

    
    kHoldOnMilliseconds = 2000
  };

  
  
  static void StartMonitoringHelper(
      int render_process_id,
      int render_frame_id,
      int stream_id,
      const ReadPowerAndClipCallback& read_power_callback);
  static void StopMonitoringHelper(int render_process_id,
                                   int render_frame_id,
                                   int stream_id);

  
  void StartMonitoringStreamOnUIThread(
      int render_process_id,
      int stream_id,
      const ReadPowerAndClipCallback& callback);

  
  
  void StopMonitoringStreamOnUIThread(int render_process_id, int stream_id);

  
  
  void Poll();

  
  
  
  void MaybeToggle();

  
  
  
  WebContents* const web_contents_;

  
  
  base::DefaultTickClock default_tick_clock_;
  base::TickClock* const clock_;

  
  base::ThreadChecker thread_checker_;

  
  
  typedef std::pair<int, int> StreamID;
  typedef std::map<StreamID, ReadPowerAndClipCallback> StreamPollCallbackMap;
  StreamPollCallbackMap poll_callbacks_;

  
  base::TimeTicks last_blurt_time_;

  
  
  bool was_recently_audible_;

  
  base::RepeatingTimer<AudioStreamMonitor> poll_timer_;

  
  
  base::OneShotTimer<AudioStreamMonitor> off_timer_;

  DISALLOW_COPY_AND_ASSIGN(AudioStreamMonitor);
};

}  

#endif  
