// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_HOST_ASH_WINDOW_TREE_HOST_X11_H_
#define ASH_HOST_ASH_WINDOW_TREE_HOST_X11_H_

#include "ash/ash_export.h"
#include "ash/host/ash_window_tree_host.h"
#include "ash/host/transformer_helper.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/env_observer.h"
#include "ui/aura/window_tree_host_x11.h"

namespace ash {
class RootWindowTransformer;
class MouseCursorEventFilter;

class ASH_EXPORT AshWindowTreeHostX11 : public AshWindowTreeHost,
                                        public aura::WindowTreeHostX11,
                                        public aura::EnvObserver {
 public:
  explicit AshWindowTreeHostX11(const gfx::Rect& initial_bounds);
  virtual ~AshWindowTreeHostX11();

 private:
  
  virtual void ToggleFullScreen() OVERRIDE;
  virtual bool ConfineCursorToRootWindow() OVERRIDE;
  virtual void UnConfineCursor() OVERRIDE;
  virtual void SetRootWindowTransformer(
      scoped_ptr<RootWindowTransformer> transformer) OVERRIDE;
  virtual gfx::Insets GetHostInsets() const OVERRIDE;
  virtual aura::WindowTreeHost* AsWindowTreeHost() OVERRIDE;
  virtual void UpdateDisplayID(int64 id1, int64 id2) OVERRIDE;
  virtual void PrepareForShutdown() OVERRIDE;

  
  virtual void SetBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual gfx::Transform GetRootTransform() const OVERRIDE;
  virtual void SetRootTransform(const gfx::Transform& transform) OVERRIDE;
  virtual gfx::Transform GetInverseRootTransform() const OVERRIDE;
  virtual void UpdateRootWindowSize(const gfx::Size& host_size) OVERRIDE;
  virtual void OnCursorVisibilityChangedNative(bool show) OVERRIDE;

  
  virtual void OnConfigureNotify() OVERRIDE;
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual void TranslateAndDispatchLocatedEvent(ui::LocatedEvent* event)
      OVERRIDE;

  
  virtual void OnWindowInitialized(aura::Window* window) OVERRIDE;
  virtual void OnHostInitialized(aura::WindowTreeHost* host) OVERRIDE;

#if defined(OS_CHROMEOS)
  
  
  void SetCrOSTapPaused(bool state);
#endif

  scoped_ptr<XID[]> pointer_barriers_;

  TransformerHelper transformer_helper_;

  
  
  
  
  
  std::pair<int64, int64> display_ids_;

  DISALLOW_COPY_AND_ASSIGN(AshWindowTreeHostX11);
};

}  

#endif  
