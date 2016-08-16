// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_RENDERER_MANIFEST_SERVICE_CHANNEL_H_
#define COMPONENTS_NACL_RENDERER_MANIFEST_SERVICE_CHANNEL_H_

#include "base/callback.h"
#include "base/files/file.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/process/process.h"
#include "base/synchronization/lock.h"
#include "ipc/ipc_listener.h"

namespace base {
class WaitableEvent;
}  

namespace IPC {
struct ChannelHandle;
class Message;
class SyncChannel;
}  

namespace nacl {

class ManifestServiceChannel : public IPC::Listener {
 public:
  typedef base::Callback<void(base::File, uint64_t, uint64_t)>
      OpenResourceCallback;

  class Delegate {
   public:
    virtual ~Delegate() {}

    
    virtual void StartupInitializationComplete() = 0;

    
    
    virtual void OpenResource(
        const std::string& key,
        const OpenResourceCallback& callback) = 0;
  };

  ManifestServiceChannel(
      const IPC::ChannelHandle& handle,
      const base::Callback<void(int32_t)>& connected_callback,
      scoped_ptr<Delegate> delegate,
      base::WaitableEvent* waitable_event);
  virtual ~ManifestServiceChannel();

  void Send(IPC::Message* message);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnChannelConnected(int32 peer_pid) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;

 private:
  void OnStartupInitializationComplete();
  void OnOpenResource(const std::string& key, IPC::Message* reply);
  void DidOpenResource(IPC::Message* reply,
                       base::File file,
                       uint64_t token_lo,
                       uint64_t token_hi);
  base::Callback<void(int32_t)> connected_callback_;
  scoped_ptr<Delegate> delegate_;
  scoped_ptr<IPC::SyncChannel> channel_;

  base::ProcessId peer_pid_;

  
  
  base::WeakPtrFactory<ManifestServiceChannel> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ManifestServiceChannel);
};

}  

#endif  
