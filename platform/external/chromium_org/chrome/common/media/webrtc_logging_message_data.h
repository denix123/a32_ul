// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_MEDIA_WEBRTC_LOGGING_MESSAGE_DATA_H_
#define CHROME_COMMON_MEDIA_WEBRTC_LOGGING_MESSAGE_DATA_H_

#include <string>

#include "base/time/time.h"

struct WebRtcLoggingMessageData {
  WebRtcLoggingMessageData();
  WebRtcLoggingMessageData(base::Time time, const std::string& message);

  
  
  
  std::string Format(base::Time start_time) const;

  base::Time timestamp;
  std::string message;
};

#endif  
