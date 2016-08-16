// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_MEDIA_STREAM_DEVICE_PERMISSIONS_H_
#define CHROME_BROWSER_MEDIA_MEDIA_STREAM_DEVICE_PERMISSIONS_H_

class GURL;
class Profile;

enum MediaStreamDevicePolicy {
  POLICY_NOT_SET,
  ALWAYS_DENY,
  ALWAYS_ALLOW,
};

bool CheckAllowAllMediaStreamContentForOrigin(Profile* profile,
                                              const GURL& security_origin);

MediaStreamDevicePolicy GetDevicePolicy(Profile* profile,
                                        const GURL& security_origin,
                                        const char* policy_name,
                                        const char* whitelist_policy_name);

#endif  
