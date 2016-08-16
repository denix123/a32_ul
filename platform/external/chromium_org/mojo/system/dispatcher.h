// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_DISPATCHER_H_
#define MOJO_SYSTEM_DISPATCHER_H_

#include <stddef.h>
#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "mojo/embedder/platform_handle.h"
#include "mojo/embedder/platform_handle_vector.h"
#include "mojo/public/c/system/buffer.h"
#include "mojo/public/c/system/data_pipe.h"
#include "mojo/public/c/system/message_pipe.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/handle_signals_state.h"
#include "mojo/system/memory.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {

namespace embedder {
class PlatformSharedBufferMapping;
}

namespace system {

class Channel;
class Core;
class Dispatcher;
class DispatcherTransport;
class HandleTable;
class LocalMessagePipeEndpoint;
class ProxyMessagePipeEndpoint;
class TransportData;
class Waiter;

typedef std::vector<scoped_refptr<Dispatcher>> DispatcherVector;

namespace test {

MOJO_SYSTEM_IMPL_EXPORT DispatcherTransport
    DispatcherTryStartTransport(Dispatcher* dispatcher);

}  

class MOJO_SYSTEM_IMPL_EXPORT Dispatcher
    : public base::RefCountedThreadSafe<Dispatcher> {
 public:
  enum Type {
    kTypeUnknown = 0,
    kTypeMessagePipe,
    kTypeDataPipeProducer,
    kTypeDataPipeConsumer,
    kTypeSharedBuffer,

    
    kTypePlatformHandle = -1
  };
  virtual Type GetType() const = 0;

  
  
  
  
  
  
  
  MojoResult Close();

  
  // written; not that |this| must not be in |transports|. On success, all the
  
  
  MojoResult WriteMessage(UserPointer<const void> bytes,
                          uint32_t num_bytes,
                          std::vector<DispatcherTransport>* transports,
                          MojoWriteMessageFlags flags);
  
  
  
  MojoResult ReadMessage(UserPointer<void> bytes,
                         UserPointer<uint32_t> num_bytes,
                         DispatcherVector* dispatchers,
                         uint32_t* num_dispatchers,
                         MojoReadMessageFlags flags);
  MojoResult WriteData(UserPointer<const void> elements,
                       UserPointer<uint32_t> elements_num_bytes,
                       MojoWriteDataFlags flags);
  MojoResult BeginWriteData(UserPointer<void*> buffer,
                            UserPointer<uint32_t> buffer_num_bytes,
                            MojoWriteDataFlags flags);
  MojoResult EndWriteData(uint32_t num_bytes_written);
  MojoResult ReadData(UserPointer<void> elements,
                      UserPointer<uint32_t> num_bytes,
                      MojoReadDataFlags flags);
  MojoResult BeginReadData(UserPointer<const void*> buffer,
                           UserPointer<uint32_t> buffer_num_bytes,
                           MojoReadDataFlags flags);
  MojoResult EndReadData(uint32_t num_bytes_read);
  
  
  
  MojoResult DuplicateBufferHandle(
      UserPointer<const MojoDuplicateBufferHandleOptions> options,
      scoped_refptr<Dispatcher>* new_dispatcher);
  MojoResult MapBuffer(
      uint64_t offset,
      uint64_t num_bytes,
      MojoMapBufferFlags flags,
      scoped_ptr<embedder::PlatformSharedBufferMapping>* mapping);

  
  
  
  
  HandleSignalsState GetHandleSignalsState() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  MojoResult AddWaiter(Waiter* waiter,
                       MojoHandleSignals signals,
                       uint32_t context,
                       HandleSignalsState* signals_state);
  
  
  
  
  void RemoveWaiter(Waiter* waiter, HandleSignalsState* signals_state);

  
  
  
  
  
  
  
  
  class HandleTableAccess {
   private:
    friend class Core;
    friend class HandleTable;
    
    friend DispatcherTransport test::DispatcherTryStartTransport(Dispatcher*);

    
    
    
    static DispatcherTransport TryStartTransport(Dispatcher* dispatcher);
  };

  
  
  
  
  
  
  
  
  
  
  class TransportDataAccess {
   private:
    friend class TransportData;

    
    
    
    
    static void StartSerialize(Dispatcher* dispatcher,
                               Channel* channel,
                               size_t* max_size,
                               size_t* max_platform_handles);
    static bool EndSerializeAndClose(
        Dispatcher* dispatcher,
        Channel* channel,
        void* destination,
        size_t* actual_size,
        embedder::PlatformHandleVector* platform_handles);

    
    
    
    static scoped_refptr<Dispatcher> Deserialize(
        Channel* channel,
        int32_t type,
        const void* source,
        size_t size,
        embedder::PlatformHandleVector* platform_handles);
  };

 protected:
  friend class base::RefCountedThreadSafe<Dispatcher>;

  Dispatcher();
  virtual ~Dispatcher();

  
  
  
  virtual void CancelAllWaitersNoLock();
  virtual void CloseImplNoLock();
  virtual scoped_refptr<Dispatcher>
      CreateEquivalentDispatcherAndCloseImplNoLock() = 0;

  
  
  
  
  virtual MojoResult WriteMessageImplNoLock(
      UserPointer<const void> bytes,
      uint32_t num_bytes,
      std::vector<DispatcherTransport>* transports,
      MojoWriteMessageFlags flags);
  virtual MojoResult ReadMessageImplNoLock(UserPointer<void> bytes,
                                           UserPointer<uint32_t> num_bytes,
                                           DispatcherVector* dispatchers,
                                           uint32_t* num_dispatchers,
                                           MojoReadMessageFlags flags);
  virtual MojoResult WriteDataImplNoLock(UserPointer<const void> elements,
                                         UserPointer<uint32_t> num_bytes,
                                         MojoWriteDataFlags flags);
  virtual MojoResult BeginWriteDataImplNoLock(
      UserPointer<void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      MojoWriteDataFlags flags);
  virtual MojoResult EndWriteDataImplNoLock(uint32_t num_bytes_written);
  virtual MojoResult ReadDataImplNoLock(UserPointer<void> elements,
                                        UserPointer<uint32_t> num_bytes,
                                        MojoReadDataFlags flags);
  virtual MojoResult BeginReadDataImplNoLock(
      UserPointer<const void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      MojoReadDataFlags flags);
  virtual MojoResult EndReadDataImplNoLock(uint32_t num_bytes_read);
  virtual MojoResult DuplicateBufferHandleImplNoLock(
      UserPointer<const MojoDuplicateBufferHandleOptions> options,
      scoped_refptr<Dispatcher>* new_dispatcher);
  virtual MojoResult MapBufferImplNoLock(
      uint64_t offset,
      uint64_t num_bytes,
      MojoMapBufferFlags flags,
      scoped_ptr<embedder::PlatformSharedBufferMapping>* mapping);
  virtual HandleSignalsState GetHandleSignalsStateImplNoLock() const;
  virtual MojoResult AddWaiterImplNoLock(Waiter* waiter,
                                         MojoHandleSignals signals,
                                         uint32_t context,
                                         HandleSignalsState* signals_state);
  virtual void RemoveWaiterImplNoLock(Waiter* waiter,
                                      HandleSignalsState* signals_state);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void StartSerializeImplNoLock(Channel* channel,
                                        size_t* max_size,
                                        size_t* max_platform_handles);
  virtual bool EndSerializeAndCloseImplNoLock(
      Channel* channel,
      void* destination,
      size_t* actual_size,
      embedder::PlatformHandleVector* platform_handles);

  
  
  base::Lock& lock() const { return lock_; }

 private:
  friend class DispatcherTransport;

  
  
  
  virtual bool IsBusyNoLock() const;

  
  
  
  
  void CloseNoLock();

  
  
  
  
  
  scoped_refptr<Dispatcher> CreateEquivalentDispatcherAndCloseNoLock();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void StartSerialize(Channel* channel,
                      size_t* max_size,
                      size_t* max_platform_handles);
  
  
  
  
  
  
  
  
  
  
  
  bool EndSerializeAndClose(Channel* channel,
                            void* destination,
                            size_t* actual_size,
                            embedder::PlatformHandleVector* platform_handles);

  
  
  mutable base::Lock lock_;
  bool is_closed_;

  DISALLOW_COPY_AND_ASSIGN(Dispatcher);
};

class MOJO_SYSTEM_IMPL_EXPORT DispatcherTransport {
 public:
  DispatcherTransport() : dispatcher_(nullptr) {}

  void End();

  Dispatcher::Type GetType() const { return dispatcher_->GetType(); }
  bool IsBusy() const { return dispatcher_->IsBusyNoLock(); }
  void Close() { dispatcher_->CloseNoLock(); }
  scoped_refptr<Dispatcher> CreateEquivalentDispatcherAndClose() {
    return dispatcher_->CreateEquivalentDispatcherAndCloseNoLock();
  }

  bool is_valid() const { return !!dispatcher_; }

 protected:
  Dispatcher* dispatcher() { return dispatcher_; }

 private:
  friend class Dispatcher::HandleTableAccess;

  explicit DispatcherTransport(Dispatcher* dispatcher)
      : dispatcher_(dispatcher) {}

  Dispatcher* dispatcher_;

  
};

}  
}  

#endif  
