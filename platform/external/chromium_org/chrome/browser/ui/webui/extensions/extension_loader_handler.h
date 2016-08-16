// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_LOADER_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_EXTENSIONS_EXTENSION_LOADER_HANDLER_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/values.h"
#include "chrome/browser/extensions/extension_error_reporter.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace content {
class WebUIDataSource;
}

class Profile;

namespace extensions {

class Extension;

class ExtensionLoaderHandler : public content::WebUIMessageHandler,
                               public ExtensionErrorReporter::Observer,
                               public content::WebContentsObserver {
 public:
  explicit ExtensionLoaderHandler(Profile* profile);
  virtual ~ExtensionLoaderHandler();

  
  void GetLocalizedValues(content::WebUIDataSource* source);

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  class FileHelper;

  
  void HandleLoadUnpacked(const base::ListValue* args);

  
  void HandleRetry(const base::ListValue* args);

  
  void HandleIgnoreFailure(const base::ListValue* args);

  
  void HandleDisplayFailures(const base::ListValue* args);

  
  void LoadUnpackedExtensionImpl(const base::FilePath& file_path);

  
  virtual void OnLoadFailure(content::BrowserContext* browser_context,
                             const base::FilePath& file_path,
                             const std::string& error) OVERRIDE;

  
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;

  
  
  
  void AddFailure(const base::FilePath& file_path,
                  const std::string& error,
                  size_t line_number,
                  const std::string& manifest);

  
  void NotifyFrontendOfFailure();

  
  Profile* profile_;

  
  scoped_ptr<FileHelper> file_helper_;

  
  
  base::ListValue failures_;

  
  std::vector<base::FilePath> failed_paths_;

  ScopedObserver<ExtensionErrorReporter, ExtensionErrorReporter::Observer>
      extension_error_reporter_observer_;

  
  
  
  bool ui_ready_;

  
  base::WeakPtrFactory<ExtensionLoaderHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionLoaderHandler);
};

}  

#endif  
