// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_BUFFERING_STATE_H_
#define CHROMECAST_MEDIA_CMA_BASE_BUFFERING_STATE_H_

#include <string>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace chromecast {
namespace media {

class BufferingConfig : public base::RefCountedThreadSafe<BufferingConfig> {
 public:
  BufferingConfig(base::TimeDelta low_level_threshold,
                  base::TimeDelta high_level_threshold);

  base::TimeDelta low_level() const { return low_level_threshold_; }
  base::TimeDelta high_level() const { return high_level_threshold_; }

  void set_low_level(base::TimeDelta low_level) {
    low_level_threshold_ = low_level;
  }
  void set_high_level(base::TimeDelta high_level) {
    high_level_threshold_ = high_level;
  }

 private:
  friend class base::RefCountedThreadSafe<BufferingConfig>;
  virtual ~BufferingConfig();

  base::TimeDelta low_level_threshold_;
  base::TimeDelta high_level_threshold_;

  DISALLOW_COPY_AND_ASSIGN(BufferingConfig);
};

class BufferingState
    : public base::RefCountedThreadSafe<BufferingState> {
 public:
  typedef base::Callback<void(base::TimeDelta)> HighLevelBufferCB;

  enum State {
    kLowLevel,
    kMediumLevel,
    kHighLevel,
    kEosReached,
  };

  
  
  
  
  
  BufferingState(const scoped_refptr<BufferingConfig>& config,
                 const base::Closure& state_changed_cb,
                 const HighLevelBufferCB& high_level_buffer_cb);

  
  State GetState() const { return state_; }

  
  
  
  void OnConfigChanged();

  
  void SetMediaTime(base::TimeDelta media_time);

  
  
  void SetMaxRenderingTime(base::TimeDelta max_rendering_time);
  base::TimeDelta GetMaxRenderingTime() const;

  
  void SetBufferedTime(base::TimeDelta buffered_time);

  
  
  void NotifyEos();

  
  
  
  
  
  
  void NotifyMaxCapacity(base::TimeDelta buffered_time);

  
  std::string ToString() const;

 private:
  friend class base::RefCountedThreadSafe<BufferingState>;
  virtual ~BufferingState();

  
  State GetBufferLevelState() const;

  
  void UpdateState(State new_state);

  scoped_refptr<BufferingConfig> const config_;

  
  base::Closure state_changed_cb_;

  
  HighLevelBufferCB high_level_buffer_cb_;

  
  State state_;

  
  
  base::TimeDelta media_time_;

  
  
  
  base::TimeDelta max_rendering_time_;

  
  
  base::TimeDelta buffered_time_;

  DISALLOW_COPY_AND_ASSIGN(BufferingState);
};

}  
}  

#endif  
