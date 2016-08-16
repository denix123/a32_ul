// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_SYNC_INTEGRATION_TEST_UTIL_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_SYNC_INTEGRATION_TEST_UTIL_H_

class ProfileSyncService;

namespace sync_integration_test_util {

bool AwaitPassphraseRequired(ProfileSyncService* service);

bool AwaitPassphraseAccepted(ProfileSyncService* service);

bool AwaitCommitActivityCompletion(ProfileSyncService* service);

}  

#endif  
