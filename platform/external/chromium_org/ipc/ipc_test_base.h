// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_TEST_BASE_H_
#define IPC_IPC_TEST_BASE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/process.h"
#include "base/test/multiprocess_test.h"
#include "ipc/ipc_channel.h"
#include "ipc/ipc_channel_factory.h"
#include "ipc/ipc_channel_proxy.h"
#include "ipc/ipc_multiprocess_test.h"

namespace base {
class MessageLoop;
}

class IPCTestBase : public base::MultiProcessTest {
 public:
  
  
  
  static std::string GetChannelName(const std::string& test_client_name);

 protected:
  IPCTestBase();
  virtual ~IPCTestBase();

  virtual void TearDown() OVERRIDE;

  
  
  void Init(const std::string& test_client_name);
  
  
  
  
  void InitWithCustomMessageLoop(const std::string& test_client_name,
                                 scoped_ptr<base::MessageLoop> message_loop);

  
  
  
  
  void CreateChannel(IPC::Listener* listener);
  bool ConnectChannel();
  void DestroyChannel();

  
  
  scoped_ptr<IPC::Channel> ReleaseChannel();
  void SetChannel(scoped_ptr<IPC::Channel> channel);

  
  
  void CreateChannelFromChannelHandle(const IPC::ChannelHandle& channel_handle,
                                      IPC::Listener* listener);

  
  
  
  
  void CreateChannelProxy(
      IPC::Listener* listener,
      const scoped_refptr<base::SingleThreadTaskRunner>& ipc_task_runner);
  void DestroyChannelProxy();

  
  
  bool StartClient();

#if defined(OS_POSIX)
  
  bool StartClientWithFD(int ipcfd);
#endif

  
  
  
  
  bool WaitForClientShutdown();

  IPC::ChannelHandle GetTestChannelHandle();

  
  
  IPC::Sender* sender() {
    return channel_.get() ? static_cast<IPC::Sender*>(channel_.get()) :
                            static_cast<IPC::Sender*>(channel_proxy_.get());
  }

  IPC::Channel* channel() { return channel_.get(); }
  IPC::ChannelProxy* channel_proxy() { return channel_proxy_.get(); }

  const base::ProcessHandle& client_process() const { return client_process_; }
  scoped_refptr<base::TaskRunner> task_runner();

  virtual scoped_ptr<IPC::ChannelFactory> CreateChannelFactory(
      const IPC::ChannelHandle& handle, base::TaskRunner* runner);

  virtual bool DidStartClient();

 private:
  std::string GetTestMainName() const;

  std::string test_client_name_;
  scoped_ptr<base::MessageLoop> message_loop_;

  scoped_ptr<IPC::Channel> channel_;
  scoped_ptr<IPC::ChannelProxy> channel_proxy_;

  base::ProcessHandle client_process_;

  DISALLOW_COPY_AND_ASSIGN(IPCTestBase);
};

#define MULTIPROCESS_IPC_TEST_CLIENT_MAIN(test_client_name) \
    MULTIPROCESS_IPC_TEST_MAIN(test_client_name ## TestClientMain)

#endif  
