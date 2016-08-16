// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_ACCESS_POLICY_DELEGATE_H_
#define MOJO_SERVICES_VIEW_MANAGER_ACCESS_POLICY_DELEGATE_H_

#include <vector>

#include "base/containers/hash_tables.h"
#include "mojo/services/view_manager/ids.h"

namespace mojo {
namespace service {

class ServerView;

class AccessPolicyDelegate {
 public:
  
  
  virtual const base::hash_set<Id>& GetRootsForAccessPolicy() const = 0;

  
  virtual bool IsViewKnownForAccessPolicy(const ServerView* view) const = 0;

  
  virtual bool IsViewRootOfAnotherConnectionForAccessPolicy(
      const ServerView* view) const = 0;

 protected:
  virtual ~AccessPolicyDelegate() {}
};

}  
}  

#endif  
