// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_FILE_STATUS_OBSERVER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_FILE_STATUS_OBSERVER_H_

#include "base/basictypes.h"
#include "chrome/browser/sync_file_system/sync_action.h"
#include "chrome/browser/sync_file_system/sync_direction.h"
#include "chrome/browser/sync_file_system/sync_file_status.h"

namespace storage {
class FileSystemURL;
}

namespace sync_file_system {

class FileStatusObserver {
 public:
  FileStatusObserver() {}
  virtual ~FileStatusObserver() {}

  virtual void OnFileStatusChanged(const storage::FileSystemURL& url,
                                   SyncFileStatus sync_status,
                                   SyncAction action_taken,
                                   SyncDirection direction) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(FileStatusObserver);
};

}  

#endif  