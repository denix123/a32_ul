// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_SYNCABLE_FILE_SYSTEM_UTIL_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_SYNCABLE_FILE_SYSTEM_UTIL_H_

#include <string>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace storage {
class FileSystemContext;
class FileSystemURL;
}

namespace tracked_objects {
class Location;
}

namespace sync_file_system {

void RegisterSyncableFileSystem();

void RevokeSyncableFileSystem();

GURL GetSyncableFileSystemRootURI(const GURL& origin);

storage::FileSystemURL CreateSyncableFileSystemURL(const GURL& origin,
                                                   const base::FilePath& path);

storage::FileSystemURL CreateSyncableFileSystemURLForSync(
    storage::FileSystemContext* file_system_context,
    const storage::FileSystemURL& syncable_url);

bool SerializeSyncableFileSystemURL(const storage::FileSystemURL& url,
                                    std::string* serialized_url);

bool DeserializeSyncableFileSystemURL(const std::string& serialized_url,
                                      storage::FileSystemURL* url);

base::FilePath GetSyncFileSystemDir(const base::FilePath& profile_base_dir);

void RunSoon(const tracked_objects::Location& from_here,
             const base::Closure& callback);

base::Closure NoopClosure();

}  

#endif  
