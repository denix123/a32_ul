// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_VIDEO_CAPTURE_ORACLE_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_VIDEO_CAPTURE_ORACLE_H_

#include <deque>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "ui/gfx/geometry/rect.h"

namespace content {

class CONTENT_EXPORT SmoothEventSampler {
 public:
  SmoothEventSampler(base::TimeDelta min_capture_period,
                     bool events_are_reliable,
                     int redundant_capture_goal);

  base::TimeDelta min_capture_period() const { return min_capture_period_; }

  
  
  
  void ConsiderPresentationEvent(base::TimeTicks event_time);

  
  bool ShouldSample() const;

  
  
  
  void RecordSample();

  
  
  bool IsOverdueForSamplingAt(base::TimeTicks event_time) const;

  
  
  bool HasUnrecordedEvent() const;

 private:
  const bool events_are_reliable_;
  const base::TimeDelta min_capture_period_;
  const int redundant_capture_goal_;
  const base::TimeDelta token_bucket_capacity_;

  base::TimeTicks current_event_;
  base::TimeTicks last_sample_;
  int overdue_sample_count_;
  base::TimeDelta token_bucket_;

  DISALLOW_COPY_AND_ASSIGN(SmoothEventSampler);
};

// In addition, AnimatedContentSampler will provide rewritten frame timestamps,
class CONTENT_EXPORT AnimatedContentSampler {
 public:
  explicit AnimatedContentSampler(base::TimeDelta min_capture_period);
  ~AnimatedContentSampler();

  
  
  
  
  void ConsiderPresentationEvent(const gfx::Rect& damage_rect,
                                 base::TimeTicks event_time);

  
  
  bool HasProposal() const;

  
  bool ShouldSample() const;

  
  
  base::TimeTicks frame_timestamp() const { return frame_timestamp_; }

  
  const gfx::Rect& detected_region() const { return detected_region_; }
  base::TimeDelta detected_period() const { return detected_period_; }

  
  
  
  void RecordSample(base::TimeTicks frame_timestamp);

 private:
  friend class AnimatedContentSamplerTest;

  
  struct Observation {
    gfx::Rect damage_rect;
    base::TimeTicks event_time;

    Observation(const gfx::Rect& d, base::TimeTicks e)
        : damage_rect(d), event_time(e) {}
  };
  typedef std::deque<Observation> ObservationFifo;

  
  void AddObservation(const gfx::Rect& damage_rect, base::TimeTicks event_time);

  
  
  
  
  gfx::Rect ElectMajorityDamageRect() const;

  
  
  
  
  bool AnalyzeObservations(base::TimeTicks event_time,
                           gfx::Rect* rect,
                           base::TimeDelta* period) const;

  
  
  void UpdateFrameTimestamp(base::TimeTicks event_time);

  
  const base::TimeDelta min_capture_period_;

  
  
  ObservationFifo observations_;

  
  
  gfx::Rect detected_region_;

  
  
  base::TimeDelta detected_period_;

  // The rewritten frame timestamp for the latest event.
  base::TimeTicks frame_timestamp_;

  
  
  base::TimeTicks recorded_frame_timestamp_;

  
  
  
  
  
  base::TimeDelta sequence_offset_;

  
  
  base::TimeDelta borrowed_time_;
};

class CONTENT_EXPORT VideoCaptureOracle {
 public:
  enum Event {
    kTimerPoll,
    kCompositorUpdate,
    kSoftwarePaint,
    kNumEvents,
  };

  VideoCaptureOracle(base::TimeDelta min_capture_period,
                     bool events_are_reliable);
  virtual ~VideoCaptureOracle();

  
  
  
  
  bool ObserveEventAndDecideCapture(Event event,
                                    const gfx::Rect& damage_rect,
                                    base::TimeTicks event_time);

  
  
  int RecordCapture();

  
  
  
  bool CompleteCapture(int frame_number, base::TimeTicks* frame_timestamp);

  base::TimeDelta min_capture_period() const {
    return smoothing_sampler_.min_capture_period();
  }

 private:
  
  base::TimeTicks GetFrameTimestamp(int frame_number) const;
  void SetFrameTimestamp(int frame_number, base::TimeTicks timestamp);

  
  int frame_number_;

  
  
  base::TimeTicks last_event_time_[kNumEvents];

  
  int last_delivered_frame_number_;

  
  
  
  
  SmoothEventSampler smoothing_sampler_;
  AnimatedContentSampler content_sampler_;

  
  
  
  enum { kMaxFrameTimestamps = 16 };
  base::TimeTicks frame_timestamps_[kMaxFrameTimestamps];
};

}  

#endif  
