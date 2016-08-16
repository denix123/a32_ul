// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_SESSIONS_SESSIONS_UTIL_H_
#define CHROME_BROWSER_SYNC_SESSIONS_SESSIONS_UTIL_H_

namespace browser_sync {

class SyncedTabDelegate;
class SyncedWindowDelegate;

namespace sessions_util {

bool ShouldSyncTab(const SyncedTabDelegate& tab);

bool ShouldSyncWindow(const SyncedWindowDelegate* window);

}  

}  

#endif  
