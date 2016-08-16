// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_X_X11_FOREIGN_WINDOW_MANAGER_H_
#define UI_BASE_X_X11_FOREIGN_WINDOW_MANAGER_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/x/x11_types.h"

template <typename T> struct DefaultSingletonTraits;

namespace ui {

class UI_BASE_EXPORT XForeignWindowManager {
 public:
  static XForeignWindowManager* GetInstance();

  
  
  int RequestEvents(XID xid, long event_mask) WARN_UNUSED_RESULT;

  
  
  
  void CancelRequest(int request_id);

  
  void OnWindowDestroyed(XID xid);

 private:
  friend struct DefaultSingletonTraits<XForeignWindowManager>;

  struct Request {
    Request(int request_id, long entry_event_mask);
    ~Request();

    int request_id;
    long event_mask;
  };

  XForeignWindowManager();
  ~XForeignWindowManager();

  
  void UpdateSelectedEvents(XID xid);

  
  int next_request_id_;

  typedef std::vector<Request> RequestVector;
  std::map<XID, RequestVector> request_map_;

  DISALLOW_COPY_AND_ASSIGN(XForeignWindowManager);
};

}  

#endif  
