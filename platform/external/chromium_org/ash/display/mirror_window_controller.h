// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_MIRROR_WINDOW_CONTROLLER_H_
#define ASH_DISPLAY_MIRROR_WINDOW_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "ui/aura/window_tree_host_observer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"

namespace aura {
class Window;
}

namespace ui {
class Reflector;
}

namespace ash {
class AshWindowTreeHost;
class DisplayInfo;
class RootWindowTransformer;

namespace test{
class MirrorWindowTestApi;
}

class ASH_EXPORT MirrorWindowController : public aura::WindowTreeHostObserver {
 public:
  MirrorWindowController();
  virtual ~MirrorWindowController();

  
  
  void UpdateWindow(const DisplayInfo& display_info);

  
  
  void UpdateWindow();

  
  void Close();

  
  virtual void OnHostResized(const aura::WindowTreeHost* host) OVERRIDE;

  
  
  aura::Window* GetWindow();

 private:
  friend class test::MirrorWindowTestApi;

  
  
  scoped_ptr<RootWindowTransformer> CreateRootWindowTransformer() const;

  scoped_ptr<AshWindowTreeHost> ash_host_;
  gfx::Size mirror_window_host_size_;
  scoped_refptr<ui::Reflector> reflector_;

  DISALLOW_COPY_AND_ASSIGN(MirrorWindowController);
};

}  

#endif  
