// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POWER_RENDERER_FREEZER_H_
#define CHROME_BROWSER_CHROMEOS_POWER_RENDERER_FREEZER_H_

#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/power_manager_client.h"

namespace chromeos {

class CHROMEOS_EXPORT RendererFreezer : public PowerManagerClient::Observer {
 public:
  class Delegate {
   public:
    virtual ~Delegate() {}

    
    
    virtual bool FreezeRenderers() = 0;

    
    
    virtual bool ThawRenderers() = 0;

    
    virtual bool CanFreezeRenderers() = 0;
  };

  explicit RendererFreezer(scoped_ptr<Delegate> delegate);
  virtual ~RendererFreezer();

  
  virtual void SuspendImminent() OVERRIDE;
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;

 private:
  
  void OnReadyToSuspend(const base::Closure& power_manager_callback);

  
  base::CancelableClosure suspend_readiness_callback_;

  bool frozen_;

  scoped_ptr<Delegate> delegate_;

  base::WeakPtrFactory<RendererFreezer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RendererFreezer);
};

}  

#endif  
