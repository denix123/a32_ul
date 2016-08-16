// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_TEST_CHANGE_TRACKER_H_
#define MOJO_SERVICES_VIEW_MANAGER_TEST_CHANGE_TRACKER_H_

#include <string>
#include <vector>

#include "mojo/public/cpp/bindings/array.h"
#include "mojo/services/public/cpp/view_manager/types.h"
#include "mojo/services/public/interfaces/view_manager/view_manager.mojom.h"
#include "ui/gfx/rect.h"

namespace mojo {
namespace service {

enum ChangeType {
  CHANGE_TYPE_EMBED,
  
  CHANGE_TYPE_NODE_BOUNDS_CHANGED,
  CHANGE_TYPE_NODE_HIERARCHY_CHANGED,
  CHANGE_TYPE_NODE_REORDERED,
  CHANGE_TYPE_NODE_VISIBILITY_CHANGED,
  CHANGE_TYPE_NODE_DRAWN_STATE_CHANGED,
  CHANGE_TYPE_NODE_DELETED,
  CHANGE_TYPE_INPUT_EVENT,
  CHANGE_TYPE_DELEGATE_EMBED,
};

struct TestView {
  
  std::string ToString() const;

  
  std::string ToString2() const;

  Id parent_id;
  Id view_id;
  bool visible;
  bool drawn;
};

struct Change {
  Change();
  ~Change();

  ChangeType type;
  ConnectionSpecificId connection_id;
  std::vector<TestView> views;
  Id view_id;
  Id view_id2;
  Id view_id3;
  gfx::Rect bounds;
  gfx::Rect bounds2;
  int32 event_action;
  String creator_url;
  String embed_url;
  OrderDirection direction;
  bool bool_value;
};

std::vector<std::string> ChangesToDescription1(
    const std::vector<Change>& changes);

std::string ChangeViewDescription(const std::vector<Change>& changes);

void ViewDatasToTestViews(const Array<ViewDataPtr>& data,
                          std::vector<TestView>* test_views);

class TestChangeTracker {
 public:
  
  
  class Delegate {
   public:
    virtual void OnChangeAdded() = 0;

   protected:
    virtual ~Delegate() {}
  };

  TestChangeTracker();
  ~TestChangeTracker();

  void set_delegate(Delegate* delegate) {
    delegate_ = delegate;
  }

  std::vector<Change>* changes() { return &changes_; }

  
  
  void OnEmbed(ConnectionSpecificId connection_id,
               const String& creator_url,
               ViewDataPtr root);
  void OnViewBoundsChanged(Id view_id, RectPtr old_bounds, RectPtr new_bounds);
  void OnViewHierarchyChanged(Id view_id,
                              Id new_parent_id,
                              Id old_parent_id,
                              Array<ViewDataPtr> views);
  void OnViewReordered(Id view_id,
                       Id relative_view_id,
                       OrderDirection direction);
  void OnViewDeleted(Id view_id);
  void OnViewVisibilityChanged(Id view_id, bool visible);
  void OnViewDrawnStateChanged(Id view_id, bool drawn);
  void OnViewInputEvent(Id view_id, EventPtr event);
  void DelegateEmbed(const String& url);

 private:
  void AddChange(const Change& change);

  Delegate* delegate_;
  std::vector<Change> changes_;

  DISALLOW_COPY_AND_ASSIGN(TestChangeTracker);
};

}  
}  

#endif  
