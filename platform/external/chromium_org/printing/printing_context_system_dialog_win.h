// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINTING_CONTEXT_SYSTEM_DIALOG_WIN_H_
#define PRINTING_PRINTING_CONTEXT_SYSTEM_DIALOG_WIN_H_

#include <ocidl.h>
#include <commdlg.h>

#include <string>

#include "printing/printing_context_win.h"
#include "ui/gfx/native_widget_types.h"

namespace printing {

class PRINTING_EXPORT PrintingContextSytemDialogWin
    : public PrintingContextWin {
 public:
  explicit PrintingContextSytemDialogWin(Delegate* delegate);
  virtual ~PrintingContextSytemDialogWin();

  
  virtual void AskUserForSettings(
      int max_pages,
      bool has_selection,
      const PrintSettingsCallback& callback) OVERRIDE;
  virtual void Cancel() OVERRIDE;

 private:
  friend class MockPrintingContextWin;

  virtual HRESULT ShowPrintDialog(PRINTDLGEX* options);

  
  
  bool InitializeSettings(const DEVMODE& dev_mode,
                          const std::wstring& new_device_name,
                          const PRINTPAGERANGE* ranges,
                          int number_ranges,
                          bool selection_only);

  
  Result ParseDialogResultEx(const PRINTDLGEX& dialog_options);
  Result ParseDialogResult(const PRINTDLG& dialog_options);

  
  volatile HWND dialog_box_;

  DISALLOW_COPY_AND_ASSIGN(PrintingContextSytemDialogWin);
};

}  

#endif  
