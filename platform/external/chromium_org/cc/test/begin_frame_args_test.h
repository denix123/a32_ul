// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TEST_BEGIN_FRAME_ARGS_TEST_H_
#define CC_TEST_BEGIN_FRAME_ARGS_TEST_H_

#include <iosfwd>

#include "base/time/time.h"
#include "cc/output/begin_frame_args.h"
#include "cc/test/test_now_source.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace cc {

BeginFrameArgs CreateBeginFrameArgsForTesting();
BeginFrameArgs CreateBeginFrameArgsForTesting(base::TimeTicks frame_time);
BeginFrameArgs CreateBeginFrameArgsForTesting(int64 frame_time,
                                              int64 deadline,
                                              int64 interval);
BeginFrameArgs CreateExpiredBeginFrameArgsForTesting();

BeginFrameArgs CreateBeginFrameArgsForTesting(
    scoped_refptr<TestNowSource> now_src);
BeginFrameArgs CreateExpiredBeginFrameArgsForTesting(
    scoped_refptr<TestNowSource> now_src);


bool operator==(const BeginFrameArgs& lhs, const BeginFrameArgs& rhs);

::std::ostream& operator<<(::std::ostream& os, const BeginFrameArgs& args);
void PrintTo(const BeginFrameArgs& args, ::std::ostream* os);

}  

#endif  
