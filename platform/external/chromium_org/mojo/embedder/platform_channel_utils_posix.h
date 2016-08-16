// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_PLATFORM_CHANNEL_UTILS_POSIX_H_
#define MOJO_EMBEDDER_PLATFORM_CHANNEL_UTILS_POSIX_H_

#include <stddef.h>
#include <sys/types.h>  

#include <deque>

#include "base/memory/scoped_ptr.h"
#include "mojo/embedder/platform_handle.h"
#include "mojo/system/system_impl_export.h"

struct iovec;  

namespace mojo {
namespace embedder {

const size_t kPlatformChannelMaxNumHandles = 7;

MOJO_SYSTEM_IMPL_EXPORT ssize_t
    PlatformChannelWrite(PlatformHandle h, const void* bytes, size_t num_bytes);
MOJO_SYSTEM_IMPL_EXPORT ssize_t
    PlatformChannelWritev(PlatformHandle h, struct iovec* iov, size_t num_iov);

MOJO_SYSTEM_IMPL_EXPORT ssize_t
    PlatformChannelSendmsgWithHandles(PlatformHandle h,
                                      struct iovec* iov,
                                      size_t num_iov,
                                      PlatformHandle* platform_handles,
                                      size_t num_platform_handles);

MOJO_SYSTEM_IMPL_EXPORT bool PlatformChannelSendHandles(PlatformHandle h,
                                                        PlatformHandle* handles,
                                                        size_t num_handles);

MOJO_SYSTEM_IMPL_EXPORT ssize_t
    PlatformChannelRecvmsg(PlatformHandle h,
                           void* buf,
                           size_t num_bytes,
                           std::deque<PlatformHandle>* platform_handles);

}  
}  

#endif  
