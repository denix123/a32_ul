// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_LOG_LIST_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_LOG_LIST_H_

#include "chrome/browser/upload_list.h"

class Profile;

class WebRtcLogList {
 public:
  
  
  
  static UploadList* CreateWebRtcLogList(UploadList::Delegate* delegate,
                                         Profile* profile);

  
  static base::FilePath GetWebRtcLogDirectoryForProfile(
      const base::FilePath& profile_path);

  
  
  static base::FilePath GetWebRtcLogListFileForDirectory(
      const base::FilePath& dir);
};

#endif  
