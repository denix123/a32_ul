// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_COMMON_TIME_HELPER_H_
#define MOJO_COMMON_TIME_HELPER_H_

#include "base/time/time.h"
#include "mojo/common/mojo_common_export.h"

namespace base {
class TickClock;
}

namespace mojo {
namespace common {
namespace test {

MOJO_COMMON_EXPORT void SetTickClockForTest(base::TickClock* clock);

}  

namespace internal {

MOJO_COMMON_EXPORT base::TimeTicks NowTicks();

}  
}  
}  

#endif  
