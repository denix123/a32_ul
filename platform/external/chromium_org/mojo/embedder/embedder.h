// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_EMBEDDER_H_
#define MOJO_EMBEDDER_EMBEDDER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/task_runner.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/public/cpp/system/core.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace embedder {

class PlatformSupport;

MOJO_SYSTEM_IMPL_EXPORT void Init(scoped_ptr<PlatformSupport> platform_support);

// this "pipe" should be connected and ready for operation (e.g., to be written
// (E.g., a message written immediately to the returned handle will be queued
struct ChannelInfo;

MOJO_SYSTEM_IMPL_EXPORT ScopedMessagePipeHandle
    CreateChannelOnIOThread(ScopedPlatformHandle platform_handle,
                            ChannelInfo** channel_info);

typedef base::Callback<void(ChannelInfo*)> DidCreateChannelCallback;
MOJO_SYSTEM_IMPL_EXPORT ScopedMessagePipeHandle
    CreateChannel(ScopedPlatformHandle platform_handle,
                  scoped_refptr<base::TaskRunner> io_thread_task_runner,
                  DidCreateChannelCallback callback,
                  scoped_refptr<base::TaskRunner> callback_thread_task_runner);

MOJO_SYSTEM_IMPL_EXPORT void DestroyChannelOnIOThread(
    ChannelInfo* channel_info);

MOJO_SYSTEM_IMPL_EXPORT void DestroyChannel(ChannelInfo* channel_info);

MOJO_SYSTEM_IMPL_EXPORT void WillDestroyChannelSoon(ChannelInfo* channel_info);

MOJO_SYSTEM_IMPL_EXPORT MojoResult
    CreatePlatformHandleWrapper(ScopedPlatformHandle platform_handle,
                                MojoHandle* platform_handle_wrapper_handle);
MOJO_SYSTEM_IMPL_EXPORT MojoResult
    PassWrappedPlatformHandle(MojoHandle platform_handle_wrapper_handle,
                              ScopedPlatformHandle* platform_handle);

}  
}  

#endif  
