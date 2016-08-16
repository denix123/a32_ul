// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_BUFFERING_CONTROLLER_H
#define CHROMECAST_MEDIA_CMA_BASE_BUFFERING_CONTROLLER_H

#include <list>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"

namespace chromecast {
namespace media {
class BufferingConfig;
class BufferingState;

class BufferingController {
 public:
  typedef base::Callback<void(bool)> BufferingNotificationCB;

  
  
  
  
  
  
  BufferingController(
      const scoped_refptr<BufferingConfig>& config,
      const BufferingNotificationCB& buffering_notification_cb);
  ~BufferingController();

  
  
  scoped_refptr<BufferingState> AddStream();

  
  void SetMediaTime(base::TimeDelta time);

  
  
  base::TimeDelta GetMaxRenderingTime() const;

  
  bool IsBuffering() const { return is_buffering_; }

  
  
  void Reset();

 private:
  
  
  
  
  
  void OnBufferingStateChanged(bool force_notification,
                               bool buffering_timeout);

  
  
  
  
  
  
  
  void UpdateHighLevelThreshold(base::TimeDelta high_level_threshold);

  
  
  bool IsHighBufferLevel();
  bool IsLowBufferLevel();

  
  void DumpState() const;

  base::ThreadChecker thread_checker_;

  
  scoped_refptr<BufferingConfig> config_;

  
  BufferingNotificationCB buffering_notification_cb_;

  
  bool is_buffering_;

  
  base::Time begin_buffering_time_;

  
  typedef std::list<scoped_refptr<BufferingState> > StreamList;
  StreamList stream_list_;

  base::WeakPtrFactory<BufferingController> weak_factory_;
  base::WeakPtr<BufferingController> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(BufferingController);
};

}  
}  

#endif  
