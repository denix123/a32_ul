// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_ANDROID_COMMON_DAEMON_H_
#define TOOLS_ANDROID_COMMON_DAEMON_H_

namespace base {
class CommandLine;
}

namespace tools {

bool HasHelpSwitch(const base::CommandLine& command_line);

bool HasNoSpawnDaemonSwitch(const base::CommandLine& command_line);

void ShowHelp(const char* program,
              const char* extra_title,
              const char* extra_descriptions);

void SpawnDaemon(int exit_status);

}  

#endif  

