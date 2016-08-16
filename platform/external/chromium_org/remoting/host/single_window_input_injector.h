// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_SINGLE_WINDOW_INPUT_INJECTOR_H_
#define REMOTING_HOST_SINGLE_WINDOW_INPUT_INJECTOR_H_

#include "base/memory/scoped_ptr.h"
#include "remoting/host/input_injector.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capture_types.h"

namespace remoting {

class SingleWindowInputInjector : public InputInjector {
 public:
  
  
  static scoped_ptr<InputInjector> CreateForWindow(
      webrtc::WindowId window_id,
      scoped_ptr<InputInjector> input_injector);
};

}  

#endif  
