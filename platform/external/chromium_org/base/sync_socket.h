// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_SYNC_SOCKET_H_
#define BASE_SYNC_SOCKET_H_


#include "base/basictypes.h"
#if defined(OS_WIN)
#include <windows.h>
#endif
#include <sys/types.h>

#include "base/base_export.h"
#include "base/compiler_specific.h"
#include "base/process/process_handle.h"
#include "base/synchronization/waitable_event.h"
#include "base/time/time.h"

#if defined(OS_POSIX)
#include "base/file_descriptor_posix.h"
#endif

namespace base {

class BASE_EXPORT SyncSocket {
 public:
#if defined(OS_WIN)
  typedef HANDLE Handle;
  typedef Handle TransitDescriptor;
#else
  typedef int Handle;
  typedef FileDescriptor TransitDescriptor;
#endif
  static const Handle kInvalidHandle;

  SyncSocket();

  
  explicit SyncSocket(Handle handle) : handle_(handle)  {}
  virtual ~SyncSocket();

  
  
  
  static bool CreatePair(SyncSocket* socket_a, SyncSocket* socket_b);

  
  static Handle UnwrapHandle(const TransitDescriptor& descriptor);

  
  
  
  bool PrepareTransitDescriptor(ProcessHandle peer_process_handle,
                                TransitDescriptor* descriptor);

  
  virtual bool Close();

  
  
  
  
  
  
  virtual size_t Send(const void* buffer, size_t length);

  
  
  
  
  virtual size_t Receive(void* buffer, size_t length);

  
  
  
  virtual size_t ReceiveWithTimeout(void* buffer,
                                    size_t length,
                                    TimeDelta timeout);

  
  
  
  
  size_t Peek();

  
  
  Handle handle() const { return handle_; }

 protected:
  Handle handle_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SyncSocket);
};

class BASE_EXPORT CancelableSyncSocket : public SyncSocket {
 public:
  CancelableSyncSocket();
  explicit CancelableSyncSocket(Handle handle);
  virtual ~CancelableSyncSocket() {}

  
  
  static bool CreatePair(CancelableSyncSocket* socket_a,
                         CancelableSyncSocket* socket_b);

  
  
  bool Shutdown();

#if defined(OS_WIN)
  
  
  
  
  
  
  virtual bool Close() OVERRIDE;
  virtual size_t Receive(void* buffer, size_t length) OVERRIDE;
  virtual size_t ReceiveWithTimeout(void* buffer,
                                    size_t length,
                                    TimeDelta timeout) OVERRIDE;
#endif

  
  
  
  
  
  virtual size_t Send(const void* buffer, size_t length) OVERRIDE;

 private:
#if defined(OS_WIN)
  WaitableEvent shutdown_event_;
  WaitableEvent file_operation_;
#endif
  DISALLOW_COPY_AND_ASSIGN(CancelableSyncSocket);
};

#if defined(OS_WIN) && !defined(COMPONENT_BUILD)
__declspec(selectany)
    const SyncSocket::Handle SyncSocket::kInvalidHandle = INVALID_HANDLE_VALUE;
#endif

}  

#endif  
