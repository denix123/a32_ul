// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_HOST_ASH_WINDOW_TREE_HOST_H_
#define ASH_HOST_ASH_WINDOW_TREE_HOST_H_

#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"

namespace aura {
class Window;
class WindowTreeHost;
}

namespace gfx {
class Insets;
class Rect;
}

namespace ash {
struct AshWindowTreeHostInitParams;
class RootWindowTransformer;

class ASH_EXPORT AshWindowTreeHost {
 public:
  virtual ~AshWindowTreeHost() {}

  
  static AshWindowTreeHost* Create(
      const AshWindowTreeHostInitParams& init_params);

  
  virtual void ToggleFullScreen() = 0;

  
  
  
  
  
  virtual bool ConfineCursorToRootWindow() = 0;
  virtual void UnConfineCursor() = 0;

  virtual void SetRootWindowTransformer(
      scoped_ptr<RootWindowTransformer> transformer) = 0;

  virtual gfx::Insets GetHostInsets() const = 0;

  virtual aura::WindowTreeHost* AsWindowTreeHost() = 0;

  
  
  
  
  
  virtual void UpdateDisplayID(int64 id1, int64 id2) {}

  
  virtual void PrepareForShutdown() {}
};

}  

#endif  
