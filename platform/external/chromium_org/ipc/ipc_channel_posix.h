// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_CHANNEL_POSIX_H_
#define IPC_IPC_CHANNEL_POSIX_H_

#include "ipc/ipc_channel.h"

#include <sys/socket.h>  

#include <queue>
#include <set>
#include <string>
#include <vector>

#include "base/message_loop/message_loop.h"
#include "base/process/process.h"
#include "ipc/file_descriptor_set_posix.h"
#include "ipc/ipc_channel_reader.h"

#if !defined(OS_MACOSX)
#define IPC_USES_READWRITE 1
#endif

namespace IPC {

class IPC_EXPORT ChannelPosix : public Channel,
                                public internal::ChannelReader,
                                public base::MessageLoopForIO::Watcher {
 public:
  ChannelPosix(const IPC::ChannelHandle& channel_handle, Mode mode,
               Listener* listener);
  virtual ~ChannelPosix();

  
  virtual bool Connect() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual bool Send(Message* message) OVERRIDE;
  virtual base::ProcessId GetPeerPID() const OVERRIDE;
  virtual base::ProcessId GetSelfPID() const OVERRIDE;
  virtual int GetClientFileDescriptor() const OVERRIDE;
  virtual int TakeClientFileDescriptor() OVERRIDE;

  
  bool AcceptsConnections() const;

  
  
  bool HasAcceptedConnection() const;

  
  
  void ResetToAcceptingConnectionState();

  
  
  bool GetPeerEuid(uid_t* peer_euid) const;

  void CloseClientFileDescriptor();

  static bool IsNamedServerInitialized(const std::string& channel_id);
#if defined(OS_LINUX)
  static void SetGlobalPid(int pid);
#endif  

 private:
  bool CreatePipe(const IPC::ChannelHandle& channel_handle);

  bool ProcessOutgoingMessages();

  bool AcceptConnection();
  void ClosePipeOnError();
  int GetHelloMessageProcId() const;
  void QueueHelloMessage();
  void CloseFileDescriptors(Message* msg);
  void QueueCloseFDMessage(int fd, int hops);

  
  virtual ReadState ReadData(char* buffer,
                             int buffer_len,
                             int* bytes_read) OVERRIDE;
  virtual bool WillDispatchInputMessage(Message* msg) OVERRIDE;
  virtual bool DidEmptyInputBuffers() OVERRIDE;
  virtual void HandleInternalMessage(const Message& msg) OVERRIDE;

#if defined(IPC_USES_READWRITE)
  
  
  
  
  bool ReadFileDescriptorsFromFDPipe();
#endif

  
  
  
  
  
  bool ExtractFileDescriptorsFromMsghdr(msghdr* msg);

  
  
  void ClearInputFDs();

  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

  Mode mode_;

  base::ProcessId peer_pid_;

  
  
  base::MessageLoopForIO::FileDescriptorWatcher
  server_listen_connection_watcher_;
  base::MessageLoopForIO::FileDescriptorWatcher read_watcher_;
  base::MessageLoopForIO::FileDescriptorWatcher write_watcher_;

  
  bool is_blocked_on_write_;
  bool waiting_connect_;

  
  
  size_t message_send_bytes_written_;

  
  
  int server_listen_pipe_;

  
  int pipe_;

  
  
  int client_pipe_;
  mutable base::Lock client_pipe_lock_;  

#if defined(IPC_USES_READWRITE)
  
  int fd_pipe_;
  int remote_fd_pipe_;
#endif

  
  
  std::string pipe_name_;

  
  std::queue<Message*> output_queue_;

  
  
  static const size_t kMaxReadFDs =
      (Channel::kReadBufferSize / sizeof(IPC::Message::Header)) *
      FileDescriptorSet::kMaxDescriptorsPerMessage;

  
  
#if defined(OS_MACOSX)
  static const size_t kMaxReadFDBuffer = 1024;
#else
  static const size_t kMaxReadFDBuffer = CMSG_SPACE(sizeof(int) * kMaxReadFDs);
#endif

  
  
  
  
  char input_cmsg_buf_[kMaxReadFDBuffer];

  
  
  
  
  
  
  std::vector<int> input_fds_;

#if defined(OS_MACOSX)
  
  
  
  std::set<int> fds_to_close_;
#endif

  
  bool must_unlink_;

#if defined(OS_LINUX)
  
  static int global_pid_;
#endif  

  DISALLOW_IMPLICIT_CONSTRUCTORS(ChannelPosix);
};

}  

#endif  
