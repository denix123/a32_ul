// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_CYGPROFILE_CYGPROFILE_H_
#define TOOLS_CYGPROFILE_CYGPROFILE_H_

#include <vector>

#include <sys/time.h>
#include <sys/types.h>

#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "build/build_config.h"

#if !defined(OS_ANDROID)
// platforms that use fork(), cygprofile.cc should be written in a way that
#error This is only supported on Android.
#endif

namespace cygprofile {

class Thread;

struct LogEntry {
  LogEntry(const void* address);

  const timespec time;
  const pid_t pid;
  const pid_t tid;
  const void* const address;
};

class ThreadLog {
 public:
  
  typedef base::Callback<void (std::vector<LogEntry>*)> FlushCallback;

  ThreadLog();

  
  ThreadLog(const FlushCallback& flush_callback);

  ~ThreadLog();

  
  void AddEntry(void* address);

  
  void TakeEntries(std::vector<LogEntry>* output);

  
  
  void Flush(std::vector<LogEntry>* entries) const;

 private:
  
  
  void FlushInternal(std::vector<LogEntry>* entries) const;

  
  
  
  const pid_t tid_;

  
  bool in_use_;

  
  const FlushCallback flush_callback_;

  
  
  std::hash_set<void*> called_functions_;

  
  
  
  base::Lock lock_;

  std::vector<LogEntry> entries_;

  DISALLOW_COPY_AND_ASSIGN(ThreadLog);
};

class ThreadLogsManager {
 public:
  ThreadLogsManager();

  
  
  
  ThreadLogsManager(const base::Closure& wait_callback,
                    const base::Closure& notify_callback);

  ~ThreadLogsManager();

  
  void AddLog(scoped_ptr<ThreadLog> new_log);

 private:
  void StartInternalFlushThread_Locked();

  
  void FlushAllLogsOnFlushThread();

  
  const base::Closure wait_callback_;
  
  
  const base::Closure notify_callback_;

  
  base::Lock lock_;
  scoped_ptr<Thread> flush_thread_;
  std::vector<ThreadLog*> logs_;

  DISALLOW_COPY_AND_ASSIGN(ThreadLogsManager);
};

}  

#endif  
