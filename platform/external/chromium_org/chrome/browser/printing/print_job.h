// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINT_JOB_H_
#define CHROME_BROWSER_PRINTING_PRINT_JOB_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "chrome/browser/printing/print_job_worker_owner.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Thread;

namespace base {
class RefCountedMemory;
}

namespace printing {

class JobEventDetails;
class MetafilePlayer;
class PdfToEmfConverter;
class PrintJobWorker;
class PrintedDocument;
class PrintedPage;
class PrintedPagesSource;
class PrinterQuery;

class PrintJob : public PrintJobWorkerOwner,
                 public content::NotificationObserver {
 public:
  
  
  PrintJob();

  
  
  void Initialize(PrintJobWorkerOwner* job, PrintedPagesSource* source,
                  int page_count);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void GetSettingsDone(const PrintSettings& new_settings,
                               PrintingContext::Result result) OVERRIDE;
  virtual PrintJobWorker* DetachWorker(PrintJobWorkerOwner* new_owner) OVERRIDE;
  virtual const PrintSettings& settings() const OVERRIDE;
  virtual int cookie() const OVERRIDE;

  
  
  void StartPrinting();

  
  
  
  
  
  void Stop();

  
  void Cancel();

  
  
  
  bool FlushJob(base::TimeDelta timeout);

  
  
  void DisconnectSource();

  
  
  bool is_job_pending() const;

  
  PrintedDocument* document() const;

#if defined(OS_WIN)
  void StartPdfToEmfConversion(
      const scoped_refptr<base::RefCountedMemory>& bytes,
      const gfx::Size& page_size,
      const gfx::Rect& content_area);
#endif  

 protected:
  virtual ~PrintJob();

 private:
  
  void UpdatePrintedDocument(PrintedDocument* new_document);

  
  void OnNotifyPrintJobEvent(const JobEventDetails& event_details);

  
  
  void OnDocumentDone();

  
  
  void ControlledWorkerShutdown();

  
  void Quit();

  void HoldUntilStopIsCalled();

#if defined(OS_WIN)
  void OnPdfToEmfStarted(int page_count);
  void OnPdfToEmfPageConverted(int page_number,
                               double scale_factor,
                               scoped_ptr<MetafilePlayer> emf);
#endif  

  content::NotificationRegistrar registrar_;

  
  
  PrintedPagesSource* source_;

  
  
  
  scoped_ptr<PrintJobWorker> worker_;

  
  PrintSettings settings_;

  
  scoped_refptr<PrintedDocument> document_;

  
  bool is_job_pending_;

  
  
  bool is_canceling_;

#if defined(OS_WIN)
  class PdfToEmfState;
  scoped_ptr<PdfToEmfState> ptd_to_emf_state_;
#endif  

  
  base::WeakPtrFactory<PrintJob> quit_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrintJob);
};

class JobEventDetails : public base::RefCountedThreadSafe<JobEventDetails> {
 public:
  
  enum Type {
    
    USER_INIT_DONE,

    
    USER_INIT_CANCELED,

    
    DEFAULT_INIT_DONE,

    
    NEW_DOC,

    
    NEW_PAGE,

    
    PAGE_DONE,

    
    
    DOC_DONE,

    
    
    JOB_DONE,

    
    ALL_PAGES_REQUESTED,

    
    FAILED,
  };

  JobEventDetails(Type type, PrintedDocument* document, PrintedPage* page);

  
  PrintedDocument* document() const;
  PrintedPage* page() const;
  Type type() const {
    return type_;
  }

 private:
  friend class base::RefCountedThreadSafe<JobEventDetails>;

  ~JobEventDetails();

  scoped_refptr<PrintedDocument> document_;
  scoped_refptr<PrintedPage> page_;
  const Type type_;

  DISALLOW_COPY_AND_ASSIGN(JobEventDetails);
};

}  

#endif  
