// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_CHANNEL_INIT_H_
#define MOJO_EMBEDDER_CHANNEL_INIT_H_

#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "mojo/public/cpp/system/core.h"
#include "mojo/system/system_impl_export.h"

namespace base {
class MessageLoopProxy;
class TaskRunner;
}

namespace mojo {
namespace embedder {
struct ChannelInfo;
}

namespace embedder {

class MOJO_SYSTEM_IMPL_EXPORT ChannelInit {
 public:
  ChannelInit();
  ~ChannelInit();

  
  
  mojo::ScopedMessagePipeHandle Init(
      base::PlatformFile file,
      scoped_refptr<base::TaskRunner> io_thread_task_runner);

  
  void WillDestroySoon();

 private:
  
  
  
  static void OnCreatedChannel(base::WeakPtr<ChannelInit> self,
                               scoped_refptr<base::TaskRunner> io_thread,
                               ChannelInfo* channel);

  scoped_refptr<base::TaskRunner> io_thread_task_runner_;

  
  ChannelInfo* channel_info_;

  base::WeakPtrFactory<ChannelInit> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChannelInit);
};

}  
}  

#endif  
