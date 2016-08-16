// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_PERMISSION_REQUEST_ID_H_
#define COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_PERMISSION_REQUEST_ID_H_

#include <string>

#include "url/gurl.h"

class PermissionRequestID {
 public:
  PermissionRequestID(int render_process_id,
                      int render_view_id,
                      int bridge_id,
                      const GURL& origin);
  ~PermissionRequestID();

  int render_process_id() const { return render_process_id_; }
  int render_view_id() const { return render_view_id_; }
  int bridge_id() const { return bridge_id_; }
  GURL origin() const { return origin_; }

  bool Equals(const PermissionRequestID& other) const;
  bool IsForSameTabAs(const PermissionRequestID& other) const;
  std::string ToString() const;

 private:
  int render_process_id_;
  int render_view_id_;
  
  int bridge_id_;
  
  
  GURL origin_;

  
};

#endif  
