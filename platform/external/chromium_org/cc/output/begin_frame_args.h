// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_OUTPUT_BEGIN_FRAME_ARGS_H_
#define CC_OUTPUT_BEGIN_FRAME_ARGS_H_

#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "base/values.h"
#include "cc/base/cc_export.h"

namespace base {
namespace debug {
class ConvertableToTraceFormat;
class TracedValue;
}
}

namespace cc {

struct CC_EXPORT BeginFrameArgs {
  
  BeginFrameArgs();

  
  
  static BeginFrameArgs Create(base::TimeTicks frame_time,
                               base::TimeTicks deadline,
                               base::TimeDelta interval);
  static BeginFrameArgs CreateForSynchronousCompositor(
      base::TimeTicks now = base::TimeTicks());

  
  
  static base::TimeDelta DefaultEstimatedParentDrawTime();

  
  
  static base::TimeDelta DefaultInterval();

  
  
  
  
  static base::TimeDelta DefaultRetroactiveBeginFramePeriod();

  bool IsValid() const { return interval >= base::TimeDelta(); }

  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  void AsValueInto(base::debug::TracedValue* dict) const;

  base::TimeTicks frame_time;
  base::TimeTicks deadline;
  base::TimeDelta interval;

 private:
  BeginFrameArgs(base::TimeTicks frame_time,
                 base::TimeTicks deadline,
                 base::TimeDelta interval);
};

}  

#endif  
