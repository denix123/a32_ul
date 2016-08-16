// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FEEDBACK_FEEDBACK_DATA_H_
#define COMPONENTS_FEEDBACK_FEEDBACK_DATA_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "components/feedback/feedback_common.h"
#include "url/gurl.h"

namespace base {
class FilePath;
class RefCountedString;
}
namespace content {
class BrowserContext;
}

namespace feedback {

class FeedbackData : public FeedbackCommon {
 public:
  FeedbackData();

  
  void OnFeedbackPageDataComplete();

  
  
  void SetAndCompressSystemInfo(scoped_ptr<SystemLogsMap> sys_info);

  
  
  void SetAndCompressHistograms(scoped_ptr<std::string> histograms);

  
  void AttachAndCompressFileData(scoped_ptr<std::string> attached_filedata);

  
  void OnCompressLogsComplete(scoped_ptr<std::string> compressed_logs);

  
  void OnCompressFileComplete(scoped_ptr<std::string> compressed_file);

  
  
  
  bool IsDataComplete();

  
  void SendReport();

  
  content::BrowserContext* context() const { return context_; }
  const std::string& attached_file_uuid() const { return attached_file_uuid_; }
  const std::string& screenshot_uuid() const { return screenshot_uuid_; }

  
  void set_context(content::BrowserContext* context) { context_ = context; }
  void set_attached_filename(const std::string& attached_filename) {
    attached_filename_ = attached_filename;
  }
  void set_attached_file_uuid(const std::string& uuid) {
    attached_file_uuid_ = uuid;
  }
  void set_screenshot_uuid(const std::string& uuid) {
    screenshot_uuid_ = uuid;
  }
  void set_trace_id(int trace_id) { trace_id_ = trace_id; }
  void set_send_report_callback(
      const base::Callback<void(scoped_refptr<FeedbackData>)>& send_report) {
    send_report_ = send_report;
  }

 private:
  virtual ~FeedbackData();

  
  void OnCompressComplete();

  void OnGetTraceData(int trace_id,
                      scoped_refptr<base::RefCountedString> trace_data);

  base::Callback<void(scoped_refptr<FeedbackData>)> send_report_;

  content::BrowserContext* context_;

  std::string attached_filename_;
  std::string attached_file_uuid_;
  std::string screenshot_uuid_;

  int trace_id_;

  int pending_op_count_;
  bool report_sent_;

  DISALLOW_COPY_AND_ASSIGN(FeedbackData);
};

}  

#endif  
