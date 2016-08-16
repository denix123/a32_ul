// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_VIEW_MANAGER_CONNECTION_MANAGER_H_
#define MOJO_SERVICES_VIEW_MANAGER_CONNECTION_MANAGER_H_

#include <map>
#include <set>

#include "base/basictypes.h"
#include "mojo/public/cpp/bindings/array.h"
#include "mojo/services/view_manager/display_manager.h"
#include "mojo/services/view_manager/ids.h"
#include "mojo/services/view_manager/server_view.h"
#include "mojo/services/view_manager/server_view_delegate.h"
#include "mojo/services/view_manager/view_manager_export.h"

namespace ui {
class Event;
}

namespace mojo {

class ApplicationConnection;

namespace service {

class ViewManagerServiceImpl;

class MOJO_VIEW_MANAGER_EXPORT ConnectionManager : public ServerViewDelegate {
 public:
  
  
  class ScopedChange {
   public:
    ScopedChange(ViewManagerServiceImpl* connection,
                 ConnectionManager* connection_manager,
                 bool is_delete_view);
    ~ScopedChange();

    ConnectionSpecificId connection_id() const { return connection_id_; }
    bool is_delete_view() const { return is_delete_view_; }

    
    void MarkConnectionAsMessaged(ConnectionSpecificId connection_id) {
      message_ids_.insert(connection_id);
    }

    
    bool DidMessageConnection(ConnectionSpecificId connection_id) const {
      return message_ids_.count(connection_id) > 0;
    }

   private:
    ConnectionManager* connection_manager_;
    const ConnectionSpecificId connection_id_;
    const bool is_delete_view_;

    
    std::set<ConnectionSpecificId> message_ids_;

    DISALLOW_COPY_AND_ASSIGN(ScopedChange);
  };

  ConnectionManager(ApplicationConnection* app_connection,
                    const Callback<void()>& native_viewport_closed_callback);
  virtual ~ConnectionManager();

  
  ConnectionSpecificId GetAndAdvanceNextConnectionId();

  void AddConnection(ViewManagerServiceImpl* connection);
  void RemoveConnection(ViewManagerServiceImpl* connection);

  
  
  void EmbedRoot(const std::string& url,
                 InterfaceRequest<ServiceProvider> service_provider);

  
  
  void Embed(ConnectionSpecificId creator_id,
             const String& url,
             Id transport_view_id,
             InterfaceRequest<ServiceProvider> service_provider);

  
  ViewManagerServiceImpl* GetConnection(ConnectionSpecificId connection_id);

  
  ServerView* GetView(const ViewId& id);

  ServerView* root() { return root_.get(); }

  bool IsProcessingChange() const { return current_change_ != NULL; }

  bool is_processing_delete_view() const {
    return current_change_ && current_change_->is_delete_view();
  }

  
  
  void OnConnectionMessagedClient(ConnectionSpecificId id);

  
  bool DidConnectionMessageClient(ConnectionSpecificId id) const;

  
  ViewManagerServiceImpl* GetConnectionWithRoot(const ViewId& id) {
    return const_cast<ViewManagerServiceImpl*>(
        const_cast<const ConnectionManager*>(this)->GetConnectionWithRoot(id));
  }
  const ViewManagerServiceImpl* GetConnectionWithRoot(const ViewId& id) const;

  void DispatchViewInputEventToWindowManager(EventPtr event);

  
  
  void ProcessViewDestroyed(ServerView* view);
  void ProcessViewBoundsChanged(const ServerView* view,
                                const gfx::Rect& old_bounds,
                                const gfx::Rect& new_bounds);
  void ProcessWillChangeViewHierarchy(const ServerView* view,
                                      const ServerView* new_parent,
                                      const ServerView* old_parent);
  void ProcessViewHierarchyChanged(const ServerView* view,
                                   const ServerView* new_parent,
                                   const ServerView* old_parent);
  void ProcessViewReorder(const ServerView* view,
                          const ServerView* relative_view,
                          const OrderDirection direction);
  void ProcessViewDeleted(const ViewId& view);

 private:
  typedef std::map<ConnectionSpecificId, ViewManagerServiceImpl*> ConnectionMap;

  
  
  
  
  
  
  void PrepareForChange(ScopedChange* change);

  
  void FinishChange();

  
  bool IsChangeSource(ConnectionSpecificId connection_id) const {
    return current_change_ && current_change_->connection_id() == connection_id;
  }

  
  ViewManagerServiceImpl* EmbedImpl(
      ConnectionSpecificId creator_id,
      const String& url,
      const ViewId& root_id,
      InterfaceRequest<ServiceProvider> service_provider);

  
  virtual void OnViewDestroyed(const ServerView* view) OVERRIDE;
  virtual void OnWillChangeViewHierarchy(const ServerView* view,
                                         const ServerView* new_parent,
                                         const ServerView* old_parent) OVERRIDE;
  virtual void OnViewHierarchyChanged(const ServerView* view,
                                      const ServerView* new_parent,
                                      const ServerView* old_parent) OVERRIDE;
  virtual void OnViewBoundsChanged(const ServerView* view,
                                   const gfx::Rect& old_bounds,
                                   const gfx::Rect& new_bounds) OVERRIDE;
  virtual void OnViewSurfaceIdChanged(const ServerView* view) OVERRIDE;
  virtual void OnWillChangeViewVisibility(const ServerView* view) OVERRIDE;

  ApplicationConnection* app_connection_;

  
  ConnectionSpecificId next_connection_id_;

  
  ConnectionMap connection_map_;

  DisplayManager display_manager_;

  scoped_ptr<ServerView> root_;

  
  
  std::set<ViewManagerServiceImpl*> connections_created_by_connect_;

  
  
  ScopedChange* current_change_;

  DISALLOW_COPY_AND_ASSIGN(ConnectionManager);
};

}  
}  

#endif  
