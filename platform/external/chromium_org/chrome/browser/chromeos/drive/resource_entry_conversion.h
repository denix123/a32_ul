// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_ENTRY_CONVERSION_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_ENTRY_CONVERSION_H_

#include <string>

#include "base/files/file.h"

namespace google_apis {
class ChangeResource;
class FileResource;
}

namespace drive {

class ResourceEntry;

bool ConvertChangeResourceToResourceEntry(
    const google_apis::ChangeResource& input,
    ResourceEntry* out_entry,
    std::string* out_parent_resource_id);

bool ConvertFileResourceToResourceEntry(
    const google_apis::FileResource& input,
    ResourceEntry* out_entry,
    std::string* out_parent_resource_id);

void ConvertResourceEntryToFileInfo(const ResourceEntry& entry,
                                    base::File::Info* file_info);

}  

#endif  
