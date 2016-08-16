// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_ZYGOTE_ZYGOTE_H_
#define CONTENT_ZYGOTE_ZYGOTE_H_

#include <stddef.h>

#include <string>

#include "base/containers/small_map.h"
#include "base/files/scoped_file.h"
#include "base/memory/scoped_vector.h"
#include "base/posix/global_descriptors.h"
#include "base/process/kill.h"
#include "base/process/process.h"

class Pickle;
class PickleIterator;

namespace content {

class ZygoteForkDelegate;

class Zygote {
 public:
  Zygote(int sandbox_flags, ScopedVector<ZygoteForkDelegate> helpers,
         const std::vector<base::ProcessHandle>& extra_children,
         const std::vector<int>& extra_fds);
  ~Zygote();

  bool ProcessRequests();

 private:
  struct ZygoteProcessInfo {
    
    base::ProcessHandle internal_pid;
    
    ZygoteForkDelegate* started_from_helper;
  };
  typedef base::SmallMap< std::map<base::ProcessHandle, ZygoteProcessInfo> >
      ZygoteProcessMap;

  
  
  
  bool GetProcessInfo(base::ProcessHandle pid,
                      ZygoteProcessInfo* process_info);

  
  bool UsingSUIDSandbox() const;

  
  

  
  
  bool HandleRequestFromBrowser(int fd);

  void HandleReapRequest(int fd, const Pickle& pickle, PickleIterator iter);

  
  
  
  
  bool GetTerminationStatus(base::ProcessHandle real_pid, bool known_dead,
                            base::TerminationStatus* status,
                            int* exit_code);

  void HandleGetTerminationStatus(int fd,
                                  const Pickle& pickle,
                                  PickleIterator iter);

  
  
  
  
  
  
  
  
  int ForkWithRealPid(const std::string& process_type,
                      const base::GlobalDescriptors::Mapping& fd_mapping,
                      const std::string& channel_id,
                      base::ScopedFD pid_oracle,
                      std::string* uma_name,
                      int* uma_sample,
                      int* uma_boundary_value);

  
  
  
  base::ProcessId ReadArgsAndFork(const Pickle& pickle,
                                  PickleIterator iter,
                                  ScopedVector<base::ScopedFD> fds,
                                  std::string* uma_name,
                                  int* uma_sample,
                                  int* uma_boundary_value);

  
  
  
  
  bool HandleForkRequest(int fd,
                         const Pickle& pickle,
                         PickleIterator iter,
                         ScopedVector<base::ScopedFD> fds);

  bool HandleGetSandboxStatus(int fd,
                              const Pickle& pickle,
                              PickleIterator iter);

  
  
  
  
  ZygoteProcessMap process_info_map_;

  const int sandbox_flags_;
  ScopedVector<ZygoteForkDelegate> helpers_;

  
  size_t initial_uma_index_;

  
  
  
  
  
  std::vector<base::ProcessHandle> extra_children_;

  
  
  std::vector<int> extra_fds_;
};

}  

#endif  
