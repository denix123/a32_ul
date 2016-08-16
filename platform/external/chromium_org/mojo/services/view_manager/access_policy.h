// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_ACCESS_POLICY_H_
#define MOJO_SERVICES_VIEW_MANAGER_ACCESS_POLICY_H_

#include "mojo/services/public/interfaces/view_manager/view_manager_constants.mojom.h"
#include "mojo/services/view_manager/ids.h"

namespace mojo {
namespace service {

class ServerView;

class AccessPolicy {
 public:
  virtual ~AccessPolicy() {}

  
  
  
  virtual bool CanRemoveViewFromParent(const ServerView* view) const = 0;
  virtual bool CanAddView(const ServerView* parent,
                          const ServerView* child) const = 0;
  virtual bool CanReorderView(const ServerView* view,
                              const ServerView* relative_view,
                              OrderDirection direction) const = 0;
  virtual bool CanDeleteView(const ServerView* view) const = 0;
  virtual bool CanGetViewTree(const ServerView* view) const = 0;
  
  
  virtual bool CanDescendIntoViewForViewTree(const ServerView* view) const = 0;
  virtual bool CanEmbed(const ServerView* view) const = 0;
  virtual bool CanChangeViewVisibility(const ServerView* view) const = 0;
  virtual bool CanSetViewSurfaceId(const ServerView* view) const = 0;
  virtual bool CanSetViewBounds(const ServerView* view) const = 0;

  
  
  
  virtual bool ShouldNotifyOnHierarchyChange(
      const ServerView* view,
      const ServerView** new_parent,
      const ServerView** old_parent) const = 0;
};

}  
}  

#endif  
