// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_INPUT_INPUT_EVENT_FILTER_H_
#define CONTENT_RENDERER_INPUT_INPUT_EVENT_FILTER_H_

#include <queue>
#include <set>

#include "base/callback_forward.h"
#include "base/synchronization/lock.h"
#include "content/common/content_export.h"
#include "content/common/input/input_event_ack_state.h"
#include "content/renderer/input/input_handler_manager_client.h"
#include "ipc/message_filter.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"

namespace base {
class MessageLoopProxy;
class SingleThreadTaskRunner;
}

namespace IPC {
class Listener;
class Sender;
}


namespace content {

class CONTENT_EXPORT InputEventFilter : public InputHandlerManagerClient,
                                        public IPC::MessageFilter {
 public:
  InputEventFilter(
      IPC::Listener* main_listener,
      const scoped_refptr<base::SingleThreadTaskRunner>& main_task_runner,
      const scoped_refptr<base::MessageLoopProxy>& target_loop);

  
  
  
  
  
  
  
  
  
  
  virtual void SetBoundHandler(const Handler& handler) OVERRIDE;
  virtual void DidAddInputHandler(int routing_id,
                                  cc::InputHandler* input_handler) OVERRIDE;
  virtual void DidRemoveInputHandler(int routing_id) OVERRIDE;
  virtual void DidOverscroll(int routing_id,
                             const DidOverscrollParams& params) OVERRIDE;
  virtual void DidStopFlinging(int routing_id) OVERRIDE;

  
  virtual void OnFilterAdded(IPC::Sender* sender) OVERRIDE;
  virtual void OnFilterRemoved() OVERRIDE;
  virtual void OnChannelClosing() OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 private:
  virtual ~InputEventFilter();

  void ForwardToMainListener(const IPC::Message& message);
  void ForwardToHandler(const IPC::Message& message);
  void SendMessage(scoped_ptr<IPC::Message> message);
  void SendMessageOnIOThread(scoped_ptr<IPC::Message> message);

  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;
  IPC::Listener* main_listener_;

  
  scoped_refptr<base::MessageLoopProxy> io_loop_;
  IPC::Sender* sender_;

  
  scoped_refptr<base::MessageLoopProxy> target_loop_;
  Handler handler_;

  
  base::Lock routes_lock_;

  
  std::set<int> routes_;

  
  bool overscroll_notifications_enabled_;

  
  
  
  
  scoped_ptr<DidOverscrollParams>* current_overscroll_params_;
};

}  

#endif  
