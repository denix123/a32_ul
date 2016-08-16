// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_BREAKPAD_H_
#define CHROME_ELF_BREAKPAD_H_

#include <windows.h>

namespace google_breakpad {
class ExceptionHandler;
}

void InitializeCrashReporting();

int GenerateCrashDump(EXCEPTION_POINTERS* exinfo);

extern google_breakpad::ExceptionHandler* g_elf_breakpad;

#endif  
