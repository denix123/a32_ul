// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINTING_CONTEXT_H_
#define PRINTING_PRINTING_CONTEXT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/strings/string16.h"
#include "printing/print_settings.h"
#include "ui/gfx/native_widget_types.h"

namespace base {
class DictionaryValue;
}

namespace printing {

class PRINTING_EXPORT PrintingContext {
 public:
  
  class Delegate {
   public:
    Delegate() {};
    virtual ~Delegate() {};

    
    virtual gfx::NativeView GetParentView() = 0;

    
    virtual std::string GetAppLocale() = 0;
  };

  
  enum Result {
    OK,
    CANCEL,
    FAILED,
  };

  virtual ~PrintingContext();

  
  
  typedef base::Callback<void(Result)> PrintSettingsCallback;

  
  
  
  
  virtual void AskUserForSettings(int max_pages,
                                  bool has_selection,
                                  const PrintSettingsCallback& callback) = 0;

  
  
  virtual Result UseDefaultSettings() = 0;

  
  Result UsePdfSettings();

  
  virtual gfx::Size GetPdfPaperSizeDeviceUnits() = 0;

  
  
  
  virtual Result UpdatePrinterSettings(bool external_preview,
                                       bool show_system_dialog) = 0;

  
  
  Result UpdatePrintSettings(const base::DictionaryValue& job_settings);

  
  virtual Result InitWithSettings(const PrintSettings& settings) = 0;

  
  
  
  
  
  
  virtual Result NewDocument(const base::string16& document_name) = 0;

  
  virtual Result NewPage() = 0;

  
  virtual Result PageDone() = 0;

  
  
  virtual Result DocumentDone() = 0;

  
  
  virtual void Cancel() = 0;

  
  virtual void ReleaseContext() = 0;

  
  virtual gfx::NativeDrawingContext context() const = 0;

  
  
  static scoped_ptr<PrintingContext> Create(Delegate* delegate);

  void set_margin_type(MarginType type);

  const PrintSettings& settings() const {
    return settings_;
  }

 protected:
  explicit PrintingContext(Delegate* delegate);

  
  void ResetSettings();

  
  PrintingContext::Result OnError();

  
  PrintSettings settings_;

  
  Delegate* delegate_;

  
  volatile bool dialog_box_dismissed_;

  
  volatile bool in_print_job_;

  
  volatile bool abort_printing_;

 private:
  DISALLOW_COPY_AND_ASSIGN(PrintingContext);
};

}  

#endif  
