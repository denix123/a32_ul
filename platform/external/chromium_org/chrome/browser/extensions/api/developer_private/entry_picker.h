// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_DEVELOPER_PRIVATE_ENTRY_PICKER_H_
#define CHROME_BROWSER_EXTENSIONS_API_DEVELOPER_PRIVATE_ENTRY_PICKER_H_

#include "extensions/browser/extension_function.h"
#include "ui/shell_dialogs/select_file_dialog.h"

namespace content {
class WebContents;
}

namespace extensions {

namespace api {

class EntryPickerClient {
 public:
  virtual void FileSelected(const base::FilePath& path) = 0;
  virtual void FileSelectionCanceled() = 0;
};

class EntryPicker : public ui::SelectFileDialog::Listener {
 public:
  EntryPicker(EntryPickerClient* client,
              content::WebContents* web_contents,
              ui::SelectFileDialog::Type picker_type,
              const base::FilePath& last_directory,
              const base::string16& select_title,
              const ui::SelectFileDialog::FileTypeInfo& info,
              int file_type_index);

  
  static void SkipPickerAndAlwaysSelectPathForTest(base::FilePath* path);
  static void SkipPickerAndAlwaysCancelForTest();
  static void StopSkippingPickerForTest();

 protected:
  virtual ~EntryPicker();

 private:
  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;

  virtual void FileSelectionCanceled(void* params) OVERRIDE;

  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;
  EntryPickerClient* client_;

  DISALLOW_COPY_AND_ASSIGN(EntryPicker);
};

}  

}  

#endif  
