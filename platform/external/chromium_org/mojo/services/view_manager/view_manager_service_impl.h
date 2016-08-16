// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_VIEW_MANAGER_SERVICE_IMPL_H_
#define MOJO_SERVICES_VIEW_MANAGER_VIEW_MANAGER_SERVICE_IMPL_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/services/public/interfaces/surfaces/surface_id.mojom.h"
#include "mojo/services/public/interfaces/view_manager/view_manager.mojom.h"
#include "mojo/services/view_manager/access_policy_delegate.h"
#include "mojo/services/view_manager/ids.h"
#include "mojo/services/view_manager/view_manager_export.h"

namespace gfx {
class Rect;
}

namespace mojo {
namespace service {

class AccessPolicy;
class ConnectionManager;
class ServerView;

#if defined(OS_WIN)
#pragma warning(push)
#pragma warning(disable : 4275)
#endif

class MOJO_VIEW_MANAGER_EXPORT ViewManagerServiceImpl
    : public InterfaceImpl<ViewManagerService>,
      public AccessPolicyDelegate {
 public:
  ViewManagerServiceImpl(ConnectionManager* connection_manager,
                         ConnectionSpecificId creator_id,
                         const std::string& creator_url,
                         const std::string& url,
                         const ViewId& root_id,
                         InterfaceRequest<ServiceProvider> service_provider);
  virtual ~ViewManagerServiceImpl();

  
  
  void set_delete_on_connection_error() { delete_on_connection_error_ = true; }

  ConnectionSpecificId id() const { return id_; }
  ConnectionSpecificId creator_id() const { return creator_id_; }
  const std::string& url() const { return url_; }

  
  ServerView* GetView(const ViewId& id) {
    return const_cast<ServerView*>(
        const_cast<const ViewManagerServiceImpl*>(this)->GetView(id));
  }
  const ServerView* GetView(const ViewId& id) const;

  
  bool HasRoot(const ViewId& id) const;

  
  void OnViewManagerServiceImplDestroyed(ConnectionSpecificId id);

  
  
  
  void ProcessViewBoundsChanged(const ServerView* view,
                                const gfx::Rect& old_bounds,
                                const gfx::Rect& new_bounds,
                                bool originated_change);
  void ProcessWillChangeViewHierarchy(const ServerView* view,
                                      const ServerView* new_parent,
                                      const ServerView* old_parent,
                                      bool originated_change);
  void ProcessViewHierarchyChanged(const ServerView* view,
                                   const ServerView* new_parent,
                                   const ServerView* old_parent,
                                   bool originated_change);
  void ProcessViewReorder(const ServerView* view,
                          const ServerView* relative_view,
                          OrderDirection direction,
                          bool originated_change);
  void ProcessViewDeleted(const ViewId& view, bool originated_change);
  void ProcessWillChangeViewVisibility(const ServerView* view,
                                       bool originated_change);

  
  
  
  virtual void OnConnectionError() MOJO_OVERRIDE;

 private:
  typedef std::map<ConnectionSpecificId, ServerView*> ViewMap;
  typedef base::hash_set<Id> ViewIdSet;

  bool IsViewKnown(const ServerView* view) const;

  
  
  bool CanReorderView(const ServerView* view,
                      const ServerView* relative_view,
                      OrderDirection direction) const;

  
  
  bool DeleteViewImpl(ViewManagerServiceImpl* source, ServerView* view);

  
  
  void GetUnknownViewsFrom(const ServerView* view,
                           std::vector<const ServerView*>* views);

  
  
  
  void RemoveFromKnown(const ServerView* view,
                       std::vector<ServerView*>* local_views);

  
  void RemoveRoot(const ViewId& view_id);

  void RemoveChildrenAsPartOfEmbed(const ViewId& view_id);

  
  
  
  Array<ViewDataPtr> ViewsToViewDatas(
      const std::vector<const ServerView*>& views);
  ViewDataPtr ViewToViewData(const ServerView* view);

  
  
  void GetViewTreeImpl(const ServerView* view,
                       std::vector<const ServerView*>* views) const;

  
  
  void NotifyDrawnStateChanged(const ServerView* view, bool new_drawn_value);

  
  virtual void CreateView(Id transport_view_id,
                          const Callback<void(ErrorCode)>& callback) OVERRIDE;
  virtual void DeleteView(Id transport_view_id,
                          const Callback<void(bool)>& callback) OVERRIDE;
  virtual void AddView(Id parent_id,
                       Id child_id,
                       const Callback<void(bool)>& callback) OVERRIDE;
  virtual void RemoveViewFromParent(
      Id view_id,
      const Callback<void(bool)>& callback) OVERRIDE;
  virtual void ReorderView(Id view_id,
                           Id relative_view_id,
                           OrderDirection direction,
                           const Callback<void(bool)>& callback) OVERRIDE;
  virtual void GetViewTree(
      Id view_id,
      const Callback<void(Array<ViewDataPtr>)>& callback) OVERRIDE;
  virtual void SetViewSurfaceId(Id view_id,
                                SurfaceIdPtr surface_id,
                                const Callback<void(bool)>& callback) OVERRIDE;
  virtual void SetViewBounds(Id view_id,
                             RectPtr bounds,
                             const Callback<void(bool)>& callback) OVERRIDE;
  virtual void SetViewVisibility(Id view_id,
                                 bool visible,
                                 const Callback<void(bool)>& callback) OVERRIDE;
  virtual void Embed(const String& url,
                     Id view_id,
                     ServiceProviderPtr service_provider,
                     const Callback<void(bool)>& callback) OVERRIDE;
  virtual void DispatchOnViewInputEvent(Id view_id, EventPtr event) OVERRIDE;

  
  virtual void OnConnectionEstablished() MOJO_OVERRIDE;

  
  virtual const base::hash_set<Id>& GetRootsForAccessPolicy() const OVERRIDE;
  virtual bool IsViewKnownForAccessPolicy(
      const ServerView* view) const OVERRIDE;
  virtual bool IsViewRootOfAnotherConnectionForAccessPolicy(
      const ServerView* view) const OVERRIDE;

  ConnectionManager* connection_manager_;

  
  const ConnectionSpecificId id_;

  
  const std::string url_;

  
  
  ConnectionSpecificId creator_id_;

  
  const std::string creator_url_;

  scoped_ptr<AccessPolicy> access_policy_;

  
  
  ViewMap view_map_;

  
  ViewIdSet known_views_;

  
  
  
  
  
  
  ViewIdSet roots_;

  
  bool delete_on_connection_error_;

  InterfaceRequest<ServiceProvider> service_provider_;

  DISALLOW_COPY_AND_ASSIGN(ViewManagerServiceImpl);
};

#if defined(OS_WIN)
#pragma warning(pop)
#endif

}  
}  

#endif  
