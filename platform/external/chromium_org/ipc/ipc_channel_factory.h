// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_CHANNEL_FACTORY_H_
#define IPC_IPC_CHANNEL_FACTORY_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "ipc/ipc_channel.h"

namespace IPC {

class IPC_EXPORT ChannelFactory {
 public:
  
  
  static scoped_ptr<ChannelFactory> Create(
      const ChannelHandle& handle, Channel::Mode mode);

  virtual ~ChannelFactory() { }
  virtual std::string GetName() const = 0;
  virtual scoped_ptr<Channel> BuildChannel(Listener* listener) = 0;
};

}  

#endif  
