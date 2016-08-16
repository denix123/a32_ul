// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_RENDERER_NEXE_PROGRESS_EVENT_H_
#define COMPONENTS_NACL_RENDERER_NEXE_PROGRESS_EVENT_H_

#include <string>

#include "ppapi/c/pp_instance.h"
#include "ppapi/c/private/ppb_nacl_private.h"

namespace nacl {

struct ProgressEvent {
  explicit ProgressEvent(PP_NaClEventType event_type_param)
      : event_type(event_type_param),
        length_is_computable(false),
        loaded_bytes(0),
        total_bytes(0) {
  }

  ProgressEvent(PP_NaClEventType event_type_param,
                const std::string& resource_url_param,
                bool length_is_computable_param,
                uint64_t loaded_bytes_param,
                uint64_t total_bytes_param)
      : event_type(event_type_param),
        resource_url(resource_url_param),
        length_is_computable(length_is_computable_param),
        loaded_bytes(loaded_bytes_param),
        total_bytes(total_bytes_param) {
  }

  PP_NaClEventType event_type;
  std::string resource_url;
  bool length_is_computable;
  uint64_t loaded_bytes;
  uint64_t total_bytes;
};

void DispatchProgressEvent(PP_Instance instance, const ProgressEvent& event);

}  

#endif  
