// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINT_JOB_WORKER_OWNER_H__
#define CHROME_BROWSER_PRINTING_PRINT_JOB_WORKER_OWNER_H__

#include "base/memory/ref_counted.h"
#include "printing/printing_context.h"

namespace base {
class MessageLoop;
class SequencedTaskRunner;
}

namespace tracked_objects {
class Location;
}

namespace printing {

class PrintJobWorker;
class PrintSettings;

class PrintJobWorkerOwner
    : public base::RefCountedThreadSafe<PrintJobWorkerOwner> {
 public:
  PrintJobWorkerOwner();

  
  
  
  virtual void GetSettingsDone(const PrintSettings& new_settings,
                               PrintingContext::Result result) = 0;

  
  virtual PrintJobWorker* DetachWorker(PrintJobWorkerOwner* new_owner) = 0;

  
  virtual const PrintSettings& settings() const = 0;

  
  virtual int cookie() const = 0;

  
  
  
  bool RunsTasksOnCurrentThread() const;

  
  bool PostTask(const tracked_objects::Location& from_here,
                const base::Closure& task);

 protected:
  friend class base::RefCountedThreadSafe<PrintJobWorkerOwner>;

  virtual ~PrintJobWorkerOwner();

  
  
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
};

}  

#endif  
