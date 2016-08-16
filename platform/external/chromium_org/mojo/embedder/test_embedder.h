// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_TEST_EMBEDDER_H_
#define MOJO_EMBEDDER_TEST_EMBEDDER_H_

#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace embedder {
namespace test {

MOJO_SYSTEM_IMPL_EXPORT void InitWithSimplePlatformSupport();

MOJO_SYSTEM_IMPL_EXPORT bool Shutdown();

}  
}  
}  

#endif  
