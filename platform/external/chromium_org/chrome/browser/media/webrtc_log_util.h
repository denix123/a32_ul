// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_LOG_UTIL_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_LOG_UTIL_H_

#include "base/files/file_path.h"
#include "base/time/time.h"

class WebRtcLogUtil {
 public:
  
  
  static void DeleteOldWebRtcLogFiles(const base::FilePath& log_dir);

  
  
  
  
  static void DeleteOldAndRecentWebRtcLogFiles(
      const base::FilePath& log_dir,
      const base::Time& delete_begin_time);

  
  
  static void DeleteOldWebRtcLogFilesForAllProfiles();
};

#endif  
