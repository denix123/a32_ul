// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINT_JOB_WORKER_H_
#define CHROME_BROWSER_PRINTING_PRINT_JOB_WORKER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "content/public/browser/browser_thread.h"
#include "printing/page_number.h"
#include "printing/print_job_constants.h"
#include "printing/printing_context.h"

namespace base {
class DictionaryValue;
}

namespace printing {

class PrintJob;
class PrintJobWorkerOwner;
class PrintedDocument;
class PrintedPage;

class PrintJobWorker {
 public:
  PrintJobWorker(int render_process_id,
                 int render_view_id,
                 PrintJobWorkerOwner* owner);
  virtual ~PrintJobWorker();

  void SetNewOwner(PrintJobWorkerOwner* new_owner);

  
  
  void GetSettings(
      bool ask_user_for_settings,
      int document_page_count,
      bool has_selection,
      MarginType margin_type);

  
  void SetSettings(scoped_ptr<base::DictionaryValue> new_settings);

  
  
  void StartPrinting(PrintedDocument* new_document);

  
  void OnDocumentChanged(PrintedDocument* new_document);

  
  
  
  void OnNewPage();

  
  void Cancel();

  
  bool IsRunning() const;

  
  bool PostTask(const tracked_objects::Location& from_here,
                const base::Closure& task);

  
  void StopSoon();

  
  void Stop();

  
  bool Start();

 protected:
  
  PrintingContext* printing_context() { return printing_context_.get(); }

 private:
  
  
  
  
  
  class NotificationTask;

  
  void SpoolPage(PrintedPage* page);

  
  void OnDocumentDone();

  
  
  void OnFailure();

  
  
  
  void GetSettingsWithUI(
      int document_page_count,
      bool has_selection);

  
  
  
  void GetSettingsWithUIDone(PrintingContext::Result result);

  
  void UpdatePrintSettings(scoped_ptr<base::DictionaryValue> new_settings);

  
  void GetSettingsDone(PrintingContext::Result result);

  
  
  
  void UseDefaultSettings();

  
  scoped_ptr<PrintingContext::Delegate> printing_context_delegate_;

  
  scoped_ptr<PrintingContext> printing_context_;

  
  scoped_refptr<PrintedDocument> document_;

  
  
  PrintJobWorkerOwner* owner_;

  
  PageNumber page_number_;

  
  base::Thread thread_;

  
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  
  base::WeakPtrFactory<PrintJobWorker> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrintJobWorker);
};

}  

#endif  
