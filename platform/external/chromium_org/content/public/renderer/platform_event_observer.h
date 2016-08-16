// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_PLATFORM_EVENT_OBSERVER_H_
#define CONTENT_PUBLIC_RENDERER_PLATFORM_EVENT_OBSERVER_H_

#include "base/logging.h"
#include "content/public/renderer/render_process_observer.h"
#include "content/public/renderer/render_thread.h"

namespace blink {
class WebPlatformEventListener;
}

namespace content {

class PlatformEventObserverBase {
 public:
  virtual ~PlatformEventObserverBase() { }

  
  

  virtual void Start(blink::WebPlatformEventListener* listener) = 0;
  virtual void Stop() = 0;

  
  
  virtual void SendFakeDataForTesting(void* data) { }
};

template <typename ListenerType>
class PlatformEventObserver : public PlatformEventObserverBase,
                              public RenderProcessObserver {
 public:
  
  
  
  PlatformEventObserver()
      : is_observing_(false),
        listener_(0) {
  }

  
  
  
  explicit PlatformEventObserver(RenderThread* thread)
      : is_observing_(false),
        listener_(0) {
    if (thread)
      thread->AddObserver(this);
  }

  
  
  virtual ~PlatformEventObserver() {
    if (is_observing())
      Stop();
  }

  
  
  virtual bool OnControlMessageReceived(const IPC::Message& msg) OVERRIDE {
    return false;
  }

  
  
  
  virtual void Start(blink::WebPlatformEventListener* listener) {
    DCHECK(!is_observing());
    listener_ = static_cast<ListenerType*>(listener);
    is_observing_ = true;

    SendStartMessage();
  }

  
  
  virtual void Stop() {
    DCHECK(is_observing());
    listener_ = 0;
    is_observing_ = false;

    SendStopMessage();
  }

 protected:
  
  
  
  virtual void SendStartMessage() = 0;

  
  
  
  virtual void SendStopMessage() = 0;

  bool is_observing() const {
    return is_observing_;
  }

  ListenerType* listener() {
    return listener_;
  }

 private:
  bool is_observing_;
  ListenerType* listener_;

  DISALLOW_COPY_AND_ASSIGN(PlatformEventObserver);
};

} 

#endif 
