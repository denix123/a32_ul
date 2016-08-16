// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_URL_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_URL_UTIL_H_

#include <string>

#include "base/strings/string16.h"
#include "ui/shell_dialogs/select_file_dialog.h"
#include "url/gurl.h"

namespace file_manager {
namespace util {

GURL GetFileManagerMainPageUrl();

GURL GetFileManagerMainPageUrlWithParams(
    ui::SelectFileDialog::Type type,
    const base::string16& title,
    const GURL& current_directory_url,
    const GURL& selection_url,
    const std::string& target_name,
    const ui::SelectFileDialog::FileTypeInfo* file_types,
    int file_type_index,
    const base::FilePath::StringType& default_extension);

}  
}  

#endif  