// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GOOGLE_GOOGLE_URL_TRACKER_CLIENT_H_
#define COMPONENTS_GOOGLE_GOOGLE_URL_TRACKER_CLIENT_H_

#include "base/macros.h"
#include "url/gurl.h"

class GoogleURLTracker;
class PrefService;

namespace net {
class URLRequestContextGetter;
}

class GoogleURLTrackerClient {
 public:
  GoogleURLTrackerClient();
  virtual ~GoogleURLTrackerClient();

  
  void set_google_url_tracker(GoogleURLTracker* google_url_tracker) {
    google_url_tracker_ = google_url_tracker;
  }

  
  
  virtual void SetListeningForNavigationStart(bool listen) = 0;

  
  
  virtual bool IsListeningForNavigationStart() = 0;

  
  virtual bool IsBackgroundNetworkingEnabled() = 0;

  
  virtual PrefService* GetPrefs() = 0;

  
  
  virtual net::URLRequestContextGetter* GetRequestContext() = 0;

 protected:
  GoogleURLTracker* google_url_tracker() { return google_url_tracker_; }

 private:
  GoogleURLTracker* google_url_tracker_;

  DISALLOW_COPY_AND_ASSIGN(GoogleURLTrackerClient);
};

#endif  
