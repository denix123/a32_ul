// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_DEVFS_JSPIPE_NODE_H_
#define LIBRARIES_NACL_IO_DEVFS_JSPIPE_NODE_H_

#include <ppapi/c/pp_var.h>
#include <string>

#include "nacl_io/devfs/jspipe_event_emitter.h"
#include "nacl_io/stream/stream_node.h"

namespace nacl_io {

class MessagingInterface;
class VarInterface;
class VarArrayInterface;
class VarArrayBufferInterface;
class VarDictionaryInterface;

class JSPipeNode : public Node {
 public:
  explicit JSPipeNode(Filesystem* filesystem);

  virtual void Destroy() {
    LOG_TRACE("JSPipeNode: Destroy");
  }

  virtual JSPipeEventEmitter* GetEventEmitter();

  virtual Error VIoctl(int request, va_list args);

  virtual Error Read(const HandleAttr& attr,
                     void* buf,
                     size_t count,
                     int* out_bytes);
  virtual Error Write(const HandleAttr& attr,
                      const void* buf,
                      size_t count,
                      int* out_bytes);

 protected:
  Error SendAck();

  ScopedJSPipeEventEmitter pipe_;
};

}  

#endif  
