// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CAST_ENVIRONMENT_H_
#define MEDIA_CAST_CAST_ENVIRONMENT_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/single_thread_task_runner.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/logging_impl.h"

namespace media {
namespace cast {

class CastEnvironment : public base::RefCountedThreadSafe<CastEnvironment> {
 public:
  
  enum ThreadId {
    
    
    MAIN,
    
    
    AUDIO,
    
    VIDEO,
  };

  CastEnvironment(
      scoped_ptr<base::TickClock> clock,
      scoped_refptr<base::SingleThreadTaskRunner> main_thread_proxy,
      scoped_refptr<base::SingleThreadTaskRunner> audio_thread_proxy,
      scoped_refptr<base::SingleThreadTaskRunner> video_thread_proxy);

  
  
  
  
  
  bool PostTask(ThreadId identifier,
                const tracked_objects::Location& from_here,
                const base::Closure& task);

  bool PostDelayedTask(ThreadId identifier,
                       const tracked_objects::Location& from_here,
                       const base::Closure& task,
                       base::TimeDelta delay);

  bool CurrentlyOn(ThreadId identifier);

  
  base::TickClock* Clock() const { return clock_.get(); }

  
  
  
  LoggingImpl* Logging() const { return logging_.get(); }

  scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner(
      ThreadId identifier) const;

  bool HasAudioThread() { return audio_thread_proxy_.get() ? true : false; }

  bool HasVideoThread() { return video_thread_proxy_.get() ? true : false; }

 protected:
  virtual ~CastEnvironment();

  
  scoped_refptr<base::SingleThreadTaskRunner> main_thread_proxy_;
  scoped_refptr<base::SingleThreadTaskRunner> audio_thread_proxy_;
  scoped_refptr<base::SingleThreadTaskRunner> video_thread_proxy_;
  scoped_ptr<base::TickClock> clock_;
  scoped_ptr<LoggingImpl> logging_;

 private:
  friend class base::RefCountedThreadSafe<CastEnvironment>;

  DISALLOW_COPY_AND_ASSIGN(CastEnvironment);
};

}  
}  

#endif  
