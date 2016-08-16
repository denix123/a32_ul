// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_CAPTURE_UTIL_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_WEB_CONTENTS_CAPTURE_UTIL_H_

#include <string>

#include "content/common/content_export.h"

namespace content {

class CONTENT_EXPORT WebContentsCaptureUtil {
 public:
  
  static bool IsWebContentsDeviceId(const std::string& device_id);

  
  
  static bool ExtractTabCaptureTarget(const std::string& device_id,
                                      int* render_process_id,
                                      int* main_render_frame_id);
};

}  

#endif  
