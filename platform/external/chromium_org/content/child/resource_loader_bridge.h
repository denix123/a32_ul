// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_RESOURCE_LOADER_BRIDGE_H_
#define CONTENT_CHILD_RESOURCE_LOADER_BRIDGE_H_

#include "base/macros.h"
#include "content/common/content_export.h"
#include "net/base/request_priority.h"

namespace blink {
class WebThreadedDataReceiver;
}

namespace content {

class RequestPeer;
class ResourceRequestBody;
struct SyncLoadResponse;

class CONTENT_EXPORT ResourceLoaderBridge {
 public:
  
  
  virtual ~ResourceLoaderBridge();

  
  
  virtual void SetRequestBody(ResourceRequestBody* request_body) = 0;

  
  
  virtual bool Start(RequestPeer* peer) = 0;

  
  
  
  
  virtual void Cancel() = 0;

  
  
  virtual void SetDefersLoading(bool value) = 0;

  
  
  
  virtual void DidChangePriority(net::RequestPriority new_priority,
                                 int intra_priority_value) = 0;

  
  
  virtual bool AttachThreadedDataReceiver(
      blink::WebThreadedDataReceiver* threaded_data_receiver) = 0;

  
  
  
  
  
  
  
  virtual void SyncLoad(SyncLoadResponse* response) = 0;

 protected:
  
  
  
  
  ResourceLoaderBridge();

 private:
  DISALLOW_COPY_AND_ASSIGN(ResourceLoaderBridge);
};

}  

#endif  
