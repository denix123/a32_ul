// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_PRINT_PREVIEW_PRINT_PREVIEW_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_PRINT_PREVIEW_PRINT_PREVIEW_HANDLER_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/printing/print_view_manager_observer.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "google_apis/gaia/merge_session_helper.h"
#include "ui/shell_dialogs/select_file_dialog.h"

#if defined(ENABLE_SERVICE_DISCOVERY)
#include "chrome/browser/local_discovery/privet_local_printer_lister.h"
#include "chrome/browser/local_discovery/service_discovery_shared_client.h"
#endif  

class AccountReconcilor;
class PrintSystemTaskProxy;

namespace base {
class DictionaryValue;
class RefCountedBytes;
}

namespace content {
class WebContents;
}

namespace gfx {
class Size;
}

class PrintPreviewHandler
    : public content::WebUIMessageHandler,
#if defined(ENABLE_SERVICE_DISCOVERY)
      public local_discovery::PrivetLocalPrinterLister::Delegate,
      public local_discovery::PrivetLocalPrintOperation::Delegate,
#endif
      public ui::SelectFileDialog::Listener,
      public printing::PrintViewManagerObserver,
      public MergeSessionHelper::Observer {
 public:
  PrintPreviewHandler();
  virtual ~PrintPreviewHandler();

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;
  virtual void FileSelectionCanceled(void* params) OVERRIDE;

  
  virtual void OnPrintDialogShown() OVERRIDE;

  
  virtual void MergeSessionCompleted(
      const std::string& account_id,
      const GoogleServiceAuthError& error) OVERRIDE;

  
  void SelectFile(const base::FilePath& default_path);

  
  
  
  void OnPrintPreviewDialogDestroyed();

  
  void OnPrintPreviewFailed();

#if !defined(DISABLE_BASIC_PRINTING)
  
  
  void ShowSystemDialog();
#endif  

#if defined(ENABLE_SERVICE_DISCOVERY)
  
  virtual void LocalPrinterChanged(
      bool added,
      const std::string& name,
      bool has_local_printing,
      const local_discovery::DeviceDescription& description) OVERRIDE;
  virtual void LocalPrinterRemoved(const std::string& name) OVERRIDE;
  virtual void LocalPrinterCacheFlushed() OVERRIDE;

  
  virtual void OnPrivetPrintingDone(
      const local_discovery::PrivetLocalPrintOperation*
      print_operation) OVERRIDE;
  virtual void OnPrivetPrintingError(
      const local_discovery::PrivetLocalPrintOperation* print_operation,
        int http_code) OVERRIDE;
#endif  
  int regenerate_preview_request_count() const {
    return regenerate_preview_request_count_;
  }

  
  void SetPdfSavedClosureForTesting(const base::Closure& closure);

 private:
  friend class PrintPreviewPdfGeneratedBrowserTest;
  FRIEND_TEST_ALL_PREFIXES(PrintPreviewPdfGeneratedBrowserTest,
                           MANUAL_DummyTest);
  class AccessTokenService;

  static bool PrivetPrintingEnabled();

  content::WebContents* preview_web_contents() const;

  
  void HandleGetPrinters(const base::ListValue* args);

  
  void HandleGetPrivetPrinters(const base::ListValue* args);

  
  void HandleStopGetPrivetPrinters(const base::ListValue* args);

  
  
  void HandleGetPreview(const base::ListValue* args);

  
  
  void HandlePrint(const base::ListValue* args);

  
  
  void HandleHidePreview(const base::ListValue* args);

  
  void HandleCancelPendingPrintRequest(const base::ListValue* args);

  
  
  void HandleSaveAppState(const base::ListValue* args);

  
  void HandleGetPrinterCapabilities(const base::ListValue* args);

#if !defined(DISABLE_BASIC_PRINTING)
  
  
  void HandleShowSystemDialog(const base::ListValue* args);
#endif  

  
  void OnSigninComplete();

  
  
  void HandleSignin(const base::ListValue* args);

  
  void HandleGetAccessToken(const base::ListValue* args);

  
  
  void HandleManageCloudPrint(const base::ListValue* args);

  
  
  void HandleClosePreviewDialog(const base::ListValue* args);

  
  
  void HandleManagePrinters(const base::ListValue* args);

  
  
  void HandlePrintWithCloudPrintDialog(const base::ListValue* args);

  
  
  void HandleGetInitialSettings(const base::ListValue* args);

  
  
  void HandleReportUiEvent(const base::ListValue* args);

  
  
  
  
  
  
  
  void HandleForceOpenNewTab(const base::ListValue* args);

  void HandleGetPrivetPrinterCapabilities(const base::ListValue* arg);

  void SendInitialSettings(const std::string& default_printer);

  
  void SendAccessToken(const std::string& type,
                       const std::string& access_token);

  
  
  void SendPrinterCapabilities(const base::DictionaryValue* settings_info);

  
  
  void SendFailedToGetPrinterCapabilities(const std::string& printer_name);

  
  void SetupPrinterList(const base::ListValue* printers);

  
  void SendCloudPrintEnabled();

  
  void SendCloudPrintJob(const base::RefCountedBytes* data);

  
  void PrintToPdf();

  
  void PrintWithCloudPrintDialog();

  
  content::WebContents* GetInitiator() const;

  
  void ClosePreviewDialog();

  
  void ReportStats();

  
  void ClearInitiatorDetails();

  
  void PostPrintToPdfTask();

  
  void GetNumberFormatAndMeasurementSystem(base::DictionaryValue* settings);

  bool GetPreviewDataAndTitle(scoped_refptr<base::RefCountedBytes>* data,
                              base::string16* title) const;

#if defined(USE_CUPS)
  void SaveCUPSColorSetting(const base::DictionaryValue* settings);

  void ConvertColorSettingToCUPSColorModel(
      base::DictionaryValue* settings) const;
#endif

#if defined(ENABLE_SERVICE_DISCOVERY)
  void StartPrivetLister(const scoped_refptr<
      local_discovery::ServiceDiscoverySharedClient>& client);
  void OnPrivetCapabilities(const base::DictionaryValue* capabilities);
  void PrivetCapabilitiesUpdateClient(
      scoped_ptr<local_discovery::PrivetHTTPClient> http_client);
  void PrivetLocalPrintUpdateClient(
      std::string print_ticket,
      std::string capabilities,
      gfx::Size page_size,
      scoped_ptr<local_discovery::PrivetHTTPClient> http_client);
  bool PrivetUpdateClient(
      scoped_ptr<local_discovery::PrivetHTTPClient> http_client);
  void StartPrivetLocalPrint(const std::string& print_ticket,
                             const std::string& capabilities,
                             const gfx::Size& page_size);
  void SendPrivetCapabilitiesError(const std::string& id);
  void PrintToPrivetPrinter(const std::string& printer_name,
                            const std::string& print_ticket,
                            const std::string& capabilities,
                            const gfx::Size& page_size);
  bool CreatePrivetHTTP(
      const std::string& name,
      const local_discovery::PrivetHTTPAsynchronousFactory::ResultCallback&
          callback);
  void FillPrinterDescription(
      const std::string& name,
      const local_discovery::DeviceDescription& description,
      bool has_local_printing,
      base::DictionaryValue* printer_value);
#endif

  
  
  void RegisterForMergeSession();
  void UnregisterForMergeSession();

  
  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;

  
  
  int regenerate_preview_request_count_;

  
  int manage_printers_dialog_request_count_;
  int manage_cloud_printers_dialog_request_count_;

  
  bool reported_failed_preview_;

  
  bool has_logged_printers_count_;

  
  
  base::FilePath print_to_pdf_path_;

  
  scoped_ptr<AccessTokenService> token_service_;

  
  
  AccountReconcilor* reconcilor_;

#if defined(ENABLE_SERVICE_DISCOVERY)
  scoped_refptr<local_discovery::ServiceDiscoverySharedClient>
      service_discovery_client_;
  scoped_ptr<local_discovery::PrivetLocalPrinterLister> printer_lister_;

  scoped_ptr<local_discovery::PrivetHTTPAsynchronousFactory>
      privet_http_factory_;
  scoped_ptr<local_discovery::PrivetHTTPResolution> privet_http_resolution_;
  scoped_ptr<local_discovery::PrivetV1HTTPClient> privet_http_client_;
  scoped_ptr<local_discovery::PrivetJSONOperation>
      privet_capabilities_operation_;
  scoped_ptr<local_discovery::PrivetLocalPrintOperation>
      privet_local_print_operation_;
#endif

  
  
  base::Closure pdf_file_saved_closure_;

  base::WeakPtrFactory<PrintPreviewHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrintPreviewHandler);
};

#endif  
