// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_CHANNEL_H_
#define MOJO_SYSTEM_CHANNEL_H_

#include <stdint.h>

#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/channel_endpoint.h"
#include "mojo/system/message_in_transit.h"
#include "mojo/system/message_pipe.h"
#include "mojo/system/raw_channel.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {

namespace embedder {
class PlatformSupport;
}

namespace system {

class ChannelEndpoint;

class MOJO_SYSTEM_IMPL_EXPORT Channel
    : public base::RefCountedThreadSafe<Channel>,
      public RawChannel::Delegate {
 public:
  
  static const MessageInTransit::EndpointId kBootstrapEndpointId = 1;

  
  
  explicit Channel(embedder::PlatformSupport* platform_support);

  
  
  
  
  bool Init(scoped_ptr<RawChannel> raw_channel);

  
  
  void Shutdown();

  
  
  // are written after this is called; other warnings may be suppressed. (This
  
  void WillShutdownSoon();

  
  
  
  
  
  
  
  
  
  MessageInTransit::EndpointId AttachEndpoint(
      scoped_refptr<ChannelEndpoint> endpoint);

  
  
  
  
  
  bool RunMessagePipeEndpoint(MessageInTransit::EndpointId local_id,
                              MessageInTransit::EndpointId remote_id);

  
  
  
  
  
  
  void RunRemoteMessagePipeEndpoint(MessageInTransit::EndpointId local_id,
                                    MessageInTransit::EndpointId remote_id);

  
  bool WriteMessage(scoped_ptr<MessageInTransit> message);

  
  
  
  bool IsWriteBufferEmpty();

  
  
  
  
  void DetachMessagePipeEndpoint(MessageInTransit::EndpointId local_id,
                                 MessageInTransit::EndpointId remote_id);

  
  size_t GetSerializedPlatformHandleSize() const;

  embedder::PlatformSupport* platform_support() const {
    return platform_support_;
  }

 private:
  friend class base::RefCountedThreadSafe<Channel>;
  virtual ~Channel();

  
  virtual void OnReadMessage(
      const MessageInTransit::View& message_view,
      embedder::ScopedPlatformHandleVectorPtr platform_handles) OVERRIDE;
  virtual void OnError(Error error) OVERRIDE;

  
  void OnReadMessageForDownstream(
      const MessageInTransit::View& message_view,
      embedder::ScopedPlatformHandleVectorPtr platform_handles);
  void OnReadMessageForChannel(
      const MessageInTransit::View& message_view,
      embedder::ScopedPlatformHandleVectorPtr platform_handles);

  
  
  
  
  bool RemoveMessagePipeEndpoint(MessageInTransit::EndpointId local_id,
                                 MessageInTransit::EndpointId remote_id);

  
  
  void HandleRemoteError(const base::StringPiece& error_message);
  
  
  void HandleLocalError(const base::StringPiece& error_message);

  
  
  bool SendControlMessage(MessageInTransit::Subtype subtype,
                          MessageInTransit::EndpointId source_id,
                          MessageInTransit::EndpointId destination_id);

  base::ThreadChecker creation_thread_checker_;

  embedder::PlatformSupport* const platform_support_;

  
  
  
  
  base::Lock lock_;  

  scoped_ptr<RawChannel> raw_channel_;
  bool is_running_;
  
  bool is_shutting_down_;

  typedef base::hash_map<MessageInTransit::EndpointId,
                         scoped_refptr<ChannelEndpoint>> IdToEndpointMap;
  IdToEndpointMap local_id_to_endpoint_map_;
  
  
  MessageInTransit::EndpointId next_local_id_;

  DISALLOW_COPY_AND_ASSIGN(Channel);
};

}  
}  

#endif  
