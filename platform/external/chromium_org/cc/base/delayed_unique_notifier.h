// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_BASE_DELAYED_UNIQUE_NOTIFIER_H_
#define CC_BASE_DELAYED_UNIQUE_NOTIFIER_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "cc/base/cc_export.h"

namespace base {
class SequencedTaskRunner;
}  

namespace cc {

class CC_EXPORT DelayedUniqueNotifier {
 public:
  
  
  DelayedUniqueNotifier(base::SequencedTaskRunner* task_runner,
                        const base::Closure& closure,
                        const base::TimeDelta& delay);

  
  
  virtual ~DelayedUniqueNotifier();

  
  
  
  
  
  void Schedule();

  
  void Cancel();

  
  bool HasPendingNotification() const;

 protected:
  
  virtual base::TimeTicks Now() const;

 private:
  void NotifyIfTime();

  base::SequencedTaskRunner* task_runner_;
  base::Closure closure_;
  base::TimeDelta delay_;
  base::TimeTicks next_notification_time_;
  bool notification_pending_;

  base::WeakPtrFactory<DelayedUniqueNotifier> weak_ptr_factory_;
};

}  

#endif  
