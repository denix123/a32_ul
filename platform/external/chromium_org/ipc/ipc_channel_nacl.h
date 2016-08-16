// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_CHANNEL_NACL_H_
#define IPC_IPC_CHANNEL_NACL_H_

#include <deque>
#include <string>

#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/process/process.h"
#include "base/threading/simple_thread.h"
#include "ipc/ipc_channel.h"
#include "ipc/ipc_channel_reader.h"

namespace IPC {

struct MessageContents;

class ChannelNacl : public Channel,
                    public internal::ChannelReader {
 public:
  
  ChannelNacl(const IPC::ChannelHandle& channel_handle,
              Mode mode,
              Listener* listener);
  virtual ~ChannelNacl();

  
  virtual base::ProcessId GetPeerPID() const OVERRIDE;
  virtual base::ProcessId GetSelfPID() const OVERRIDE;
  virtual bool Connect() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual bool Send(Message* message) OVERRIDE;

  
  void DidRecvMsg(scoped_ptr<MessageContents> contents);
  void ReadDidFail();

 private:
  class ReaderThreadRunner;

  bool CreatePipe(const IPC::ChannelHandle& channel_handle);
  bool ProcessOutgoingMessages();
  void CallOnChannelConnected();

  
  virtual ReadState ReadData(char* buffer,
                             int buffer_len,
                             int* bytes_read) OVERRIDE;
  virtual bool WillDispatchInputMessage(Message* msg) OVERRIDE;
  virtual bool DidEmptyInputBuffers() OVERRIDE;
  virtual void HandleInternalMessage(const Message& msg) OVERRIDE;

  Mode mode_;
  bool waiting_connect_;

  
  int pipe_;

  
  
  
  
  std::string pipe_name_;

  
  
  
  
  
  
  
  scoped_ptr<ReaderThreadRunner> reader_thread_runner_;
  scoped_ptr<base::DelegateSimpleThread> reader_thread_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  std::deque<linked_ptr<std::vector<char> > > read_queue_;
  
  
  
  
  std::vector<int> input_fds_;

  
  
  std::deque<linked_ptr<Message> > output_queue_;

  base::WeakPtrFactory<ChannelNacl> weak_ptr_factory_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ChannelNacl);
};

}  

#endif  
