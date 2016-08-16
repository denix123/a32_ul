// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CERTIFICATE_VIEWER_WEBUI_H_
#define CHROME_BROWSER_UI_WEBUI_CERTIFICATE_VIEWER_WEBUI_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/values.h"
#include "components/web_modal/native_web_contents_modal_dialog.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "net/cert/x509_certificate.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/web_dialogs/web_dialog_delegate.h"

namespace content {
class WebContents;
}

class ConstrainedWebDialogDelegate;

class CertificateViewerModalDialog : public ui::WebDialogDelegate {
 public:
  
  
  
  explicit CertificateViewerModalDialog(
      net::X509Certificate* cert);
  virtual ~CertificateViewerModalDialog();

  virtual void Show(content::WebContents* web_contents,
                    gfx::NativeWindow parent);
  virtual web_modal::NativeWebContentsModalDialog
  GetNativeWebContentsModalDialog();
  const content::WebUI* GetWebUI() const { return webui_; }

 protected:
  
  virtual ui::ModalType GetDialogModalType() const OVERRIDE;
  virtual base::string16 GetDialogTitle() const OVERRIDE;
  virtual GURL GetDialogContentURL() const OVERRIDE;
  virtual void GetWebUIMessageHandlers(
      std::vector<content::WebUIMessageHandler*>* handlers) const OVERRIDE;
  virtual void GetDialogSize(gfx::Size* size) const OVERRIDE;
  virtual std::string GetDialogArgs() const OVERRIDE;
  virtual void OnDialogShown(
      content::WebUI* webui,
      content::RenderViewHost* render_view_host) OVERRIDE;
  virtual void OnDialogClosed(const std::string& json_retval) OVERRIDE;
  virtual void OnCloseContents(
      content::WebContents* source, bool* out_close_dialog) OVERRIDE;
  virtual bool ShouldShowDialogTitle() const OVERRIDE;

  
  scoped_refptr<net::X509Certificate> cert_;

  
  base::string16 title_;

 private:
  content::WebUI* webui_;
  gfx::NativeWindow window_;
  DISALLOW_COPY_AND_ASSIGN(CertificateViewerModalDialog);
};

class CertificateViewerDialog : public CertificateViewerModalDialog {
 public:
  
  
  
  explicit CertificateViewerDialog(net::X509Certificate* cert);
  virtual ~CertificateViewerDialog();

  
  virtual void Show(content::WebContents* web_contents,
                    gfx::NativeWindow parent) OVERRIDE;
  virtual web_modal::NativeWebContentsModalDialog
  GetNativeWebContentsModalDialog() OVERRIDE;

 protected:
  
  virtual GURL GetDialogContentURL() const OVERRIDE;
  virtual ui::ModalType GetDialogModalType() const OVERRIDE;

 private:
  ConstrainedWebDialogDelegate* dialog_;

  DISALLOW_COPY_AND_ASSIGN(CertificateViewerDialog);
};

class CertificateViewerDialogHandler : public content::WebUIMessageHandler {
 public:
  CertificateViewerDialogHandler(CertificateViewerModalDialog* dialog,
                                 net::X509Certificate* cert);
  virtual ~CertificateViewerDialogHandler();

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  
  
  
  void ExportCertificate(const base::ListValue* args);

  
  
  
  
  
  void RequestCertificateFields(const base::ListValue* args);

  
  
  int GetCertificateIndex(const base::ListValue* args) const;

  
  scoped_refptr<net::X509Certificate> cert_;

  
  CertificateViewerModalDialog* dialog_;

  
  
  net::X509Certificate::OSCertHandles cert_chain_;

  DISALLOW_COPY_AND_ASSIGN(CertificateViewerDialogHandler);
};

#endif  
