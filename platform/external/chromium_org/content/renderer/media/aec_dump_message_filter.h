// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_AEC_DUMP_MESSAGE_FILTER_H_
#define CONTENT_RENDERER_MEDIA_AEC_DUMP_MESSAGE_FILTER_H_

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/renderer/render_thread_impl.h"
#include "ipc/ipc_platform_file.h"
#include "ipc/message_filter.h"

namespace base {
class MessageLoopProxy;
}

namespace content {

class CONTENT_EXPORT AecDumpMessageFilter : public IPC::MessageFilter {
 public:
  class AecDumpDelegate {
   public:
    virtual void OnAecDumpFile(
        const IPC::PlatformFileForTransit& file_handle) = 0;
    virtual void OnDisableAecDump() = 0;
    virtual void OnIpcClosing() = 0;
  };

  AecDumpMessageFilter(
      const scoped_refptr<base::MessageLoopProxy>& io_message_loop,
      const scoped_refptr<base::MessageLoopProxy>& main_message_loop);

  
  static scoped_refptr<AecDumpMessageFilter> Get();

  
  void AddDelegate(AecDumpMessageFilter::AecDumpDelegate* delegate);

  
  void RemoveDelegate(AecDumpMessageFilter::AecDumpDelegate* delegate);

  
  scoped_refptr<base::MessageLoopProxy> io_message_loop() const {
    return io_message_loop_;
  }

 protected:
  virtual ~AecDumpMessageFilter();

 private:
  
  void Send(IPC::Message* message);

  
  
  
  void RegisterAecDumpConsumer(int id);

  
  void UnregisterAecDumpConsumer(int id);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnFilterAdded(IPC::Sender* sender) OVERRIDE;
  virtual void OnFilterRemoved() OVERRIDE;
  virtual void OnChannelClosing() OVERRIDE;

  
  void OnEnableAecDump(int id, IPC::PlatformFileForTransit file_handle);
  void OnDisableAecDump();

  
  void DoEnableAecDump(int id, IPC::PlatformFileForTransit file_handle);
  void DoDisableAecDump();
  void DoChannelClosingOnDelegates();
  int GetIdForDelegate(AecDumpMessageFilter::AecDumpDelegate* delegate);

  
  IPC::Sender* sender_;

  
  
  typedef std::map<int, AecDumpMessageFilter::AecDumpDelegate*> DelegateMap;
  DelegateMap delegates_;

  
  
  int delegate_id_counter_;

  
  const scoped_refptr<base::MessageLoopProxy> io_message_loop_;

  
  const scoped_refptr<base::MessageLoopProxy> main_message_loop_;

  
  static AecDumpMessageFilter* g_filter;

  DISALLOW_COPY_AND_ASSIGN(AecDumpMessageFilter);
};

}  

#endif  
