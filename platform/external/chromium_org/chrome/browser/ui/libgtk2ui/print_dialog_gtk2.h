// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_PRINT_DIALOG_GTK2_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_PRINT_DIALOG_GTK2_H_

#include <gtk/gtk.h>
#include <gtk/gtkunixprint.h>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal.h"
#include "content/public/browser/browser_thread.h"
#include "printing/print_dialog_gtk_interface.h"
#include "printing/printing_context_linux.h"
#include "ui/aura/window_observer.h"

namespace printing {
class MetafilePlayer;
class PrintSettings;
}

using printing::PrintingContextLinux;

class PrintDialogGtk2
    : public printing::PrintDialogGtkInterface,
      public base::RefCountedThreadSafe<
          PrintDialogGtk2, content::BrowserThread::DeleteOnUIThread>,
      public aura::WindowObserver {
 public:
  
  static printing::PrintDialogGtkInterface* CreatePrintDialog(
      PrintingContextLinux* context);

  
  virtual void UseDefaultSettings() OVERRIDE;
  virtual bool UpdateSettings(printing::PrintSettings* settings) OVERRIDE;
  virtual void ShowDialog(
      gfx::NativeView parent_view,
      bool has_selection,
      const PrintingContextLinux::PrintSettingsCallback& callback) OVERRIDE;
  virtual void PrintDocument(const printing::MetafilePlayer& metafile,
                             const base::string16& document_name) OVERRIDE;
  virtual void AddRefToDialog() OVERRIDE;
  virtual void ReleaseDialog() OVERRIDE;

 private:
  friend struct content::BrowserThread::DeleteOnThread<
      content::BrowserThread::UI>;
  friend class base::DeleteHelper<PrintDialogGtk2>;

  explicit PrintDialogGtk2(PrintingContextLinux* context);
  virtual ~PrintDialogGtk2();

  
  CHROMEGTK_CALLBACK_1(PrintDialogGtk2, void, OnResponse, int);

  
  void SendDocumentToPrinter(const base::string16& document_name);

  
  static void OnJobCompletedThunk(GtkPrintJob* print_job,
                                  gpointer user_data,
                                  GError* error);
  void OnJobCompleted(GtkPrintJob* print_job, GError* error);

  
  
  void InitPrintSettings(printing::PrintSettings* settings);

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  
  PrintingContextLinux::PrintSettingsCallback callback_;
  PrintingContextLinux* context_;

  
  
  GtkWidget* dialog_;
  GtkPrintSettings* gtk_settings_;
  GtkPageSetup* page_setup_;
  GtkPrinter* printer_;

  base::FilePath path_to_pdf_;

  DISALLOW_COPY_AND_ASSIGN(PrintDialogGtk2);
};

#endif  
