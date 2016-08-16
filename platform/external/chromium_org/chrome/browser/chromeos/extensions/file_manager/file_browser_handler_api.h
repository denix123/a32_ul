// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_FILE_BROWSER_HANDLER_API_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_FILE_BROWSER_HANDLER_API_H_

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "chrome/browser/extensions/chrome_extension_function.h"

class Browser;
class FileBrowserHandlerInternalSelectFileFunction;

namespace file_manager {

namespace util {
struct EntryDefinition;
struct FileDefinition;
}

class FileSelector {
 public:
  virtual ~FileSelector() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void SelectFile(
      const base::FilePath& suggested_name,
      const std::vector<std::string>& allowed_extensions,
      Browser* browser,
      FileBrowserHandlerInternalSelectFileFunction* function) = 0;
};

class FileSelectorFactory {
 public:
  virtual ~FileSelectorFactory() {}

  
  
  virtual FileSelector* CreateFileSelector() const = 0;
};

}  


class FileBrowserHandlerInternalSelectFileFunction
    : public ChromeAsyncExtensionFunction {
 public:
  
  
  
  FileBrowserHandlerInternalSelectFileFunction();

  
  
  
  
  FileBrowserHandlerInternalSelectFileFunction(
      file_manager::FileSelectorFactory* file_selector_factory,
      bool enable_user_gesture_check);

  
  
  
  
  
  
  void OnFilePathSelected(bool success, const base::FilePath& full_path);

 protected:
  
  virtual ~FileBrowserHandlerInternalSelectFileFunction();

  
  
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void RespondEntryDefinition(
      const file_manager::util::EntryDefinition& entry_definition);

  
  
  
  
  
  
  
  
  
  void Respond(const file_manager::util::EntryDefinition& entry_definition,
               bool success);

  
  
  scoped_ptr<file_manager::FileSelectorFactory> file_selector_factory_;
  
  bool user_gesture_check_enabled_;

  
  
  std::vector<std::pair<base::FilePath, int> > permissions_to_grant_;

  DECLARE_EXTENSION_FUNCTION("fileBrowserHandlerInternal.selectFile",
                             FILEBROWSERHANDLERINTERNAL_SELECTFILE)
};

#endif  
