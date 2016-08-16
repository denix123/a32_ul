// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILE_BROWSER_HANDLERS_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_FILE_BROWSER_HANDLERS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "chrome/browser/chromeos/file_manager/file_tasks.h"

class FileBrowserHandler;
class GURL;
class Profile;

namespace extensions {
class Extension;
}

namespace storage {
class FileSystemURL;
}

namespace file_manager {
namespace file_browser_handlers {

typedef std::vector<const FileBrowserHandler*> FileBrowserHandlerList;

FileBrowserHandlerList FindFileBrowserHandlers(
    Profile* profile,
    const std::vector<GURL>& file_list);

bool ExecuteFileBrowserHandler(
    Profile* profile,
    const extensions::Extension* extension,
    const std::string& action_id,
    const std::vector<storage::FileSystemURL>& file_urls,
    const file_tasks::FileTaskFinishedCallback& done);

}  
}  

#endif  
