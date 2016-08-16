// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_APP_SHIM_UNIX_DOMAIN_SOCKET_ACCEPTOR_H_
#define CHROME_BROWSER_APPS_APP_SHIM_UNIX_DOMAIN_SOCKET_ACCEPTOR_H_

#include "base/files/file_path.h"
#include "base/message_loop/message_loop.h"
#include "ipc/ipc_channel_handle.h"

namespace apps {

class UnixDomainSocketAcceptor : public base::MessageLoopForIO::Watcher {
 public:
  class Delegate {
   public:
    
    
    
    virtual void OnClientConnected(const IPC::ChannelHandle& handle) = 0;

    
    virtual void OnListenError() = 0;
  };

  UnixDomainSocketAcceptor(const base::FilePath& path, Delegate* delegate);

  virtual ~UnixDomainSocketAcceptor();

  
  bool Listen();

  
  void Close();

 private:
  bool CreateSocket();
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

  base::MessageLoopForIO::FileDescriptorWatcher
      server_listen_connection_watcher_;
  base::FilePath path_;
  Delegate* delegate_;
  int listen_fd_;

  DISALLOW_COPY_AND_ASSIGN(UnixDomainSocketAcceptor);
};

}  

#endif  
