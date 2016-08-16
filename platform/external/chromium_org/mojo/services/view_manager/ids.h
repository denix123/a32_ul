// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_IDS_H_
#define MOJO_SERVICES_VIEW_MANAGER_IDS_H_

#include "mojo/services/public/cpp/view_manager/types.h"
#include "mojo/services/public/cpp/view_manager/util.h"

namespace mojo {
namespace service {

const ConnectionSpecificId kInvalidConnectionId = 0;

const ConnectionSpecificId kWindowManagerConnection = 1;

struct ViewId {
  ViewId(ConnectionSpecificId connection_id, ConnectionSpecificId view_id)
      : connection_id(connection_id),
        view_id(view_id) {}
  ViewId() : connection_id(0), view_id(0) {}

  bool operator==(const ViewId& other) const {
    return other.connection_id == connection_id &&
        other.view_id == view_id;
  }

  bool operator!=(const ViewId& other) const {
    return !(*this == other);
  }

  ConnectionSpecificId connection_id;
  ConnectionSpecificId view_id;
};

inline ViewId ViewIdFromTransportId(Id id) {
  return ViewId(HiWord(id), LoWord(id));
}

inline Id ViewIdToTransportId(const ViewId& id) {
  return (id.connection_id << 16) | id.view_id;
}

inline ViewId RootViewId() {
  return ViewId(kInvalidConnectionId, 1);
}

inline ViewId InvalidViewId() {
  return ViewId(kInvalidConnectionId, 0);
}

}  
}  

#endif  
