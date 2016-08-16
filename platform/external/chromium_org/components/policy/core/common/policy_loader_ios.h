// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_POLICY_LOADER_IOS_H_
#define COMPONENTS_POLICY_CORE_COMMON_POLICY_LOADER_IOS_H_

#include "base/basictypes.h"
#include "base/mac/scoped_nsobject.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "components/policy/core/common/async_policy_loader.h"
#include "components/policy/policy_export.h"

namespace policy {

class POLICY_EXPORT PolicyLoaderIOS : public AsyncPolicyLoader {
 public:
  explicit PolicyLoaderIOS(
      scoped_refptr<base::SequencedTaskRunner> task_runner);
  virtual ~PolicyLoaderIOS();

  
  virtual void InitOnBackgroundThread() OVERRIDE;
  virtual scoped_ptr<PolicyBundle> Load() OVERRIDE;
  virtual base::Time LastModificationTime() OVERRIDE;

 private:
  void UserDefaultsChanged();

  
  static void LoadNSDictionaryToPolicyBundle(NSDictionary* dictionary,
                                             PolicyBundle* bundle);

  
  base::scoped_nsobject<id> notification_observer_;

  
  
  base::Time last_notification_time_;

  
  
  base::WeakPtrFactory<PolicyLoaderIOS> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PolicyLoaderIOS);
};

}  

#endif  
