// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_RESOURCE_REPLY_THREAD_REGISTRAR_H_
#define PPAPI_PROXY_RESOURCE_REPLY_THREAD_REGISTRAR_H_

#include <map>
#include <set>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"


namespace base {
class MessageLoopProxy;
}

namespace IPC {
class Message;
}

namespace ppapi {

class TrackedCallback;

namespace proxy {

class ResourceMessageReplyParams;

class PPAPI_PROXY_EXPORT ResourceReplyThreadRegistrar
    : public base::RefCountedThreadSafe<ResourceReplyThreadRegistrar> {
 public:
  explicit ResourceReplyThreadRegistrar(
      scoped_refptr<base::MessageLoopProxy> main_thread);

  
  
  void Register(PP_Resource resource,
                int32_t sequence_number,
                scoped_refptr<TrackedCallback> reply_thread_hint);
  void Unregister(PP_Resource resource);

  
  
  
  void HandleOnIOThread(uint32 nested_msg_type);

  
  
  scoped_refptr<base::MessageLoopProxy> GetTargetThread(
      const ResourceMessageReplyParams& reply_params,
      const IPC::Message& nested_msg);

 private:
  friend class base::RefCountedThreadSafe<ResourceReplyThreadRegistrar>;

  typedef std::map<int32_t, scoped_refptr<base::MessageLoopProxy> >
      SequenceThreadMap;
  typedef std::map<PP_Resource, SequenceThreadMap> ResourceMap;

  ~ResourceReplyThreadRegistrar();

  
  
  
  base::Lock lock_;
  ResourceMap map_;
  std::set<uint32> io_thread_message_types_;
  scoped_refptr<base::MessageLoopProxy> main_thread_;

  DISALLOW_COPY_AND_ASSIGN(ResourceReplyThreadRegistrar);
};

}  
}  

#endif   
