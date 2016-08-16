// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SYSTEM_LOGS_DEBUG_LOG_WRITER_H_
#define CHROME_BROWSER_CHROMEOS_SYSTEM_LOGS_DEBUG_LOG_WRITER_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"

namespace chromeos {

class DebugLogWriter {
 public:
  
  
  
  typedef base::Callback<void(const base::FilePath& log_path, bool succeeded)>
      StoreLogsCallback;

  
  
  
  
  
  static void StoreLogs(const base::FilePath& fileshelf,
                        bool should_compress,
                        const StoreLogsCallback& callback);

  
  
  
  static void StoreCombinedLogs(const base::FilePath& fileshelf,
                                const std::string& sequence_token_name,
                                const StoreLogsCallback& callback);

 private:
  DebugLogWriter();
  DISALLOW_COPY_AND_ASSIGN(DebugLogWriter);
};

}  

#endif  
