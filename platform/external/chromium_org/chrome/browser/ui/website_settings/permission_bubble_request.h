// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_REQUEST_H_
#define CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_REQUEST_H_

#include "base/strings/string16.h"
#include "url/gurl.h"

class PermissionBubbleRequest {
 public:
  virtual ~PermissionBubbleRequest() {}

  
  
  virtual int GetIconID() const = 0;

  
  
  
  virtual base::string16 GetMessageText() const = 0;

  
  
  
  
  virtual base::string16 GetMessageTextFragment() const = 0;

  
  
  virtual bool HasUserGesture() const = 0;

  
  virtual GURL GetRequestingHostname() const = 0;

  
  virtual void PermissionGranted() = 0;

  
  virtual void PermissionDenied() = 0;

  
  
  
  virtual void Cancelled() = 0;

  
  
  
  
  virtual void RequestFinished() = 0;
};

#endif  
