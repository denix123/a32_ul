// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_SERVER_BACKED_STATE_KEYS_BROKER_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_SERVER_BACKED_STATE_KEYS_BROKER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/callback_list.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"

namespace base {
class TaskRunner;
}

namespace chromeos {
class SessionManagerClient;
}

namespace policy {

class ServerBackedStateKeysBroker {
 public:
  typedef scoped_ptr<base::CallbackList<void()>::Subscription> Subscription;
  typedef base::Callback<void(const std::vector<std::string>&, bool)>
      StateKeysCallback;

  ServerBackedStateKeysBroker(
      chromeos::SessionManagerClient* session_manager_client,
      scoped_refptr<base::TaskRunner> delayed_task_runner);
  ~ServerBackedStateKeysBroker();

  
  
  
  
  Subscription RegisterUpdateCallback(const base::Closure& callback);

  
  
  
  
  void RequestStateKeys(const StateKeysCallback& callback);

  
  
  const std::vector<std::string>& state_keys() const { return state_keys_; }

  
  
  std::string current_state_key() const {
    return state_keys_.empty() ? std::string() : state_keys_.front();
  }

  
  bool pending() const { return !initial_retrieval_completed_; }

  
  bool available() const { return !state_keys_.empty(); }

 private:
  
  void FetchStateKeys();

  
  void StoreStateKeys(const std::vector<std::string>& state_keys,
                      bool first_boot);

  chromeos::SessionManagerClient* session_manager_client_;

  scoped_refptr<base::TaskRunner> delayed_task_runner_;

  
  std::vector<std::string> state_keys_;

  
  bool first_boot_;

  
  bool requested_;

  
  bool initial_retrieval_completed_;

  
  base::CallbackList<void()> update_callbacks_;

  
  std::vector<StateKeysCallback> request_callbacks_;

  base::WeakPtrFactory<ServerBackedStateKeysBroker> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServerBackedStateKeysBroker);
};

}  

#endif  
