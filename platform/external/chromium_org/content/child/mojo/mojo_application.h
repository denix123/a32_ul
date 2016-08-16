// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_MOJO_MOJO_APPLICATION_H_
#define CONTENT_CHILD_MOJO_MOJO_APPLICATION_H_

#include "content/common/mojo/service_registry_impl.h"
#include "ipc/ipc_platform_file.h"
#include "mojo/embedder/channel_init.h"

namespace IPC {
class Message;
}

namespace content {

class MojoApplication {
 public:
  MojoApplication();
  virtual ~MojoApplication();

  bool OnMessageReceived(const IPC::Message& msg);

  ServiceRegistry* service_registry() { return &service_registry_; }

 private:
  void OnActivate(const IPC::PlatformFileForTransit& file);

  mojo::embedder::ChannelInit channel_init_;

  ServiceRegistryImpl service_registry_;

  DISALLOW_COPY_AND_ASSIGN(MojoApplication);
};

}  

#endif  
