// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_TRACING_TRACING_CONSUMER_WIN_H_
#define CONTENT_BROWSER_TRACING_TRACING_CONSUMER_WIN_H_

#include "base/bind.h"
#include "base/memory/ref_counted_memory.h"
#include "base/threading/thread.h"
#include "base/values.h"
#include "base/win/event_trace_consumer.h"
#include "base/win/event_trace_controller.h"

template <typename Type>
struct DefaultSingletonTraits;

namespace content {

class EtwSystemEventConsumer :
    public base::win::EtwTraceConsumerBase<EtwSystemEventConsumer> {
 public:
  typedef base::Callback<void(const scoped_refptr<base::RefCountedString>&)>
      OutputCallback;

  bool StartSystemTracing();
  void StopSystemTracing(const OutputCallback& callback);

  
  static EtwSystemEventConsumer* GetInstance();

 private:
  
  
  friend struct DefaultSingletonTraits<EtwSystemEventConsumer>;

  
  EtwSystemEventConsumer();
  virtual ~EtwSystemEventConsumer();

  void AddSyncEventToBuffer();
  void AppendEventToBuffer(EVENT_TRACE* event);

  
  
  friend class base::win::EtwTraceConsumerBase<EtwSystemEventConsumer>;
  static void ProcessEvent(EVENT_TRACE* event);

  
  
  bool StartKernelSessionTracing();

  
  
  
  bool StopKernelSessionTracing();

  void OnStopSystemTracingDone(
    const OutputCallback& callback,
    const scoped_refptr<base::RefCountedString>& result);

  void TraceAndConsumeOnThread();
  void FlushOnThread(const OutputCallback& callback);

  scoped_ptr<base::ListValue> events_;
  base::Thread thread_;
  TRACEHANDLE session_handle_;
  base::win::EtwTraceProperties properties_;

  DISALLOW_COPY_AND_ASSIGN(EtwSystemEventConsumer);
};

}  

#endif  
