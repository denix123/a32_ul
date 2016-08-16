// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DBUS_SCREEN_LOCK_SERVICE_PROVIDER_H_
#define CHROME_BROWSER_CHROMEOS_DBUS_SCREEN_LOCK_SERVICE_PROVIDER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/dbus/cros_dbus_service.h"
#include "dbus/exported_object.h"

namespace dbus {
class MethodCall;
}

namespace chromeos {

class ScreenLockServiceProvider
    : public CrosDBusService::ServiceProviderInterface {
 public:
  ScreenLockServiceProvider();
  virtual ~ScreenLockServiceProvider();

  
  virtual void Start(
      scoped_refptr<dbus::ExportedObject> exported_object) OVERRIDE;

 private:
  
  
  void OnExported(const std::string& interface_name,
                  const std::string& method_name,
                  bool success);

  
  void LockScreen(dbus::MethodCall* method_call,
                  dbus::ExportedObject::ResponseSender response_sender);

  
  
  base::WeakPtrFactory<ScreenLockServiceProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ScreenLockServiceProvider);
};

}  

#endif  
