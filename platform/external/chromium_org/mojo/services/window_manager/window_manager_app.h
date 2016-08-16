// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_WINDOW_MANAGER_WINDOW_MANAGER_APP_H_
#define MOJO_SERVICES_WINDOW_MANAGER_WINDOW_MANAGER_APP_H_

#include <set>

#include "base/memory/scoped_ptr.h"
#include "mojo/aura/window_tree_host_mojo.h"
#include "mojo/aura/window_tree_host_mojo_delegate.h"
#include "mojo/public/cpp/application/application_delegate.h"
#include "mojo/public/cpp/application/interface_factory_impl.h"
#include "mojo/public/cpp/bindings/string.h"
#include "mojo/services/public/cpp/view_manager/types.h"
#include "mojo/services/public/cpp/view_manager/view_manager_client_factory.h"
#include "mojo/services/public/cpp/view_manager/view_manager_delegate.h"
#include "mojo/services/public/cpp/view_manager/view_observer.h"
#include "mojo/services/public/cpp/view_manager/window_manager_delegate.h"
#include "mojo/services/window_manager/window_manager_service_impl.h"
#include "ui/aura/client/focus_change_observer.h"
#include "ui/events/event_handler.h"
#include "ui/wm/public/activation_change_observer.h"

namespace aura {
namespace client {
class ActivationClient;
class FocusClient;
}
class Window;
}

namespace wm {
class ScopedCaptureClient;
}

namespace mojo {

class AuraInit;
class DummyDelegate;
class WindowManagerServiceImpl;
class WindowTreeHostMojo;

class WindowManagerApp
    : public ApplicationDelegate,
      public ViewManagerDelegate,
      public WindowManagerDelegate,
      public ViewObserver,
      public WindowTreeHostMojoDelegate,
      public ui::EventHandler,
      public aura::client::FocusChangeObserver,
      public aura::client::ActivationChangeObserver {
 public:
  WindowManagerApp(ViewManagerDelegate* view_manager_delegate,
                   WindowManagerDelegate* window_manager_delegate);
  virtual ~WindowManagerApp();

  static View* GetViewForWindow(aura::Window* window);

  
  void AddConnection(WindowManagerServiceImpl* connection);
  void RemoveConnection(WindowManagerServiceImpl* connection);

  
  void SetCapture(Id view);
  void FocusWindow(Id view);
  void ActivateWindow(Id view);

  bool IsReady() const;

  
  
  aura::WindowTreeHost* host() { return window_tree_host_.get(); }

  
  virtual void Initialize(ApplicationImpl* impl) MOJO_OVERRIDE;
  virtual bool ConfigureIncomingConnection(ApplicationConnection* connection)
      MOJO_OVERRIDE;

 private:
  typedef std::set<WindowManagerServiceImpl*> Connections;
  typedef std::map<Id, aura::Window*> ViewIdToWindowMap;

  
  virtual void OnEmbed(
      ViewManager* view_manager,
      View* root,
      ServiceProviderImpl* exported_services,
      scoped_ptr<ServiceProvider> imported_services) MOJO_OVERRIDE;
  virtual void OnViewManagerDisconnected(
      ViewManager* view_manager) MOJO_OVERRIDE;

  
  virtual void Embed(
      const String& url,
      InterfaceRequest<ServiceProvider> service_provider) OVERRIDE;
  virtual void DispatchEvent(EventPtr event) OVERRIDE;

  
  virtual void OnTreeChanged(
      const ViewObserver::TreeChangeParams& params) MOJO_OVERRIDE;
  virtual void OnViewDestroyed(View* view) MOJO_OVERRIDE;
  virtual void OnViewBoundsChanged(View* view,
                                   const gfx::Rect& old_bounds,
                                   const gfx::Rect& new_bounds) MOJO_OVERRIDE;

  
  virtual void CompositorContentsChanged(const SkBitmap& bitmap) MOJO_OVERRIDE;

  
  virtual void OnEvent(ui::Event* event) MOJO_OVERRIDE;

  
  virtual void OnWindowFocused(aura::Window* gained_focus,
                               aura::Window* lost_focus) MOJO_OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_active,
                                 aura::Window* lost_active) MOJO_OVERRIDE;

  aura::Window* GetWindowForViewId(Id view) const;

  
  
  
  
  void RegisterSubtree(View* view, aura::Window* parent);
  
  
  void UnregisterSubtree(View* view);

  InterfaceFactoryImplWithContext<WindowManagerServiceImpl, WindowManagerApp>
      window_manager_service_factory_;

  ViewManagerDelegate* wrapped_view_manager_delegate_;
  WindowManagerDelegate* wrapped_window_manager_delegate_;

  ViewManager* view_manager_;
  scoped_ptr<ViewManagerClientFactory> view_manager_client_factory_;
  View* root_;

  scoped_ptr<AuraInit> aura_init_;
  scoped_ptr<WindowTreeHostMojo> window_tree_host_;

  scoped_ptr<wm::ScopedCaptureClient> capture_client_;
  scoped_ptr<aura::client::FocusClient> focus_client_;
  aura::client::ActivationClient* activation_client_;

  Connections connections_;
  ViewIdToWindowMap view_id_to_window_map_;

  scoped_ptr<DummyDelegate> dummy_delegate_;

  DISALLOW_COPY_AND_ASSIGN(WindowManagerApp);
};

}  

#endif  
