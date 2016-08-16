// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_CALLBACK_TRACKER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_CALLBACK_TRACKER_H_

#include <map>

#include "base/bind.h"
#include "base/callback_forward.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/sync_file_system/drive_backend/callback_tracker_internal.h"

namespace sync_file_system {
namespace drive_backend {

class CallbackTracker {
 public:
  typedef std::map<internal::AbortHelper*, base::Closure> AbortClosureByHelper;

  CallbackTracker();
  ~CallbackTracker();

  
  
  
  
  
  template <typename T>
  base::Callback<T> Register(const base::Closure& abort_closure,
                             const base::Callback<T>& callback) {
    internal::AbortHelper* helper = new internal::AbortHelper(this);
    helpers_[helper] = abort_closure;
    return base::Bind(&internal::InvokeAndInvalidateHelper<T>::Run,
                      helper->AsWeakPtr(), callback);
  }

  void AbortAll();

 private:
  friend class internal::AbortHelper;

  scoped_ptr<internal::AbortHelper> PassAbortHelper(
      internal::AbortHelper* helper);

  AbortClosureByHelper helpers_;  

  DISALLOW_COPY_AND_ASSIGN(CallbackTracker);
};

}  
}  

#endif  
