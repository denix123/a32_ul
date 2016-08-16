// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_TRACING_CONTROLLER_H_
#define CONTENT_PUBLIC_BROWSER_TRACING_CONTROLLER_H_

#include <set>
#include <string>

#include "base/callback.h"
#include "base/debug/trace_event.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"

namespace content {

class TracingController;

class TracingController {
 public:

  CONTENT_EXPORT static TracingController* GetInstance();

  
  
  
  
  
  
  
  class CONTENT_EXPORT TraceDataSink
      : public base::RefCountedThreadSafe<TraceDataSink> {
   public:
    virtual void AddTraceChunk(const std::string& chunk) {}
    virtual void SetSystemTrace(const std::string& data) {}
    virtual void Close() {}

   protected:
    friend class base::RefCountedThreadSafe<TraceDataSink>;
    virtual ~TraceDataSink() {}
  };

  
  
  CONTENT_EXPORT static scoped_refptr<TraceDataSink> CreateStringSink(
      const base::Callback<void(base::RefCountedString*)>& callback);

  
  
  CONTENT_EXPORT static scoped_refptr<TraceDataSink> CreateFileSink(
      const base::FilePath& file_path,
      const base::Closure& callback);

  
  
  
  
  
  
  typedef base::Callback<void(const std::set<std::string>&)>
      GetCategoriesDoneCallback;
  virtual bool GetCategories(
      const GetCategoriesDoneCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef base::Callback<void()> EnableRecordingDoneCallback;
  virtual bool EnableRecording(
      const base::debug::CategoryFilter& category_filter,
      const base::debug::TraceOptions& trace_options,
      const EnableRecordingDoneCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual bool DisableRecording(
      const scoped_refptr<TraceDataSink>& trace_data_sink) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  typedef base::Callback<void()> EnableMonitoringDoneCallback;
  virtual bool EnableMonitoring(
      const base::debug::CategoryFilter& category_filter,
      const base::debug::TraceOptions& trace_options,
      const EnableMonitoringDoneCallback& callback) = 0;

  
  
  
  
  typedef base::Callback<void()> DisableMonitoringDoneCallback;
  virtual bool DisableMonitoring(
      const DisableMonitoringDoneCallback& callback) = 0;

  
  virtual void GetMonitoringStatus(
      bool* out_enabled,
      base::debug::CategoryFilter* out_category_filter,
      base::debug::TraceOptions* out_trace_options) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual bool CaptureMonitoringSnapshot(
      const scoped_refptr<TraceDataSink>& trace_data_sink) = 0;

  
  
  
  typedef base::Callback<void(float)> GetTraceBufferPercentFullCallback;
  virtual bool GetTraceBufferPercentFull(
      const GetTraceBufferPercentFullCallback& callback) = 0;

  
  
  typedef base::Callback<void()> WatchEventCallback;
  virtual bool SetWatchEvent(const std::string& category_name,
                             const std::string& event_name,
                             const WatchEventCallback& callback) = 0;

  
  
  virtual bool CancelWatchEvent() = 0;

 protected:
  virtual ~TracingController() {}
};

}  

#endif  
