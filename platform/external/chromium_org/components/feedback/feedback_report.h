// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FEEDBACK_FEEDBACK_REPORT_H_
#define COMPONENTS_FEEDBACK_FEEDBACK_REPORT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace base {
class SequencedTaskRunner;
}

namespace feedback {

typedef base::Callback<void(const std::string&)> QueueCallback;

class FeedbackReport : public base::RefCounted<FeedbackReport> {
 public:
  FeedbackReport(const base::FilePath& path,
                 const base::Time& upload_at,
                 const std::string& data,
                 scoped_refptr<base::SequencedTaskRunner> task_runner);

  
  // written.
  void DeleteReportOnDisk();

  const base::Time& upload_at() const { return upload_at_; }
  const std::string& data() const { return data_; }

  
  
  static void LoadReportsAndQueue(const base::FilePath& user_dir,
                                  QueueCallback callback);

 private:
  friend class base::RefCounted<FeedbackReport>;
  virtual ~FeedbackReport();

  
  base::FilePath file_;

  base::FilePath reports_path_;
  base::Time upload_at_;  
  std::string data_;

  scoped_refptr<base::SequencedTaskRunner> reports_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(FeedbackReport);
};

}  

#endif  
