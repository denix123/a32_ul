// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINTING_CONTEXT_LINUX_H_
#define PRINTING_PRINTING_CONTEXT_LINUX_H_

#include <string>

#include "printing/printing_context.h"

namespace base {
class DictionaryValue;
}

namespace printing {

class MetafilePlayer;
class PrintDialogGtkInterface;

class PRINTING_EXPORT PrintingContextLinux : public PrintingContext {
 public:
  explicit PrintingContextLinux(Delegate* delegate);
  virtual ~PrintingContextLinux();

  
  static void SetCreatePrintDialogFunction(
      PrintDialogGtkInterface* (*create_dialog_func)(
          PrintingContextLinux* context));

  
  static void SetPdfPaperSizeFunction(
      gfx::Size (*get_pdf_paper_size)(PrintingContextLinux* context));

  
  void PrintDocument(const MetafilePlayer& metafile);

  
  virtual void AskUserForSettings(
      int max_pages,
      bool has_selection,
      const PrintSettingsCallback& callback) OVERRIDE;
  virtual gfx::Size GetPdfPaperSizeDeviceUnits() OVERRIDE;
  virtual Result UseDefaultSettings() OVERRIDE;
  virtual Result UpdatePrinterSettings(bool external_preview,
                                       bool show_system_dialog) OVERRIDE;
  virtual Result InitWithSettings(const PrintSettings& settings) OVERRIDE;
  virtual Result NewDocument(const base::string16& document_name) OVERRIDE;
  virtual Result NewPage() OVERRIDE;
  virtual Result PageDone() OVERRIDE;
  virtual Result DocumentDone() OVERRIDE;
  virtual void Cancel() OVERRIDE;
  virtual void ReleaseContext() OVERRIDE;
  virtual gfx::NativeDrawingContext context() const OVERRIDE;

 private:
  base::string16 document_name_;
  PrintDialogGtkInterface* print_dialog_;

  DISALLOW_COPY_AND_ASSIGN(PrintingContextLinux);
};

}  

#endif  
