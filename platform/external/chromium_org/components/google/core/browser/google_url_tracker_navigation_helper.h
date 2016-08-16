// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_URL_TRACKER_NAVIGATION_HELPER_H_
#define COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_URL_TRACKER_NAVIGATION_HELPER_H_

#include "base/macros.h"
#include "ui/base/window_open_disposition.h"

class GoogleURLTracker;
class GURL;

class GoogleURLTrackerNavigationHelper {
 public:
  explicit GoogleURLTrackerNavigationHelper(
      GoogleURLTracker* google_url_tracker);
  virtual ~GoogleURLTrackerNavigationHelper();

  
  
  
  virtual void SetListeningForNavigationCommit(bool listen) = 0;

  
  
  virtual bool IsListeningForNavigationCommit() = 0;

  
  
  virtual void SetListeningForTabDestruction(bool listen) = 0;

  
  
  virtual bool IsListeningForTabDestruction() = 0;

  
  virtual void OpenURL(GURL url,
                       WindowOpenDisposition disposition,
                       bool user_clicked_on_link) = 0;

 protected:
  GoogleURLTracker* google_url_tracker() { return google_url_tracker_; }

 private:
  GoogleURLTracker* google_url_tracker_;

  DISALLOW_COPY_AND_ASSIGN(GoogleURLTrackerNavigationHelper);
};

#endif  
