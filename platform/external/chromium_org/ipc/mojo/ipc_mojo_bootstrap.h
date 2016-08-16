// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_MOJO_IPC_MOJO_BOOTSTRAP_H_
#define IPC_MOJO_IPC_MOJO_BOOTSTRAP_H_

#include "base/memory/scoped_ptr.h"
#include "base/process/process_handle.h"
#include "ipc/ipc_channel.h"
#include "ipc/ipc_listener.h"
#include "mojo/embedder/scoped_platform_handle.h"

namespace IPC {

class IPC_MOJO_EXPORT MojoBootstrap : public Listener {
 public:
  class Delegate {
   public:
    virtual void OnPipeAvailable(
        mojo::embedder::ScopedPlatformHandle handle) = 0;
    virtual void OnBootstrapError() = 0;
  };

  
  
  
  static scoped_ptr<MojoBootstrap> Create(ChannelHandle handle,
                                          Channel::Mode mode,
                                          Delegate* delegate);

  MojoBootstrap();
  virtual ~MojoBootstrap();

  
  bool Connect();

  
  virtual void OnClientLaunched(base::ProcessHandle process) = 0;

#if defined(OS_POSIX) && !defined(OS_NACL)
  int GetClientFileDescriptor() const;
  int TakeClientFileDescriptor();
#endif  

 protected:
  enum State { STATE_INITIALIZED, STATE_WAITING_ACK, STATE_READY };

  Delegate* delegate() const { return delegate_; }
  bool Send(Message* message);

  State state() const { return state_; }
  void set_state(State state) { state_ = state; }

 private:
  void Init(scoped_ptr<Channel> channel, Delegate* delegate);

  
  virtual void OnBadMessageReceived(const Message& message) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;

  scoped_ptr<Channel> channel_;
  Delegate* delegate_;
  State state_;

  DISALLOW_COPY_AND_ASSIGN(MojoBootstrap);
};

}  

#endif  
