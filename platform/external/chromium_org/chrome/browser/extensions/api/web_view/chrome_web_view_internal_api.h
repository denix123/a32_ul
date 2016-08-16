// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_WEB_VIEW_CHROME_WEB_VIEW_INTERNAL_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_WEB_VIEW_CHROME_WEB_VIEW_INTERNAL_API_H_

#include "extensions/browser/api/web_view/web_view_internal_api.h"
#include "extensions/browser/extension_function.h"
#include "extensions/browser/guest_view/web_view/web_view_guest.h"

namespace extensions {

class ChromeWebViewInternalContextMenusCreateFunction
    : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("chromeWebViewInternal.contextMenusCreate",
                             WEBVIEWINTERNAL_CONTEXTMENUSCREATE);
  ChromeWebViewInternalContextMenusCreateFunction() {}

 protected:
  virtual ~ChromeWebViewInternalContextMenusCreateFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewInternalContextMenusCreateFunction);
};

class ChromeWebViewInternalContextMenusUpdateFunction
    : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("chromeWebViewInternal.contextMenusUpdate",
                             WEBVIEWINTERNAL_CONTEXTMENUSUPDATE);
  ChromeWebViewInternalContextMenusUpdateFunction() {}

 protected:
  virtual ~ChromeWebViewInternalContextMenusUpdateFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewInternalContextMenusUpdateFunction);
};

class ChromeWebViewInternalContextMenusRemoveFunction
    : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("chromeWebViewInternal.contextMenusRemove",
                             WEBVIEWINTERNAL_CONTEXTMENUSREMOVE);
  ChromeWebViewInternalContextMenusRemoveFunction() {}

 protected:
  virtual ~ChromeWebViewInternalContextMenusRemoveFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewInternalContextMenusRemoveFunction);
};

class ChromeWebViewInternalContextMenusRemoveAllFunction
    : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("chromeWebViewInternal.contextMenusRemoveAll",
                             WEBVIEWINTERNAL_CONTEXTMENUSREMOVEALL);
  ChromeWebViewInternalContextMenusRemoveAllFunction() {}

 protected:
  virtual ~ChromeWebViewInternalContextMenusRemoveAllFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewInternalContextMenusRemoveAllFunction);
};

class ChromeWebViewInternalShowContextMenuFunction
    : public WebViewInternalExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("chromeWebViewInternal.showContextMenu",
                             WEBVIEWINTERNAL_SHOWCONTEXTMENU);

  ChromeWebViewInternalShowContextMenuFunction();

 protected:
  virtual ~ChromeWebViewInternalShowContextMenuFunction();

 private:
  
  virtual bool RunAsyncSafe(WebViewGuest* guest) OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(ChromeWebViewInternalShowContextMenuFunction);
};

}  

#endif  
