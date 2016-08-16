// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_LOGGER_UTIL_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_LOGGER_UTIL_H_

#include "extensions/common/api/cast_channel.h"
#include "extensions/common/api/cast_channel/logging.pb.h"

namespace extensions {
namespace core_api {
namespace cast_channel {
proto::ErrorState ErrorStateToProto(ChannelError state);

proto::ReadyState ReadyStateToProto(ReadyState state);

struct LastErrors {
 public:
  LastErrors();
  ~LastErrors();

  
  proto::EventType event_type;

  
  proto::ChallengeReplyErrorType challenge_reply_error_type;

  
  int net_return_value;

  
  int nss_error_code;
};

}  
}  
}  

#endif  
