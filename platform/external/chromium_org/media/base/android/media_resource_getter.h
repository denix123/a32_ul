// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_RESOURCE_GETTER_H_
#define MEDIA_BASE_ANDROID_MEDIA_RESOURCE_GETTER_H_

#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "url/gurl.h"

namespace media {

class MEDIA_EXPORT MediaResourceGetter {
 public:
  
  typedef base::Callback<void(const std::string&)> GetCookieCB;

  
  typedef base::Callback<void(const std::string&)> GetPlatformPathCB;

  
  typedef base::Callback<void(const base::string16&, const base::string16&)>
      GetAuthCredentialsCB;

  
  
  typedef base::Callback<void(base::TimeDelta, int, int, bool)>
      ExtractMediaMetadataCB;
  virtual ~MediaResourceGetter();

  
  virtual void GetAuthCredentials(const GURL& url,
                                  const GetAuthCredentialsCB& callback) = 0;

  
  virtual void GetCookies(const GURL& url,
                          const GURL& first_party_for_cookies,
                          const GetCookieCB& callback) = 0;

  
  virtual void GetPlatformPathFromURL(
      const GURL& url,
      const GetPlatformPathCB& callback) = 0;

  
  
  virtual void ExtractMediaMetadata(
      const std::string& url,
      const std::string& cookies,
      const std::string& user_agent,
      const ExtractMediaMetadataCB& callback) = 0;

  
  
  virtual void ExtractMediaMetadata(
      const int fd,
      const int64 offset,
      const int64 size,
      const ExtractMediaMetadataCB& callback) = 0;
};

}  

#endif  