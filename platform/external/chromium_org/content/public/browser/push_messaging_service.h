// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_PUSH_MESSAGING_SERVICE_H_
#define CONTENT_PUBLIC_BROWSER_PUSH_MESSAGING_SERVICE_H_

#include <string>

#include "base/callback.h"
#include "content/common/content_export.h"
#include "content/public/common/push_messaging_status.h"
#include "url/gurl.h"

namespace content {

class CONTENT_EXPORT PushMessagingService {
 public:
  typedef base::Callback<void(const GURL& ,
                              const std::string& ,
                              PushMessagingStatus )>
      RegisterCallback;

  virtual ~PushMessagingService() {}
  virtual void Register(const GURL& origin,
                        int64 service_worker_registration_id,
                        const std::string& sender_id,
                        int renderer_id,
                        int render_frame_id,
                        bool user_gesture,
                        const RegisterCallback& callback) = 0;
};

}  

#endif  
