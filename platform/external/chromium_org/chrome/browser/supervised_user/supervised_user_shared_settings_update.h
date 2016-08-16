// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SHARED_SETTINGS_UPDATE_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_SHARED_SETTINGS_UPDATE_H_

#include <string>

#include "base/callback.h"
#include "base/callback_list.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class Value;
}

class SupervisedUserSharedSettingsService;

class SupervisedUserSharedSettingsUpdate {
 public:
  SupervisedUserSharedSettingsUpdate(
      SupervisedUserSharedSettingsService* service,
      const std::string& su_id,
      const std::string& key,
      scoped_ptr<base::Value> value,
      const base::Callback<void(bool)>& success_callback);
  ~SupervisedUserSharedSettingsUpdate();

 private:
  typedef base::CallbackList<void(const std::string&, const std::string&)>
      CallbackList;

  void OnSettingChanged(const std::string& su_id,
                        const std::string& key);

  SupervisedUserSharedSettingsService* service_;
  std::string su_id_;
  std::string key_;
  scoped_ptr<base::Value> value_;
  base::Callback<void(bool)> callback_;
  scoped_ptr<CallbackList::Subscription> subscription_;
};

#endif  
