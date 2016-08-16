// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_WEB_VIEW_WEB_VIEW_INTERNAL_API_H_
#define EXTENSIONS_BROWSER_API_WEB_VIEW_WEB_VIEW_INTERNAL_API_H_

#include "extensions/browser/api/capture_web_contents_function.h"
#include "extensions/browser/api/execute_code_function.h"
#include "extensions/browser/extension_function.h"
#include "extensions/browser/guest_view/web_view/web_view_guest.h"

namespace extensions {

class WebViewInternalExtensionFunction : public AsyncExtensionFunction {
 public:
  WebViewInternalExtensionFunction() {}

 protected:
  virtual ~WebViewInternalExtensionFunction() {}

  
  virtual bool RunAsync() OVERRIDE FINAL;

 private:
  virtual bool RunAsyncSafe(WebViewGuest* guest) = 0;
};

class WebViewInternalNavigateFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.navigate",
                             WEBVIEWINTERNAL_NAVIGATE);
  WebViewInternalNavigateFunction() {}

 protected:
  virtual ~WebViewInternalNavigateFunction() {}

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalNavigateFunction);
};

class WebViewInternalExecuteCodeFunction
    : public extensions::ExecuteCodeFunction {
 public:
  WebViewInternalExecuteCodeFunction();

 protected:
  virtual ~WebViewInternalExecuteCodeFunction();

  
  virtual bool Init() OVERRIDE;
  virtual bool ShouldInsertCSS() const OVERRIDE;
  virtual bool CanExecuteScriptOnPage() OVERRIDE;
  
  virtual extensions::ScriptExecutor* GetScriptExecutor() OVERRIDE FINAL;
  virtual bool IsWebView() const OVERRIDE;
  virtual const GURL& GetWebViewSrc() const OVERRIDE;

 private:
  
  
  extensions::ExtensionResource resource_;

  int guest_instance_id_;

  GURL guest_src_;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalExecuteCodeFunction);
};

class WebViewInternalExecuteScriptFunction
    : public WebViewInternalExecuteCodeFunction {
 public:
  WebViewInternalExecuteScriptFunction();

 protected:
  virtual ~WebViewInternalExecuteScriptFunction() {}

  virtual void OnExecuteCodeFinished(const std::string& error,
                                     const GURL& on_url,
                                     const base::ListValue& result) OVERRIDE;

  DECLARE_EXTENSION_FUNCTION("webViewInternal.executeScript",
                             WEBVIEWINTERNAL_EXECUTESCRIPT)

 private:
  DISALLOW_COPY_AND_ASSIGN(WebViewInternalExecuteScriptFunction);
};

class WebViewInternalInsertCSSFunction
    : public WebViewInternalExecuteCodeFunction {
 public:
  WebViewInternalInsertCSSFunction();

 protected:
  virtual ~WebViewInternalInsertCSSFunction() {}

  virtual bool ShouldInsertCSS() const OVERRIDE;

  DECLARE_EXTENSION_FUNCTION("webViewInternal.insertCSS",
                             WEBVIEWINTERNAL_INSERTCSS)

 private:
  DISALLOW_COPY_AND_ASSIGN(WebViewInternalInsertCSSFunction);
};

class WebViewInternalCaptureVisibleRegionFunction
    : public extensions::CaptureWebContentsFunction {
  DECLARE_EXTENSION_FUNCTION("webViewInternal.captureVisibleRegion",
                             WEBVIEWINTERNAL_CAPTUREVISIBLEREGION);

  WebViewInternalCaptureVisibleRegionFunction();

 protected:
  virtual ~WebViewInternalCaptureVisibleRegionFunction();

 private:
  
  virtual bool IsScreenshotEnabled() OVERRIDE;
  virtual content::WebContents* GetWebContentsForID(int id) OVERRIDE;
  virtual void OnCaptureFailure(FailureReason reason) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalCaptureVisibleRegionFunction);
};

class WebViewInternalSetNameFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.setName",
                             WEBVIEWINTERNAL_SETNAME);

  WebViewInternalSetNameFunction();

 protected:
  virtual ~WebViewInternalSetNameFunction();

 private:
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalSetNameFunction);
};

class WebViewInternalSetAllowTransparencyFunction :
    public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.setAllowTransparency",
                             WEBVIEWINTERNAL_SETALLOWTRANSPARENCY);

  WebViewInternalSetAllowTransparencyFunction();

 protected:
  virtual ~WebViewInternalSetAllowTransparencyFunction();

 private:
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalSetAllowTransparencyFunction);
};

class WebViewInternalSetZoomFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.setZoom",
                             WEBVIEWINTERNAL_SETZOOM);

  WebViewInternalSetZoomFunction();

 protected:
  virtual ~WebViewInternalSetZoomFunction();

 private:
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalSetZoomFunction);
};

class WebViewInternalGetZoomFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.getZoom",
                             WEBVIEWINTERNAL_GETZOOM);

  WebViewInternalGetZoomFunction();

 protected:
  virtual ~WebViewInternalGetZoomFunction();

 private:
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalGetZoomFunction);
};

class WebViewInternalFindFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.find", WEBVIEWINTERNAL_FIND);

  WebViewInternalFindFunction();

  
  using WebViewInternalExtensionFunction::SendResponse;

 protected:
  virtual ~WebViewInternalFindFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalFindFunction);
};

class WebViewInternalStopFindingFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.stopFinding",
                             WEBVIEWINTERNAL_STOPFINDING);

  WebViewInternalStopFindingFunction();

 protected:
  virtual ~WebViewInternalStopFindingFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalStopFindingFunction);
};

class WebViewInternalGoFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.go", WEBVIEWINTERNAL_GO);

  WebViewInternalGoFunction();

 protected:
  virtual ~WebViewInternalGoFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalGoFunction);
};

class WebViewInternalReloadFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.reload", WEBVIEWINTERNAL_RELOAD);

  WebViewInternalReloadFunction();

 protected:
  virtual ~WebViewInternalReloadFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalReloadFunction);
};

class WebViewInternalSetPermissionFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.setPermission",
                             WEBVIEWINTERNAL_SETPERMISSION);

  WebViewInternalSetPermissionFunction();

 protected:
  virtual ~WebViewInternalSetPermissionFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalSetPermissionFunction);
};

class WebViewInternalOverrideUserAgentFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.overrideUserAgent",
                             WEBVIEWINTERNAL_OVERRIDEUSERAGENT);

  WebViewInternalOverrideUserAgentFunction();

 protected:
  virtual ~WebViewInternalOverrideUserAgentFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalOverrideUserAgentFunction);
};

class WebViewInternalStopFunction : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.stop", WEBVIEWINTERNAL_STOP);

  WebViewInternalStopFunction();

 protected:
  virtual ~WebViewInternalStopFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalStopFunction);
};

class WebViewInternalTerminateFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.terminate",
                             WEBVIEWINTERNAL_TERMINATE);

  WebViewInternalTerminateFunction();

 protected:
  virtual ~WebViewInternalTerminateFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalTerminateFunction);
};

class WebViewInternalClearDataFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webViewInternal.clearData",
                             WEBVIEWINTERNAL_CLEARDATA);

  WebViewInternalClearDataFunction();

 protected:
  virtual ~WebViewInternalClearDataFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  uint32 GetRemovalMask();
  void ClearDataDone();

  
  base::Time remove_since_;
  
  uint32 remove_mask_;
  
  bool bad_message_;

  DISALLOW_COPY_AND_ASSIGN(WebViewInternalClearDataFunction);
};

}  

#endif  
