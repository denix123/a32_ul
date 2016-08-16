// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SUGGESTIONS_SUGGESTIONS_UTILS_H_
#define COMPONENTS_SUGGESTIONS_SUGGESTIONS_UTILS_H_

namespace suggestions {

enum SyncState {
  
  
  
  
  NOT_INITIALIZED_ENABLED,

  
  
  
  INITIALIZED_ENABLED_HISTORY,

  
  
  
  SYNC_OR_HISTORY_SYNC_DISABLED,
};

SyncState GetSyncState(bool sync_enabled,
                       bool sync_initialized,
                       bool history_sync_enabled);

}  

#endif  
