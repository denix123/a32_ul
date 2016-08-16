// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GOOGLE_GOOGLE_UPDATE_WIN_H_
#define CHROME_BROWSER_GOOGLE_GOOGLE_UPDATE_WIN_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "google_update/google_update_idl.h"

namespace base {
class MessageLoop;
}

namespace views {
class Widget;
}

enum GoogleUpdateUpgradeResult {
  
  UPGRADE_STARTED = 0,
  
  UPGRADE_CHECK_STARTED = 1,
  
  UPGRADE_IS_AVAILABLE = 2,
  
  UPGRADE_SUCCESSFUL = 3,
  
  UPGRADE_ALREADY_UP_TO_DATE = 4,
  
  UPGRADE_ERROR = 5,
  NUM_UPGRADE_RESULTS
};

enum GoogleUpdateErrorCode {
  
  GOOGLE_UPDATE_NO_ERROR = 0,
  
  
  
  CANNOT_UPGRADE_CHROME_IN_THIS_DIRECTORY = 1,
  
  GOOGLE_UPDATE_JOB_SERVER_CREATION_FAILED = 2,
  
  GOOGLE_UPDATE_ONDEMAND_CLASS_NOT_FOUND = 3,
  
  
  GOOGLE_UPDATE_ONDEMAND_CLASS_REPORTED_ERROR = 4,
  
  GOOGLE_UPDATE_GET_RESULT_CALL_FAILED = 5,
  
  GOOGLE_UPDATE_GET_VERSION_INFO_FAILED = 6,
  
  
  GOOGLE_UPDATE_ERROR_UPDATING = 7,
  
  
  GOOGLE_UPDATE_DISABLED_BY_POLICY = 8,
  
  
  GOOGLE_UPDATE_DISABLED_BY_POLICY_AUTO_ONLY = 9,
  NUM_ERROR_CODES
};

class GoogleUpdateStatusListener {
 public:
  
  
  
  
  
  
  
  virtual void OnReportResults(GoogleUpdateUpgradeResult results,
                               GoogleUpdateErrorCode error_code,
                               const base::string16& error_message,
                               const base::string16& version) = 0;
};

class GoogleUpdate : public base::RefCountedThreadSafe<GoogleUpdate> {
 public:
  GoogleUpdate();

  
  
  
  
  
  
  void CheckForUpdate(bool install_if_newer, HWND window);

  
  void set_status_listener(GoogleUpdateStatusListener* listener) {
    listener_ = listener;
  }

 private:
  friend class base::RefCountedThreadSafe<GoogleUpdate>;

  virtual ~GoogleUpdate();

  
  
  
  bool ReportFailure(HRESULT hr, GoogleUpdateErrorCode error_code,
                     const base::string16& error_message,
                     base::MessageLoop* main_loop);

  
  
  
  
  
  void InitiateGoogleUpdateCheck(bool install_if_newer, HWND window,
                                 base::MessageLoop* main_loop);

  
  
  
  
  void ReportResults(GoogleUpdateUpgradeResult results,
                     GoogleUpdateErrorCode error_code,
                     const base::string16& error_message);

  
  
  base::string16 version_available_;

  
  GoogleUpdateStatusListener* listener_;

  DISALLOW_COPY_AND_ASSIGN(GoogleUpdate);
};

#endif  
