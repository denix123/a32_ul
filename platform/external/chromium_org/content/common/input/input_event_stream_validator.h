// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_INPUT_EVENT_STREAM_VALIDATOR
#define CONTENT_COMMON_INPUT_EVENT_STREAM_VALIDATOR

#include <string>

#include "content/common/input/gesture_event_stream_validator.h"
#include "content/common/input/touch_event_stream_validator.h"

namespace blink {
class WebInputEvent;
}

namespace content {

class InputEventStreamValidator {
 public:
  InputEventStreamValidator();
  ~InputEventStreamValidator();

  void Validate(const blink::WebInputEvent&);

 private:
  bool ValidateImpl(const blink::WebInputEvent&, std::string* error_msg);

  GestureEventStreamValidator gesture_validator_;
  TouchEventStreamValidator touch_validator_;
  std::string error_msg_;
  const bool enabled_;

  DISALLOW_COPY_AND_ASSIGN(InputEventStreamValidator);
};

}  

#endif  