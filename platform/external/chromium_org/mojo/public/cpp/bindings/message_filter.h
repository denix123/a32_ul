// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_MESSAGE_FILTER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_MESSAGE_FILTER_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {

class MessageFilter : public MessageReceiver {
 public:
  
  
  explicit MessageFilter(MessageReceiver* sink = NULL);
  virtual ~MessageFilter();

  void set_sink(MessageReceiver* sink) { sink_ = sink; }

 protected:
  MessageReceiver* sink_;
};

class PassThroughFilter : public MessageFilter {
 public:
  explicit PassThroughFilter(MessageReceiver* sink = NULL);

  virtual bool Accept(Message* message) MOJO_OVERRIDE;
};

}  

#endif  
