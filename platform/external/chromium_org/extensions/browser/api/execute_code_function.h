// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_EXECUTE_CODE_FUNCTION_H_
#define EXTENSIONS_BROWSER_API_EXECUTE_CODE_FUNCTION_H_

#include "extensions/browser/extension_function.h"
#include "extensions/browser/script_executor.h"
#include "extensions/common/api/extension_types.h"

namespace extensions {

class ExecuteCodeFunction : public AsyncExtensionFunction {
 public:
  ExecuteCodeFunction();

 protected:
  virtual ~ExecuteCodeFunction();

  
  virtual bool HasPermission() OVERRIDE;
  virtual bool RunAsync() OVERRIDE;

  
  virtual bool Init() = 0;
  virtual bool ShouldInsertCSS() const = 0;
  virtual bool CanExecuteScriptOnPage() = 0;
  virtual ScriptExecutor* GetScriptExecutor() = 0;
  virtual bool IsWebView() const = 0;
  virtual const GURL& GetWebViewSrc() const = 0;
  virtual void OnExecuteCodeFinished(const std::string& error,
                                     const GURL& on_url,
                                     const base::ListValue& result);

  
  scoped_ptr<core_api::extension_types::InjectDetails> details_;

 private:
  
  
  void DidLoadFile(bool success, const std::string& data);

  
  
  void GetFileURLAndLocalizeCSS(ScriptExecutor::ScriptType script_type,
                                const std::string& data,
                                const std::string& extension_id,
                                const base::FilePath& extension_path,
                                const std::string& extension_default_locale);

  
  void DidLoadAndLocalizeFile(bool success, const std::string& data);

  
  
  bool Execute(const std::string& code_string);

  
  
  ExtensionResource resource_;

  
  GURL file_url_;
};

}  

#endif  
