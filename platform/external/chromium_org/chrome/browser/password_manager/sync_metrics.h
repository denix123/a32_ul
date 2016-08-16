// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PASSWORD_MANAGER_SYNC_METRICS_H_
#define CHROME_BROWSER_PASSWORD_MANAGER_SYNC_METRICS_H_

#include <string>

class Profile;

namespace password_manager_sync_metrics {

std::string GetSyncUsername(Profile* profile);

bool IsSyncAccountCredential(Profile* profile,
                             const std::string& username,
                             const std::string& origin);

}  

#endif  
