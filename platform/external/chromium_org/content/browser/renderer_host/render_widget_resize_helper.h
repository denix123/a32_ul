// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_RESIZE_HELPER_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_RESIZE_HELPER_H_

#include "base/lazy_instance.h"
#include "base/single_thread_task_runner.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "ipc/ipc_message.h"

namespace content {

class RenderWidgetResizeHelper {
 public:
  static RenderWidgetResizeHelper* Get();
  scoped_refptr<base::SingleThreadTaskRunner> task_runner() const;

  

  
  
  bool WaitForSingleTaskToRun(const base::TimeDelta& max_delay);

  

  
  
  
  
  void PostRendererProcessMsg(int render_process_id, const IPC::Message& msg);

  
  
  void PostGpuProcessMsg(int gpu_host_id, const IPC::Message& msg);

 private:
  friend struct base::DefaultLazyInstanceTraits<RenderWidgetResizeHelper>;
  RenderWidgetResizeHelper();
  ~RenderWidgetResizeHelper();

  
  
  static void EventTimedWait(
      base::WaitableEvent* event,
      base::TimeDelta delay);

  
  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidgetResizeHelper);
};

}  

#endif  
