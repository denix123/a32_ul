// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINTER_QUERY_H_
#define CHROME_BROWSER_PRINTING_PRINTER_QUERY_H_

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/printing/print_job_worker_owner.h"
#include "printing/print_job_constants.h"

namespace base {
class DictionaryValue;
}

namespace printing {

class PrintDestinationInterface;
class PrintJobWorker;

class PrinterQuery : public PrintJobWorkerOwner {
 public:
  
  enum GetSettingsAskParam {
    DEFAULTS,
    ASK_USER,
  };

  PrinterQuery(int render_process_id, int render_view_id);

  
  virtual void GetSettingsDone(const PrintSettings& new_settings,
                               PrintingContext::Result result) OVERRIDE;
  virtual PrintJobWorker* DetachWorker(PrintJobWorkerOwner* new_owner) OVERRIDE;
  virtual const PrintSettings& settings() const OVERRIDE;
  virtual int cookie() const OVERRIDE;

  
  
  
  
  void GetSettings(
      GetSettingsAskParam ask_user_for_settings,
      int expected_page_count,
      bool has_selection,
      MarginType margin_type,
      const base::Closure& callback);

  
  void SetSettings(scoped_ptr<base::DictionaryValue> new_settings,
                   const base::Closure& callback);

  
  void StopWorker();

  
  bool is_callback_pending() const;

  PrintingContext::Result last_status() const { return last_status_; }

  
  bool is_valid() const;

 private:
  virtual ~PrinterQuery();

  
  void StartWorker(const base::Closure& callback);

  
  
  
  scoped_ptr<PrintJobWorker> worker_;

  
  PrintSettings settings_;

  
  bool is_print_dialog_box_shown_;

  
  int cookie_;

  
  PrintingContext::Result last_status_;

  
  base::Closure callback_;

  DISALLOW_COPY_AND_ASSIGN(PrinterQuery);
};

}  

#endif  
