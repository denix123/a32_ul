// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_ROOT_DELETE_HELPER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_ROOT_DELETE_HELPER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/file_system_url.h"

class GURL;

namespace storage {
class FileSystemContext;
}

namespace sync_file_system {

class LocalFileSyncStatus;

class RootDeleteHelper {
 public:
  typedef base::Callback<void(base::File::Error)> FileStatusCallback;

  RootDeleteHelper(storage::FileSystemContext* file_system_context,
                   LocalFileSyncStatus* sync_status,
                   const storage::FileSystemURL& url,
                   const FileStatusCallback& callback);
  ~RootDeleteHelper();

  void Run();

 private:
  void DidDeleteFileSystem(base::File::Error error);
  void DidResetFileChangeTracker();
  void DidOpenFileSystem(const GURL& root,
                         const std::string& name,
                         base::File::Error error);

  scoped_refptr<storage::FileSystemContext> file_system_context_;
  const storage::FileSystemURL url_;
  FileStatusCallback callback_;

  
  LocalFileSyncStatus* sync_status_;

  base::WeakPtrFactory<RootDeleteHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RootDeleteHelper);
};

}  

#endif  
