// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/synchronization/lock.h"
#include "breakpad/src/client/windows/common/ipc_protocol.h"
#include "breakpad/src/client/windows/handler/exception_handler.h"


namespace base {
class CommandLine;
}  

namespace crash_reporter {
class CrashReporterClient;
}

namespace breakpad {

class CrashKeysWin {
 public:
  CrashKeysWin();
  ~CrashKeysWin();

  
  
  
  
  
  
  
  
  
  
  google_breakpad::CustomClientInfo* GetCustomInfo(
        const std::wstring& exe_path,
        const std::wstring& type,
        const std::wstring& profile_type,
        base::CommandLine* cmd_line,
        crash_reporter::CrashReporterClient* crash_client);

  void SetCrashKeyValue(const std::wstring& key, const std::wstring& value);
  void ClearCrashKeyValue(const std::wstring& key);

  static CrashKeysWin* keeper() { return keeper_; }

 private:
  
  void SetPluginPath(const std::wstring& path);
  void SetBreakpadDumpPath(crash_reporter::CrashReporterClient* crash_client);

  
  std::vector<google_breakpad::CustomInfoEntry> custom_entries_;

  typedef std::map<std::wstring, google_breakpad::CustomInfoEntry*>
      DynamicEntriesMap;
  base::Lock lock_;
  
  size_t dynamic_keys_offset_;  
  
  
  DynamicEntriesMap dynamic_entries_;  

  
  static CrashKeysWin* keeper_;

  DISALLOW_COPY_AND_ASSIGN(CrashKeysWin);
};

}  
