// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_APP_CLIENT_UTIL_H_
#define CHROME_APP_CLIENT_UTIL_H_

#include <windows.h>

#include <string>
#include "base/strings/string16.h"

namespace sandbox {
  struct SandboxInterfaceInfo;
}

base::string16 GetExecutablePath();

base::string16 GetCurrentModuleVersion();

class MainDllLoader {
 public:
  MainDllLoader();
  virtual ~MainDllLoader();

  
  
  
  
  int Launch(HINSTANCE instance);

  
  
  void RelaunchChromeBrowserWithNewCommandLineIfNeeded();

 protected:
  
  
  
  virtual void OnBeforeLaunch(const base::string16& dll_path) = 0;

  
  
  
  virtual int OnBeforeExit(int return_code, const base::string16& dll_path) = 0;

 private:
  HMODULE Load(base::string16* version, base::string16* out_file);

 private:
  HMODULE dll_;
  std::string process_type_;
  const bool metro_mode_;
};

MainDllLoader* MakeMainDllLoader();

#endif  
