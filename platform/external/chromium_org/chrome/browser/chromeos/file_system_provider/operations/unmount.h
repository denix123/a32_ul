// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_OPERATIONS_UNMOUNT_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_OPERATIONS_UNMOUNT_H_

#include "base/files/file.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/file_system_provider/operations/operation.h"
#include "storage/browser/fileapi/async_file_util.h"

namespace base {
class DictionaryValue;
}  

namespace extensions {
class EventRouter;
}  

namespace chromeos {
namespace file_system_provider {

class ProvidedFileSystemInfo;

namespace operations {

class Unmount : public Operation {
 public:
  Unmount(extensions::EventRouter* event_router,
          const ProvidedFileSystemInfo& file_system_info,
          const storage::AsyncFileUtil::StatusCallback& callback);
  virtual ~Unmount();

  
  virtual bool Execute(int request_id) OVERRIDE;
  virtual void OnSuccess(int request_id,
                         scoped_ptr<RequestValue> result,
                         bool has_more) OVERRIDE;
  virtual void OnError(int request_id,
                       scoped_ptr<RequestValue> result,
                       base::File::Error error) OVERRIDE;

 private:
  const storage::AsyncFileUtil::StatusCallback callback_;

  DISALLOW_COPY_AND_ASSIGN(Unmount);
};

}  
}  
}  

#endif  
