// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_DEBUG_TRACE_EVENT_SYNTHETIC_DELAY_H_
#define BASE_DEBUG_TRACE_EVENT_SYNTHETIC_DELAY_H_

#include "base/atomicops.h"
#include "base/debug/trace_event.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"

#define TRACE_EVENT_SYNTHETIC_DELAY(name)                                     \
  static base::subtle::AtomicWord INTERNAL_TRACE_EVENT_UID(impl_ptr) = 0;     \
  trace_event_internal::ScopedSyntheticDelay INTERNAL_TRACE_EVENT_UID(delay)( \
      name, &INTERNAL_TRACE_EVENT_UID(impl_ptr));

#define TRACE_EVENT_SYNTHETIC_DELAY_BEGIN(name)                          \
  do {                                                                   \
    static base::subtle::AtomicWord impl_ptr = 0;                        \
    trace_event_internal::GetOrCreateDelay(name, &impl_ptr)->Begin();    \
  } while (false)

#define TRACE_EVENT_SYNTHETIC_DELAY_END(name)                         \
  do {                                                                \
    static base::subtle::AtomicWord impl_ptr = 0;                     \
    trace_event_internal::GetOrCreateDelay(name, &impl_ptr)->End();   \
  } while (false)

template <typename Type>
struct DefaultSingletonTraits;

namespace base {
namespace debug {

class TRACE_EVENT_API_CLASS_EXPORT TraceEventSyntheticDelayClock {
 public:
  TraceEventSyntheticDelayClock();
  virtual ~TraceEventSyntheticDelayClock();
  virtual base::TimeTicks Now() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(TraceEventSyntheticDelayClock);
};

class TRACE_EVENT_API_CLASS_EXPORT TraceEventSyntheticDelay {
 public:
  enum Mode {
    STATIC,      
    ONE_SHOT,    
    ALTERNATING  
  };

  
  static TraceEventSyntheticDelay* Lookup(const std::string& name);

  void SetTargetDuration(TimeDelta target_duration);
  void SetMode(Mode mode);
  void SetClock(TraceEventSyntheticDelayClock* clock);

  
  
  
  void Begin();

  
  
  void End();

  
  
  
  
  void BeginParallel(base::TimeTicks* out_end_time);

  
  
  void EndParallel(base::TimeTicks end_time);

 private:
  TraceEventSyntheticDelay();
  ~TraceEventSyntheticDelay();
  friend class TraceEventSyntheticDelayRegistry;

  void Initialize(const std::string& name,
                  TraceEventSyntheticDelayClock* clock);
  base::TimeTicks CalculateEndTimeLocked(base::TimeTicks start_time);
  void ApplyDelay(base::TimeTicks end_time);

  Lock lock_;
  Mode mode_;
  std::string name_;
  int begin_count_;
  int trigger_count_;
  base::TimeTicks end_time_;
  base::TimeDelta target_duration_;
  TraceEventSyntheticDelayClock* clock_;

  DISALLOW_COPY_AND_ASSIGN(TraceEventSyntheticDelay);
};

TRACE_EVENT_API_CLASS_EXPORT void ResetTraceEventSyntheticDelays();

}  
}  

namespace trace_event_internal {

class TRACE_EVENT_API_CLASS_EXPORT ScopedSyntheticDelay {
 public:
  explicit ScopedSyntheticDelay(const char* name,
                                base::subtle::AtomicWord* impl_ptr);
  ~ScopedSyntheticDelay();

 private:
  base::debug::TraceEventSyntheticDelay* delay_impl_;
  base::TimeTicks end_time_;

  DISALLOW_COPY_AND_ASSIGN(ScopedSyntheticDelay);
};

TRACE_EVENT_API_CLASS_EXPORT base::debug::TraceEventSyntheticDelay*
    GetOrCreateDelay(const char* name, base::subtle::AtomicWord* impl_ptr);

}  

#endif 
