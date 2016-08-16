// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_STORE_CONSUMER_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_PASSWORD_STORE_CONSUMER_H_

#include <vector>

#include "base/task/cancelable_task_tracker.h"

namespace autofill {
struct PasswordForm;
}

namespace password_manager {

class PasswordStoreConsumer {
 public:
  PasswordStoreConsumer();

  
  
  
  virtual void OnGetPasswordStoreResults(
      const std::vector<autofill::PasswordForm*>& results) = 0;

  
  
  base::CancelableTaskTracker* cancelable_task_tracker() {
    return &cancelable_task_tracker_;
  }

  base::WeakPtr<PasswordStoreConsumer> GetWeakPtr() {
    return weak_ptr_factory_.GetWeakPtr();
  }

 protected:
  virtual ~PasswordStoreConsumer();

 private:
  base::CancelableTaskTracker cancelable_task_tracker_;
  base::WeakPtrFactory<PasswordStoreConsumer> weak_ptr_factory_;
};

}  

#endif  
