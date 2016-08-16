// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_GAMEPAD_GAMEPAD_SERVICE_H
#define CONTENT_BROWSER_GAMEPAD_GAMEPAD_SERVICE_H

#include <set>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/memory/singleton.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"

namespace blink {
class WebGamepad;
}

namespace content {

class GamepadConsumer;
class GamepadDataFetcher;
class GamepadProvider;
class GamepadServiceTestConstructor;
class RenderProcessHost;

class CONTENT_EXPORT GamepadService {
 public:
  
  static GamepadService* GetInstance();

  
  
  
  
  
  
  
  
  
  void ConsumerBecameActive(GamepadConsumer* consumer);

  
  
  
  
  
  void ConsumerBecameInactive(GamepadConsumer* consumer);

  
  
  
  
  
  void RemoveConsumer(GamepadConsumer* consumer);

  
  
  
  void RegisterForUserGesture(const base::Closure& closure);

  
  
  base::SharedMemoryHandle GetSharedMemoryHandleForProcess(
      base::ProcessHandle handle);

  
  void Terminate();

  
  void OnGamepadConnected(int index, const blink::WebGamepad& pad);

  
  void OnGamepadDisconnected(int index, const blink::WebGamepad& pad);

 private:
  friend struct DefaultSingletonTraits<GamepadService>;
  friend class GamepadServiceTestConstructor;
  friend class GamepadServiceTest;

  GamepadService();

  
  
  GamepadService(scoped_ptr<GamepadDataFetcher> fetcher);

  virtual ~GamepadService();

  static void SetInstance(GamepadService*);

  void OnUserGesture();

  struct ConsumerInfo {
    ConsumerInfo(GamepadConsumer* consumer)
        : consumer(consumer),
          did_observe_user_gesture(false) {
    }

    bool operator<(const ConsumerInfo& other) const {
      return consumer < other.consumer;
    }

    GamepadConsumer* consumer;
    mutable bool is_active;
    mutable bool did_observe_user_gesture;
  };

  scoped_ptr<GamepadProvider> provider_;

  base::ThreadChecker thread_checker_;

  typedef std::set<ConsumerInfo> ConsumerSet;
  ConsumerSet consumers_;

  int num_active_consumers_;

  bool gesture_callback_pending_;

  DISALLOW_COPY_AND_ASSIGN(GamepadService);
};

}  

#endif  
