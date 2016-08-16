// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_UTIL_H_

#include <vector>

#include "base/callback_forward.h"

class GURL;
class Profile;

namespace base {
class FilePath;
}

namespace content {
class RenderViewHost;
}

namespace drive {
class EventLogger;
}

namespace extensions {
namespace api {
namespace file_manager_private {
struct VolumeMetadata;
}
}
}

namespace ui {
struct SelectedFileInfo;
}

namespace file_manager {

struct VolumeInfo;

namespace util {

void VolumeInfoToVolumeMetadata(
    Profile* profile,
    const VolumeInfo& volume_info,
    extensions::api::file_manager_private::VolumeMetadata* volume_metadata);

base::FilePath GetLocalPathFromURL(content::RenderViewHost* render_view_host,
                                   Profile* profile,
                                   const GURL& url);

typedef base::Callback<void(const std::vector<ui::SelectedFileInfo>&)>
    GetSelectedFileInfoCallback;

enum GetSelectedFileInfoLocalPathOption {
  NO_LOCAL_PATH_RESOLUTION,
  NEED_LOCAL_PATH_FOR_OPENING,
  NEED_LOCAL_PATH_FOR_SAVING,
};

void GetSelectedFileInfo(content::RenderViewHost* render_view_host,
                         Profile* profile,
                         const std::vector<GURL>& file_urls,
                         GetSelectedFileInfoLocalPathOption local_path_option,
                         GetSelectedFileInfoCallback callback);

void SetupProfileFileAccessPermissions(int render_view_process_id,
                                       Profile* profile);

drive::EventLogger* GetLogger(Profile* profile);

}  
}  

#endif  
