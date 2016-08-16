// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_ANDROID_FORWARDER2_FORWARDER_H_
#define TOOLS_ANDROID_FORWARDER2_FORWARDER_H_

#include <sys/select.h>

#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"

namespace forwarder2 {

class Socket;

class Forwarder {
 public:
  Forwarder(scoped_ptr<Socket> socket1, scoped_ptr<Socket> socket2);

  ~Forwarder();

  void RegisterFDs(fd_set* read_fds, fd_set* write_fds, int* max_fd);

  void ProcessEvents(const fd_set& read_fds, const fd_set& write_fds);

  bool IsClosed() const;

  void Shutdown();

 private:
  class BufferedCopier;

  base::ThreadChecker thread_checker_;
  const scoped_ptr<Socket> socket1_;
  const scoped_ptr<Socket> socket2_;
  
  const scoped_ptr<BufferedCopier> buffer1_;
  
  const scoped_ptr<BufferedCopier> buffer2_;
};

}  

#endif  
