// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_TEST_SUPPORT_TEST_UTILS_H_
#define MOJO_PUBLIC_CPP_TEST_SUPPORT_TEST_UTILS_H_

#include <string>

#include "mojo/public/cpp/system/core.h"

namespace mojo {
namespace test {

bool WriteTextMessage(const MessagePipeHandle& handle, const std::string& text);

bool ReadTextMessage(const MessagePipeHandle& handle, std::string* text);

bool DiscardMessage(const MessagePipeHandle& handle);

typedef void (*PerfTestSingleIteration)(void* closure);
void IterateAndReportPerf(const char* test_name,
                          PerfTestSingleIteration single_iteration,
                          void* closure);

}  
}  

#endif  
