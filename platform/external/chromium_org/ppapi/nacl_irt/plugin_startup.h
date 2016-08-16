// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_NACL_IRT_PLUGIN_STARTUP_H_
#define PPAPI_NACL_IRT_PLUGIN_STARTUP_H_

#include "ppapi/proxy/ppapi_proxy_export.h"

namespace base {
class Thread;
class WaitableEvent;
}  

namespace ppapi {

class ManifestService;

PPAPI_PROXY_EXPORT void SetIPCFileDescriptors(
    int browser_ipc_fd, int renderer_ipc_fd, int manifest_service_fd);

PPAPI_PROXY_EXPORT void StartUpPlugin();

int GetBrowserIPCFileDescriptor();

int GetRendererIPCFileDescriptor();

base::WaitableEvent* GetShutdownEvent();

base::Thread* GetIOThread();

ManifestService* GetManifestService();

}  

#endif  
