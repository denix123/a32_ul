// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ENV_PUBLIC_ATHENA_ENV_H_
#define ATHENA_ENV_PUBLIC_ATHENA_ENV_H_

#include "athena/athena_export.h"
#include "base/callback_forward.h"

namespace aura {
class WindowTreeHost;
}

namespace gfx {
class Insets;
}

namespace athena {

class ATHENA_EXPORT AthenaEnv {
 public:
  static void Create();
  static AthenaEnv* Get();
  static void Shutdown();

  virtual ~AthenaEnv() {}

  
  virtual aura::WindowTreeHost* GetHost() = 0;

  
  virtual void SetDisplayWorkAreaInsets(const gfx::Insets& insets) = 0;

  
  virtual void AddTerminatingCallback(const base::Closure& closure) = 0;
  virtual void RemoveTerminatingCallback(const base::Closure& closure) = 0;

  
  virtual void OnTerminating() = 0;
};

}  

#endif  
